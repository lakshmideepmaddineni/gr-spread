/* -*- c++ -*- */
/*
 * Copyright 2026 lakshmideep.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPREAD_SYNTHESIZER_H
#define INCLUDED_SPREAD_SYNTHESIZER_H

#include <gnuradio/spread/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace spread {

    /*!
     * \brief <+description of block+>
     * \ingroup spread
     *
     */
    class SPREAD_API synthesizer : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<synthesizer> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of spread::synthesizer.
       *
       * To avoid accidental use of raw pointers, spread::synthesizer's
       * constructor is in a private implementation
       * class. spread::synthesizer::make is the public interface for
       * creating new instances.
       */
      static sptr make(const int samples_per_hop, const int delay, const double sample_rate, const std::vector<unsigned char> gen, const std::vector<unsigned char> init);
    };

  } // namespace spread
} // namespace gr

#endif /* INCLUDED_SPREAD_SYNTHESIZER_H */
