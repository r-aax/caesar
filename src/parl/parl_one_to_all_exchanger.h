/// \file
/// \brief One to all exchanger declaration.
///
/// One to all exchanger declaration.

#ifndef CAESAR_PARL_ONE_TO_ALL_EXCHANGER_H
#define CAESAR_PARL_ONE_TO_ALL_EXCHANGER_H

#include "parl_buffers.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief Data gatherer.
///
/// Class for exchanges between process 0
/// and other processes.
class OneToAllExchanger : public Buffers
{

public:

    // Default constructor.
    OneToAllExchanger();

    // Default destructor.
    ~OneToAllExchanger();

    //
    // Allocate memory.
    //

    // Allocate buffers.
    void
    allocate();

    // Set size of exchanges 0 <-> i.
    void
    set_size(size_t i,
             size_t buffer_size);

    //
    // Data transfers.
    //

    // Gather data in process 0.
    void
    gather();
};

/// @}

}

}

#endif // !CAESAR_PARL_ONE_TO_ALL_EXCHANGER_H
