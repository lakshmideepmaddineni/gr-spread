/* -*- c++ -*- */
/*
 * Copyright 2026 lakshmideep.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPREAD_RX_SYNTHESIZER_IMPL_H
#define INCLUDED_SPREAD_RX_SYNTHESIZER_IMPL_H


#include <gnuradio/spread/rx_synthesizer.h>
#include <gnuradio/filter/fir_filter.h>
#include "code_generator.h"
#include <vector>
namespace gr {
namespace spread {

class rx_synthesizer_impl : public rx_synthesizer
{
private:
    // Nothing to declare in this block.
      const int _samp_hop; 
      const int _samp_sym; 
      const int _size; 

      const double _transition; 
      const double _sample_rate;       
      const double _energy_threshold; 

      int d_offset, d_clock; 
      int clock_error; 

      float d_energy; 

      enum modes {SYNC, TRACK} d_mode; 

      std::vector<int> pattern_sequence; 
      std::vector<double> freq_set; 

      std::vector<gr_complex> acq_buffer; 
      std::vector<gr_complex> track_buffer; 

      filter::kernel::fir_filter_ccf * track_filter; 

      LFSR * code; 
    void generate_hop_freqs();
    gr_complex transform(double freq, gr_complex sample);
    void add_tag(uint64_t item);
public:
    rx_synthesizer_impl(const int samples_per_hop,
                        const int samples_per_symbol,
                        const double sample_rate,
                        const double high_freq,
                        const double transition,
                        const double energy_threshold,
                        const std::vector<unsigned char> gen,
                        const std::vector<unsigned char> init);
    ~rx_synthesizer_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace spread
} // namespace gr

#endif /* INCLUDED_SPREAD_RX_SYNTHESIZER_IMPL_H */
