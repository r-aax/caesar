/// \file
/// \brief MPI wrapper functions.
///
/// MPI wrapper functions implementation.

#include "parl_mpi.h"

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

//
// Basic functions.
//

/// \brief Check initialization.
///
/// Check if MPI is initialized.
///
/// \return
/// true - if MPI is initialized,
/// false - otherwise.
bool
is_mpi_initialized()
{
    int initialized { 0 };

    MPI_Initialized(&initialized);

    return (initialized != 0);
}

/// \brief Initialization.
///
/// MPI initialization.
///
/// \param[in] argc Number of arguments pointer.
/// \param[in] argv Arguments pointer.
///
/// \return
/// Status of operation.
int
mpi_init(int* argc,
         char*** argv)
{
    return MPI_Init(argc, argv);
}

/// \brief Finalize.
///
/// MPI finalization.
///
/// \return
/// Status of operation.
int
mpi_finalize()
{
    return MPI_Finalize();
}

/// \brief Barrier.
///
/// Barrier for synchronization.
void
mpi_barrier()
{
    MPI_Barrier(MPI_COMM_WORLD);
}

//
// Numbers.
//

/// \brief Size.
///
/// Get size - number of processes.
///
/// \return
/// MPI size.
size_t
mpi_size()
{
    if (is_mpi_initialized())
    {
        int s { 0 };

        MPI_Comm_size(MPI_COMM_WORLD, &s);

        return static_cast<size_t>(s);
    }
    else
    {
        return 1;
    }
}

/// \brief Rank.
///
/// Get rank - current process index.
///
/// \return
/// MPI rank.
size_t
mpi_rank()
{
    if (is_mpi_initialized())
    {
        int r { 0 };

        MPI_Comm_rank(MPI_COMM_WORLD, &r);

        return static_cast<size_t>(r);
    }
    else
    {
        return 0;
    }
}

//
// Data transfer.
//

/// \brief Acync send.
///
/// Asynchronic send.
///
/// \param[in]  data       Data to send.
/// \param[in]  process_id Process identifier.
/// \param[out] request    Request.
void
mpi_isend(vector<double>& data,
          size_t process_id,
          MPI_Request& request)
{
    MPI_Isend(data.data(),
              static_cast<int>(data.size()),
              MPI_DOUBLE,
              static_cast<int>(process_id),
              0,
              MPI_COMM_WORLD,
              &request);
}

/// \brief Async receive.
///
/// Asynchronic receive.
///
/// \param[out] data       Data to receive.
/// \param[in]  process_id Process identifier.
/// \param[out] request    Request.
void
mpi_irecv(vector<double>& data,
          size_t process_id,
          MPI_Request& request)
{
    MPI_Irecv(data.data(),
              static_cast<int>(data.size()),
              MPI_DOUBLE,
              static_cast<int>(process_id),
              0,
              MPI_COMM_WORLD,
              &request);
}

/// \brief Wait.
///
/// Wait for request.
///
/// \param[in] request Request.
void
mpi_wait(MPI_Request request)
{
    MPI_Wait(&request,
             MPI_STATUS_IGNORE);
}

/// \brief Wait all requests.
///
/// Wait for all requests.
///
/// \param[in,out] requests Requests.
void
mpi_waitall(vector<MPI_Request>& requests)
{
    MPI_Waitall(static_cast<int>(requests.size()),
                requests.data(),
                MPI_STATUSES_IGNORE);
}

/// \brief MPI reduce with add operation.
///
/// MPI reduce with add operation.
///
/// \param[out] out_data Out data vector.
/// \param[in]  in_data  In data vector.
void
mpi_reduce_sum(vector<double>& out_data,
               vector<double>& in_data)
{
    MPI_Reduce(out_data.data(),
               in_data.data(),
               static_cast<int>(in_data.size()),
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);
}

/// @}

}

}
