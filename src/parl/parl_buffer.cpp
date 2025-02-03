/// \file
/// \brief Implementation of buffer for interprocess communications.
///
/// Implementation of buffer for interprocess communications.

#include "parl_buffer.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

/// \brief Default constructor.
///
/// Constructor by default.
Buffer::Buffer()
    : Buffer(0, 0)
{
}

/// \brief Default constructor.
///
/// Construct buffer for working with given process.
///
/// \param[in] process_id_           Process id.
/// \param[in] neighbour_process_id_ Process id for communication.
Buffer::Buffer(size_t process_id_,
               size_t neighbour_process_id_)
    : process_id(process_id_),
      neighbour_process_id(neighbour_process_id_),
      requests(2)
{
}

/// \brief Default destructor.
Buffer::~Buffer()
{
}

//
// Data manipulation.
//

/// \brief Set size.
///
/// Set size of buffer.
///
/// \param[in] s Size.
void
Buffer::set_size(size_t s)
{
    // Clear.
    in_data.clear();
    out_data.clear();

    // Add values.
    in_data.insert(in_data.begin(), s, 0.0);
    out_data.insert(out_data.begin(), s, 0.0);
}

/// \brief Fill out data.
///
/// Fill whole out vector with data.
///
/// \param[in] v Value.
void
Buffer::fill_out_data(double v)
{
    fill(out_data.begin(), out_data.end(), v);
}

/// \brief Print data.
///
/// Print all data.
///
/// \param[out] os Output stream.
void
Buffer::print(ostream& os)
{
    size_t s = size();

    os << "Buffer " << process_id << " <-> " << neighbour_process_id << " (size " << s << "):" << endl;
    os << "IN :";

    for (size_t i = 0; i < s; ++i)
    {
        os << ((i == 0) ? " " : ", ") << in_data[i];
    }

    os << endl << "OUT:";

    for (size_t i = 0; i < s; ++i)
    {
        os << ((i == 0) ? " " : ", ") << out_data[i];
    }

    os << endl << "----------" << endl;
}

/// \brief Print data for all processes.
///
/// Print data of buffer in all processes consequently.
///
/// \param[out] os Output stream.
void
Buffer::print_all(ostream& os)
{
    size_t s = mpi_size();

    for (size_t i = 0; i < s; ++i)
    {
        if (mpi_rank() == i)
        {
            print(os);
        }

        mpi_barrier();
    }
}

//
// Data transfer.
//

/// \brief Async send.
///
/// Asynchronic send.
///
/// \param[out] requests  Requests.
/// \param[in]  request_i Request index.
void
Buffer::isend(MPIRequests& requests,
              size_t request_i)
{
    mpi_isend(out_data, neighbour_process_id, requests, request_i);
}

/// \brief Async receive.
///
/// Asynchronic receice.
///
/// \param[out] request Request.
void
Buffer::irecv(MPIRequests& requests,
              size_t request_i)
{
    mpi_irecv(in_data, neighbour_process_id, requests, request_i);
}

/// \brief Exchange data between processes.
///
///     self_id                      process_id
///     ========                     ==========
///     in_data ----------+     +--- in_data
///                       |     |
///                 +---- | ----+
///                 |     |
///     out_data <--+     +--------> out_data
void
Buffer::exchange()
{
    irecv();
    isend();
    mpi_waitall(requests);
}

/// \brief Reduce sum in 0 process.
///
/// Reduce with operation add.
void
Buffer::reduce_sum()
{
    mpi_reduce_sum(out_data, in_data);
}

/// @}

}

}
