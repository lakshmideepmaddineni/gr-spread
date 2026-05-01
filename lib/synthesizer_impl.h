/* -*- c++ -*- */
/*
 * Copyright 2026 lakshmideep.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPREAD_SYNTHESIZER_IMPL_H
#define INCLUDED_SPREAD_SYNTHESIZER_IMPL_H

#include <gnuradio/spread/synthesizer.h>
#include "code_generator.h"
#include <vector>

namespace gr {
  namespace spread {

    class synthesizer_impl : public synthesizer
    {
     private:
      // Nothing to declare in this block.
      const int _samp_hop; 
      const int _size; 
      const double _sample_rate; 

      std::vector<int> pattern_sequence; 
      std::vector<double> freq_set; 

      LFSR * code; 

      int d_delay; 
      int d_clock;
      int d_offset; 

     public:
      synthesizer_impl(const int samples_per_hop, const int delay, const double sample_rate, const std::vector<unsigned char> gen, const std::vector<unsigned char> init);
      ~synthesizer_impl();

     void generate_hop_freqs(); 
      
      gr_complex transform(double freq, gr_complex sample); 
      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace spread
} // namespace gr

#endif /* INCLUDED_SPREAD_SYNTHESIZER_IMPL_H */
