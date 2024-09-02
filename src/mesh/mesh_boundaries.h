/// \file
/// \brief Boundaries between domains.
///
/// Boundaries between domains declaration.

#ifndef CAESAR_MESH_BOUNDARIES_H
#define CAESAR_MESH_BOUNDARIES_H

#include "mesh_boundary.h"
#include "parl/parl.h"

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Boundaries.
class Boundaries
{

private:

    /// \brief Vector of boundaries.
    vector<Boundary> boundaries;

    /// \brief Comminicator.
    parl::AllToAllExchanger comm;

public:

    // Default constructor.
    Boundaries();

    // Default destructor.
    ~Boundaries();

    // Allocate boundaries.
    void
    allocate();

    /// \brief Add pair of cells into boundaries.
    ///
    /// Add pair of cell into boundaries.
    ///
    /// \param[in] neighbour_domain Neighbour domain.
    /// \param[in] in_cell          Cell in current domain.
    /// \param[in] neighbour_cell   Cell in neighbour domain.
    inline void
    add(size_t neighbour_domain,
        Cell* in_cell,
        Cell* neighbour_cell)
    {
        boundaries[neighbour_domain].add(in_cell, neighbour_cell);
    }

    // Print in current process.
    void
    print(ostream& os = cout);

    // Print in all processes.
    void
    print_all(ostream& os = cout);

    // Set buffers sizes.
    void
    set_buffers_sizes();

    /// \brief Write data to buffers.
    ///
    /// Write data to buffers.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] index Index of element.
    template<typename TData>
    void
    write_to_buffers(int index)
    {
        size_t s = boundaries.size();

        for (size_t i = 0; i < s; ++i)
        {
            vector<double>& buffer = comm.get_out_data(i);

            for (size_t j = 0; j < boundaries[i].size(); ++j)
            {
                buffer[j] = boundaries[i].pairs[j].first->get_element<TData>(index);
            }
        }
    }

    // Exchange.
    void
    exchange();

    /// \brief Read data from buffers.
    ///
    /// Read data from buffers.
    ///
    /// \tparam    TData Type of data.
    /// \param[in] index Index of element.
    template<typename TData>
    void
    read_from_buffers(int index)
    {
        size_t s = boundaries.size();

        for (size_t i = 0; i < s; ++i)
        {
            vector<double>& buffer = comm.get_in_data(i);

            for (size_t j = 0; j < boundaries[i].size(); ++j)
            {
                boundaries[i].pairs[j].second->set_element<TData>(index, buffer[j]);
            }
        }
    }
};

/// @}

}

}

#endif // !CAESAR_MESH_BOUNDARIES_H
