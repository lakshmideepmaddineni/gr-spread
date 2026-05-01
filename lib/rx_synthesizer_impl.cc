/* -*- c++ -*- */
/*
 * Copyright 2026 lakshmideep.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "rx_synthesizer_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/filter/firdes.h>
#include <gnuradio/filter/fir_filter.h>
#include <volk/volk.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <gnuradio/fft/window.h>

namespace gr {
namespace spread {

rx_synthesizer::sptr
rx_synthesizer::make(const int samples_per_hop,
                     const int samples_per_symbol,
                     const double sample_rate,
                     const double high_freq,
                     const double transition,
                     const double energy_threshold,
                     const polynomial gen,
                     const polynomial init)
{
    return gnuradio::make_block_sptr<rx_synthesizer_impl>(samples_per_hop,
                                                          samples_per_symbol,
                                                          sample_rate,
                                                          high_freq,
                                                          transition,
                                                          energy_threshold,
                                                          gen,
                                                          init);
}

/*
 * The private constructor
 */
rx_synthesizer_impl::rx_synthesizer_impl(const int samples_per_hop,
                                         const int samples_per_symbol,
                                         const double sample_rate,
                                         const double high_freq,
                                         const double transition,
                                         const double energy_threshold,
                                         const polynomial gen,
                                         const polynomial init)
    : gr::sync_block("rx_synthesizer",
                     gr::io_signature::make(1, 1, sizeof(gr_complex)),
                     gr::io_signature::make(1, 1, sizeof(gr_complex))),
      _samp_sym(samples_per_symbol),
      _samp_hop(samples_per_hop),
      _sample_rate(sample_rate),
      _transition(transition),
      _energy_threshold(energy_threshold),
      _size(init.size()),
      clock_error(0),
      d_energy(0),
      d_mode(TRACK),
      d_clock(0),
      d_offset(0)
{
    code = new LFSR(gen, init);

    bool repeated = false;
    while (!repeated) {
        for (int j = 0; j < _samp_hop; j++)
            pattern_sequence.push_back(code->getFrequency());

        code->update();

        if (code->getFrequency() == pattern_sequence[0])
            repeated = true;
    }

    code->reset();

    generate_hop_freqs();

    // Create a bandpass filter for calculating out-of-band energy
std::vector<float> lowpass_taps = filter::firdes::low_pass(1,
                                                           sample_rate,
                                                           high_freq,
                                                           transition,
                                                           fft::window::WIN_HAMMING);
    track_filter = new filter::kernel::fir_filter_ccf(lowpass_taps);
    track_buffer = std::vector<gr_complex>(track_filter->ntaps(), 1);

    std::cout << "Tracking ntaps: " << track_filter->ntaps() << std::endl;
}

/*
 * Our virtual destructor.
 */
rx_synthesizer_impl::~rx_synthesizer_impl()
{
    delete code;
    delete track_filter;
}

void rx_synthesizer_impl::generate_hop_freqs()
{
    // Given the total size of the incoming vectors
    // generate a number of frequencies of that size
    // that fit within the specified bandwidth (sampling rate)
    int nfreqs = std::pow(2, _size);

    double bandwidth = _sample_rate;
    double channel_width = bandwidth / nfreqs;
    double inc = channel_width / 2;

    for (int i = 0; i < nfreqs; i++) {
        freq_set.push_back(inc + i*channel_width - bandwidth / 2);
    }
}

gr_complex rx_synthesizer_impl::transform(double freq, gr_complex sample)
{
    gr_complex phasor = static_cast<gr_complex>(std::polar(1.0, -2 * M_PI * freq * d_offset / _sample_rate));
    gr_complex result = phasor * sample;

    if (d_offset == _sample_rate)
        d_offset = 0;

    return result;
}

void rx_synthesizer_impl::add_tag(uint64_t item)
{
    const pmt::pmt_t key = pmt::string_to_symbol("hop_start");
    const pmt::pmt_t value = pmt::PMT_T;
    const pmt::pmt_t srcid = pmt::string_to_symbol(name());
    add_item_tag(0, item, key, value, srcid);
}

int
rx_synthesizer_impl::work(int noutput_items,
                          gr_vector_const_void_star &input_items,
                          gr_vector_void_star &output_items)
{
    const gr_complex *sample_input = (const gr_complex *) input_items[0];
    gr_complex *out = (gr_complex *) output_items[0];

    switch (d_mode) {

        // TODO: Implement a separate acquisition routine
        case SYNC: {

            for (int i = 0; i < noutput_items; i++) {

            }

            break;
        }

        // Acquire/track the signal
        // Note: Simple acquisition - wait until we detect a hop
        case TRACK: {

            gr_complex filtered_sample(0, 0);

            for (int i = 0; i < noutput_items; i++) {

                int selected_freq = pattern_sequence[d_clock % pattern_sequence.size()];
                gr_complex despread_sample = transform(freq_set[selected_freq],
                                                       sample_input[i]);

                // Calculate the error energy
                // for early-late gate
                track_buffer.push_back(despread_sample);
                track_buffer.erase(track_buffer.begin());

                filtered_sample = track_filter->filter(&track_buffer[0]);
                float filtered_sample_abs = std::abs(filtered_sample);

                int sample_decision = (filtered_sample_abs < _energy_threshold);
                int clock_value = 2 * ((d_clock % _samp_hop) < (_samp_hop / 2)) - 1;
                int error = (sample_decision * clock_value);

                clock_error += error;

                // Output the the dehopped sample
                out[i] = despread_sample;
                d_offset++;

                d_clock -= error;
                d_clock++;

            }

            return noutput_items;
        }

        default: {
            throw std::runtime_error("Error: Unknown mode.");
        }

    } // End of mode switch

    return noutput_items;
}

} /* namespace spread */
} /* namespace gr */
