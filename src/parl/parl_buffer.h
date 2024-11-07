/// \file
/// \brief Buffer or interprocess communications.
///
/// Buffer for interprocess communications.

#ifndef CAESAR_PARL_BUFFER_H
#define CAESAR_PARL_BUFFER_H

#include <iostream>

#include "parl_mpi.h"
#include "utils/utils.h"

using namespace std;

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief Buffer for interprocess communications.
class Buffer
{

private:

    /// \brief Own process id.
    size_t process_id { 0 };

    /// \brief Neighbour process id.
    ///
    /// Process id to communicate with.
    size_t neighbour_process_id { 0 };

    /// \brief Input vector of data.
    ///
    /// Vector of data for receiving from process_id process.
    vector<double> in_data;

    /// \brief Output vector of data.
    ///
    /// Vector of data for sending to process_id process.
    vector<double> out_data;

    /// \brief Vector of requests.
    vector<MPI_Request> requests { 0, 0 };

public:

    // Default constructor.
    Buffer();

    // Constructor for pair of processes.
    Buffer(size_t process_id_,
           size_t neighbour_process_id_);

    // Default destructor.
    ~Buffer();

    //
    // Data manipulation.
    //

    /// \brief Get size of buffer.
    ///
    /// Get size of buffer.
    ///
    /// \return
    /// Size of buffer.
    inline size_t
    size() const
    {
        return in_data.size();
    }

    /// \brief Get in data.
    ///
    /// Get in data.
    ///
    /// \return
    /// In data.
    inline vector<double>&
    get_in_data()
    {
        return in_data;
    }

    /// \brief Get out data.
    ///
    /// Get out data.
    ///
    /// \return
    /// Out data.
    inline vector<double>&
    get_out_data()
    {
        return out_data;
    }

    // Set size.
    void
    set_size(size_t s);

    // Fill out data.
    void
    fill_out_data(double v);

    // Print data.
    void
    print(ostream& os = cout);

    // Print data for all processes.
    void
    print_all(ostream& os = cout);

    //
    // Data transfer.
    //

    // Async send.
    void
    isend(MPI_Request& request);

    /// \brief Async send.
    ///
    /// Asynchronic send using inner request.
    inline void
    isend()
    {
        isend(requests[0]);
    }

    // Async receive.
    void
    irecv(MPI_Request& request);

    /// \brief
    ///
    /// Asynchronic receive using inner request.
    inline void
    irecv()
    {
        irecv(requests[1]);
    }

    // Exchange data between processes.
    void
    exchange();

    // Reduce sum in 0 process.
    void
    reduce_sum();
};

/// @}

}

}

#endif // !CAESAR_PARL_BUFFER_H
