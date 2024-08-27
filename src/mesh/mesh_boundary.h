/// \file
/// \brief Boundary between domains.
///
/// Boundary between domains declaration.

#ifndef MESH_BOUNDARY_H
#define MESH_BOUNDARY_H

#include "mesh_cell.h"

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Boundary between domains.
class Boundary
{

private:

    /// \brief Own domain.
    size_t domain;

    /// \brief Neighbour domain.
    size_t neighbour_domain;

public:

    /// \brief Pairs of cells on boundary.
    ///
    /// In each pair:
    /// fisrt cell - cell in current domain,
    /// second cell - cell in neighbour domain.
    vector<pair<Cell*, Cell*>> pairs;

public:

    // Default constructor.
    Boundary(size_t domain_,
             size_t neighbour_domain_);

    // Default destructor.
    ~Boundary();

    /// \brief Get size.
    ///
    /// Get size.
    ///
    /// \param
    /// Size.
    inline size_t
    size() const
    {
        return pairs.size();
    }

    /// \brief Add pair.
    ///
    /// Add pair of cells into boundary.
    ///
    /// \param[in] in_cell        Cell in current domain.
    /// \param[in] neighbour_cell Cell in neighbour domain.
    inline void
    add(Cell* in_cell,
        Cell* neighbour_cell)
    {
        pairs.push_back(pair<Cell*, Cell*> { in_cell, neighbour_cell });
    }

    // Print boundary.
    void
    print(ostream& os = cout);

    // Print in all processes.
    void
    print_all(ostream& os = cout);
};

/// @}

}

#endif // !MESH_BOUNDARY_H
