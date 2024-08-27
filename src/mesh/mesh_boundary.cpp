/// \file
/// \brief Boundary implementation.
///
/// Boundary between domains implementation.

#include "mesh_boundary.h"

#include "parl/parl.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Default constructor.
///
/// Default constructor.
///
/// \param[in] domain_           Own domain.
/// \param[in] neighbour_domain_ Neighbour domain.
Boundary::Boundary(size_t domain_,
                   size_t neighbour_domain_)
    : domain(domain_),
      neighbour_domain(neighbour_domain_)
{
}

/// \brief Default destructor.
///
/// Default destructor.
Boundary::~Boundary()
{
}

/// \brief Print boundary.
///
/// Print boundary in current process.
///
/// \param[out] os Out stream.
void
Boundary::print(ostream& os)
{
    size_t s = pairs.size();

    if (s > 0)
    {
        os << "Boundary " << domain << " <-> " << neighbour_domain << ":";

        if (s)
        {
            for (size_t i = 0; i < s; ++i)
            {
                pair<Cell*, Cell*>& p = pairs[i];

                os << ((i == 0) ? " (" : " ,(") << p.first->get_id() << ", " << p.second->get_id() << ")";
            }
        }

        os << endl;
    }
}

/// \brief Print in all processes.
///
/// Print boundary in all processes.
///
/// \param[out] os Out stream.
void
Boundary::print_all(ostream& os)
{
    size_t s = parl::mpi_size();

    for (size_t i = 0; i < s; ++i)
    {
        if (parl::mpi_rank() == i)
        {
            print(os);
        }

        parl::mpi_barrier();
    }
}

/// @}

}

}
