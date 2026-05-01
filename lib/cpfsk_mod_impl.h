/* -*- c++ -*- */
/*
 * Copyright 2026 lakshmideep.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPREAD_CPFSK_MOD_IMPL_H
#define INCLUDED_SPREAD_CPFSK_MOD_IMPL_H

#include <gnuradio/spread/cpfsk_mod.h>

namespace gr {
namespace spread {

class cpfsk_mod_impl : public cpfsk_mod
{
private:
    // Nothing to declare in this block.
      const int samp_sym;
      int d_offset; 
      double phase; 
public:
    cpfsk_mod_impl(const int samples_per_symbol);
    ~cpfsk_mod_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace spread
} // namespace gr

#endif /* INCLUDED_SPREAD_CPFSK_MOD_IMPL_H */
