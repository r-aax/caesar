/// \file
/// \brief MPI wrapper functions.
///
/// MPI wrapper functions implementation.

#include "parl_mpi.h"

#include <cstring>

#ifdef COMPILE_ENABLE_MPI

// Disable cast-function-type warning inside openmpi.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
#pragma GCC diagnostic ignored "-Wold-style-cast"
// The only place where MPI is included.
#include "mpi.h"
#pragma GCC diagnostic pop

/// \brief MPI request type.
#define MPI_REQUEST MPI_Request

#else // !COMPILE_ENABLE_MPI

/// \brief MPI request type.
#define MPI_REQUEST int

#endif // COMPILE_ENABLE_MPI

namespace caesar
{

namespace parl
{

/// \addtogroup parl
/// @{

//
// MPIRequests methods.
//

/// \brief Allocate memory.
///
/// Allocate memory.
///
/// \param[in] n Count of requests.
void
MPIRequests::alloc_memory(size_t n)
{
    CHECK_ERROR((count_ == 0) && (data == nullptr), "MPIRequests: double allocation");

    count_ = n;

    if (n > 0)
    {
        data = new char[n * sizeof(MPI_REQUEST)];
    }
}

/// \brief Free memory.
///
/// Free memory.
void
MPIRequests::free_memory()
{
    count_ = 0;

    if (data != nullptr)
    {
        delete [] data;
        data = nullptr;
    }
}

/// \brief Constructor.
///
/// Constructor.
///
/// \param[in] n Number of requests.
MPIRequests::MPIRequests(size_t n)
{
    alloc_memory(n);
}

/// \brief Copy constructor.
///
/// Copy constructor.
///
/// \param[in] src Source.
MPIRequests::MPIRequests(const MPIRequests& src)
{
    alloc_memory(src.count());

    if (count_ > 0)
    {
        memcpy(data, src.get(0), count_ * sizeof(MPI_REQUEST));
    }
}

/// \brief Destructor.
///
/// Default destructor.
MPIRequests::~MPIRequests()
{
    free_memory();
}

/// \brief Get address of request.
///
/// Get address of request.
///
/// \param[in] i Index.
///
/// \return
/// Address of request.
void*
MPIRequests::get(size_t i) const
{
    DEBUG_CHECK_ERROR(i < count_, "MPIRequests: wrong index");

    return static_cast<void*>(data + (i * sizeof(MPI_REQUEST)));
}

/// \brief Resize data for requests.
///
/// Resize memory for new size.
///
/// \param[in] n New count of requests.
void
MPIRequests::resize(size_t n)
{
    free_memory();
    alloc_memory(n);
}

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

#ifdef COMPILE_ENABLE_MPI

    int initialized { 0 };

    MPI_Initialized(&initialized);

    return (initialized != 0);

#else // !COMPILE_ENABLE_MPI

    return false;

#endif // COMPILE_ENABLE_MPI

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

#ifdef COMPILE_ENABLE_MPI

    return MPI_Init(argc, argv);

#else // !COMPILE_ENABLE_MPI

    (void)argc;
    (void)argv;

    return 0;

#endif // COMPILE_ENABLE_MPI

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

#ifdef COMPILE_ENABLE_MPI

    return MPI_Finalize();

#else // !COMPILE_ENABLE_MPI

    return 0;

#endif // COMPILE_ENABLE_MPI

}

/// \brief Barrier.
///
/// Barrier for synchronization.
void
mpi_barrier()
{

#ifdef COMPILE_ENABLE_MPI

    if (!is_mpi_initialized())
    {
        return;
    }

    MPI_Barrier(MPI_COMM_WORLD);

#endif // COMPILE_ENABLE_MPI

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

#ifdef COMPILE_ENABLE_MPI

    if (!is_mpi_initialized())
    {
        return 1;
    }

    int s { 0 };

    MPI_Comm_size(MPI_COMM_WORLD, &s);

    return static_cast<size_t>(s);

#else // !COMPILE_ENABLE_MPI

    return 1;

#endif // COMPILE_ENABLE_MPI

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

#ifdef COMPILE_ENABLE_MPI

    if (!is_mpi_initialized())
    {
        return 0;
    }

    int r { 0 };

    MPI_Comm_rank(MPI_COMM_WORLD, &r);

    return static_cast<size_t>(r);

#else // !COMPILE_ENABLE_MPI

    return 0;

#endif // COMPILE_ENABLE_MPI

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
/// \param[out] requests   Requests.
/// \param[in]  request_i  Request index.
void
mpi_isend(vector<double>& data,
          size_t process_id,
          MPIRequests& requests,
          size_t request_i)
{

#if COMPILE_ENABLE_MPI

    if (!is_mpi_initialized())
    {
        return;
    }

    MPI_Isend(data.data(),
              static_cast<int>(data.size()),
              MPI_DOUBLE,
              static_cast<int>(process_id),
              0,
              MPI_COMM_WORLD,
              static_cast<MPI_Request*>(requests.get(request_i)));

#else // !COMPILE_ENABLE_MPI

    (void)data;
    (void)process_id;
    (void)requests;
    (void)request_i;

#endif // COMPILE_ENABLE_MPI

}

/// \brief Async receive.
///
/// Asynchronic receive.
///
/// \param[out] data       Data to receive.
/// \param[in]  process_id Process identifier.
/// \param[out] requests   Requests.
/// \param[in]  request_i  Request index.
void
mpi_irecv(vector<double>& data,
          size_t process_id,
          MPIRequests& requests,
          size_t request_i)
{

#ifdef COMPILE_ENABLE_MPI

    if (!is_mpi_initialized())
    {
        return;
    }

    MPI_Irecv(data.data(),
              static_cast<int>(data.size()),
              MPI_DOUBLE,
              static_cast<int>(process_id),
              0,
              MPI_COMM_WORLD,
              static_cast<MPI_Request*>(requests.get(request_i)));

#else // !COMPILE_ENABLE_MPI

    (void)data;
    (void)process_id;
    (void)requests;
    (void)request_i;

#endif // COMPILE_ENABLE_MPI

}

/// \brief Wait.
///
/// Wait for request.
///
/// \param[in] requests  Requests.
/// \param[in] request_i Request index.
void
mpi_wait(MPIRequests& requests,
         size_t request_i)
{

#ifdef COMPILE_ENABLE_MPI

    if (!is_mpi_initialized())
    {
        return;
    }

    MPI_Wait(static_cast<MPI_Request*>(requests.get(request_i)),
             MPI_STATUS_IGNORE);

#else // !COMPILE_ENABLE_MPI

    (void)requests;
    (void)request_i;

#endif // COMPILE_ENABLE_MPI

}

/// \brief Wait all requests.
///
/// Wait for all requests.
///
/// \param[in,out] requests Requests.
void
mpi_waitall(MPIRequests& requests)
{

#ifdef COMPILE_ENABLE_MPI

    if (!is_mpi_initialized())
    {
        return;
    }

    MPI_Waitall(static_cast<int>(requests.count()),
                static_cast<MPI_Request*>(requests.get()),
                MPI_STATUSES_IGNORE);

#else // !COMPILE_ENABLE_MPI

    (void)requests;

#endif // COMPILE_ENABLE_MPI

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

#ifdef COMPILE_ENABLE_MPI

    if (!is_mpi_initialized())
    {
        return;
    }

    MPI_Reduce(out_data.data(),
               in_data.data(),
               static_cast<int>(in_data.size()),
               MPI_DOUBLE,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

#else // !COMPILE_ENABLE_MPI

    (void)out_data;
    (void)in_data;

#endif // COMPILE_ENABLE_MPI

}

/// @}

}

}
