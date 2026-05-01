/* -*- c++ -*- */
/*
 * Copyright 2026 lakshmideep.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPREAD_CPFSK_MOD_H
#define INCLUDED_SPREAD_CPFSK_MOD_H

#include <gnuradio/spread/api.h>
#include <gnuradio/sync_interpolator.h>

namespace gr {
namespace spread {

/*!
 * \brief <+description of block+>
 * \ingroup spread
 *
 */
class SPREAD_API cpfsk_mod : virtual public gr::sync_interpolator
{
public:
    typedef std::shared_ptr<cpfsk_mod> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of spread::cpfsk_mod.
     *
     * To avoid accidental use of raw pointers, spread::cpfsk_mod's
     * constructor is in a private implementation
     * class. spread::cpfsk_mod::make is the public interface for
     * creating new instances.
     */
    static sptr make(const int samples_per_symbol);
};

} // namespace spread
} // namespace gr

#endif /* INCLUDED_SPREAD_CPFSK_MOD_H */
