/// \file
/// \brief Class that holds vector of buffers.
///
/// Class for holding vector of buffers.

#ifndef CAESAR_PARL_BUFFERS_H
#define CAESAR_PARL_BUFFERS_H

#include "parl_buffer.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief Buffers holder.
class Buffers
{

public:

    /// \brief Vector of buffers.
    vector<Buffer> buffers;

    /// \brief Requests.
    MPIRequests requests;

public:

    // Default constructor.
    Buffers();

    // Default destructor.
    virtual
    ~Buffers();

    //
    // Access to data.
    //

    /// \brief Get in data.
    ///
    /// Get in data.
    ///
    /// \param[in] i Index of buffer.
    ///
    /// \return
    /// In data.
    inline vector<double>&
    get_in_data(size_t i)
    {
        return buffers[i].get_in_data();
    }

    /// \brief Get out data.
    ///
    /// Get out data.
    ///
    /// \param[in] i Index of buffer.
    ///
    /// \return
    /// Out data.
    inline vector<double>&
    get_out_data(size_t i)
    {
        return buffers[i].get_out_data();
    }

    //
    // Print information.
    //

    // Print.
    void
    print(ostream& os = cout);

    // Print all.
    void
    print_all(ostream& os = cout);
};

/// @}

}

}

#endif // !CAESAR_PARL_BUFFERS_H
