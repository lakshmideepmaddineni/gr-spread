/* -*- c++ -*- */
/*
 * Copyright 2026 lakshmideep.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPREAD_CPFSK_DEMOD_H
#define INCLUDED_SPREAD_CPFSK_DEMOD_H

#include <gnuradio/spread/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
namespace spread {

/*!
 * \brief <+description of block+>
 * \ingroup spread
 *
 */
class SPREAD_API cpfsk_demod : virtual public gr::sync_decimator
{
public:
    typedef std::shared_ptr<cpfsk_demod> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of spread::cpfsk_demod.
     *
     * To avoid accidental use of raw pointers, spread::cpfsk_demod's
     * constructor is in a private implementation
     * class. spread::cpfsk_demod::make is the public interface for
     * creating new instances.
     */
    static sptr make(const int samples_per_symbol);
};

} // namespace spread
} // namespace gr

#endif /* INCLUDED_SPREAD_CPFSK_DEMOD_H */
