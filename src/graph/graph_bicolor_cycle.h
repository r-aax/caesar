/// \file
/// \brief Bicolor cycle declaration.
///
/// Declaration of bicolor cycle - cycle consists of edges colored with 2 colors.

#ifndef CAESAR_GRAPH_BICOLOR_CYCLE_H
#define CAESAR_GRAPH_BICOLOR_CYCLE_H

#include <vector>
#include <set>

#include "graph_edge.h"

using namespace std;

namespace caesar
{

namespace graph
{

/// \addtogroup graph
/// @{

/// \brief Cycle with edges of two colors without color coflict edges.
///
/// Cycle has no two adjacent edges of the same color.
class BicolorCycle
{

private:

    /// \brief Vector of edges.
    vector<Edge*> edges;

    /// \brief Set of identifiers.
    set<int> ids;

public:

    // Default constructor.
    BicolorCycle();

    // Default destructor.
    ~BicolorCycle();

    // Print function.
    friend ostream&
    operator<<(ostream& os,
               const BicolorCycle& bc);

    //
    // Basic properties.
    //

    /// \brief Length of the cicle.
    ///
    /// Length.
    ///
    /// \return
    /// Length.
    inline size_t
    len()
    {
        return edges.size();
    }

    /// \brief Sum of colors.
    ///
    /// Get sum of colors.
    ///
    /// \return
    /// Sum of colors.
    inline int
    sum_colors() const
    {
        return edges[0]->get_color() + edges[1]->get_color();
    }

    //
    // Build cycle.
    //

    // Build cycle.
    void
    build(Edge* start_edge,
          int another_color);

    /// \brief Check if edge is in cycle.
    ///
    /// Check if edge is in cycle.
    ///
    /// \param[in] e Edge.
    ///
    /// \return
    /// true - if edge is in cycle,
    /// false - otherwise.
    inline bool
    has(const Edge* e) const
    {
        return ids.find(e->get_id()) != ids.end();
    }

    // Switch colors.
    void
    switch_colors();

    // Switch colors between two edges.
    void
    switch_colors(const Edge* e1,
                  const Edge* e2);
};

/// @}

}

}

#endif // !CAESAR_GRAPH_BICOLOR_CYCLE_H
