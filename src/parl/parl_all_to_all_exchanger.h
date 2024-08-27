/// \file
/// \brief All to all exchanger declaration.
///
/// All to all exchanger declaration.
/// All to all exchanger - class for vector of buffers.

#ifndef CAESAR_PARL_ALL_TO_ALL_EXCHANGER_H
#define CAESAR_PARL_ALL_TO_ALL_EXCHANGER_H

#include "parl_buffers.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief All to all exchanger.
class AllToAllExchanger : public Buffers
{

public:

    // Default constructor.
    AllToAllExchanger();

    // Default destructor.
    ~AllToAllExchanger();

    //
    // Allocate memory.
    //

    // Allocate buffers.
    void
    allocate();

    /// \brief Set size of buffer.
    ///
    /// Set size of buffer.
    ///
    /// \param[in] i Index of buffer.
    /// \param[in] s Size.
    inline void
    set_size(size_t i,
             size_t s)
    {
        buffers[i].set_size(s);
    }

    //
    // Data transfers.
    //

    // Exchange data.
    void
    exchange();
};

/// @}

}

}

#endif // !CAESAR_PARL_ALL_TO_ALL_EXCHANGER_H
