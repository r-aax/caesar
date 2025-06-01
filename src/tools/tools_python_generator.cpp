/// \file
/// \brief Python generator implementation.
///
/// Python generator for generate python code.

#include "tools_python_generator.h"

namespace caesar
{

namespace tools
{

/// \addtogroup tools
/// @{

/// \brief Begin generated code.
///
/// Output text before generated code.
///
/// \param[out] os Out stream.
void
PythonGenerator::begin(ostream& os)
{
    os << "# --------------------------------------------------------------------------------------" << endl;
    os << "# This code is generated from crys for running in Jupiter Notebook." << endl;
    os << endl;
}

/// \brief End generated code.
///
/// Output text after generated code.
///
/// \param[out] os Out stream.
void
PythonGenerator::end(ostream& os)
{
    os << "# End of code generated from crys." << endl;
    os << "# --------------------------------------------------------------------------------------" << endl;
}

/// \brief Generate simple chart for function.
///
/// Generate code for python for drawing function xs -> ys chart.
///
/// \param[in]  xs Vector of X values.
/// \param[in]  ys Vector of Y values.
/// \param[out] os Out stream.
void
PythonGenerator::simple_function_chart(const vector<double>& xs,
                                       const vector<double>& ys,
                                       ostream& os)
{
    size_t n { xs.size() };

    DEBUG_CHECK_ERROR(ys.size() == n, "can not construct function chart, ys size doesn't math xs size");

    begin();

    os << "from matplotlib import pyplot as plt" << endl;
    os << endl;

    // xs array.
    os << "xs = [";
    for (size_t i = 0; i < n - 1; ++i)
    {
        os << xs[i] << ", ";
    }
    os << xs[n - 1] << "]" << endl;

    // ys array.
    os << "ys = [";
    for (size_t i = 0; i < n - 1; ++i)
    {
        os << ys[i] << ", ";
    }
    os << ys[n - 1] << "]" << endl;

    os << endl;
    os << "plt.plot(xs, ys)" << endl;
    os << "plt.show()" << endl;
    os << endl;

    end();
}

/// \brief Generate simple chart for function.
///
/// Generate chart for function.
///
/// \param[in] f       Function.
/// \param[in] data    Data.
/// \param[in] segment Segment.
/// \param[in] n       Count of pieces of definition scope [lo, hi].
/// \param[in] os      Out stream.
void
PythonGenerator::simple_function_chart(double (*f)(double, void *),
                                       void *data,
                                       mth::Segment segment,
                                       int n,
                                       ostream& os)
{
    vector<double> xs;
    vector<double> ys;
    double lo { segment.lo() };
    double hi { segment.hi() };
    double dx { (hi - lo) / n };

    DEBUG_CHECK_ERROR(lo < hi, "wrong function definition scope segment");

    for (int i = 0; i <= n; ++i)
    {
        double x { lo + i * dx };
        double y { f(x, data) };

        xs.push_back(x);
        ys.push_back(y);
    }

    PythonGenerator::simple_function_chart(xs, ys, os);
}

/// \brief Generate code for graph visualization.
///
/// Python code for graph visualization.
///
/// \param[in] g  Graph.
/// \param[in] os Out stream.
void
PythonGenerator::graph_visualization(graph::Graph* g,
                                     ostream& os)
{
    static string colors[] { "red", "blue", "green", "magenta", "yellow" };
    size_t vc { g->vertices_count() }, ec { g->edges_count() };

    begin();

    os << "import networkx as nx" << endl;
    os << "import matplotlib.pyplot as plt" << endl;
    os << endl;
    os << "g = nx.Graph()" << endl << endl;

    // Vectors of nodes and edges.
    const vector<graph::Vertex*> vertices = g->get_vertices();
    const vector<graph::Edge*> edges = g->get_edges();

    // Add nodes.
    for (size_t i = 0; i < vc; ++i)
    {
        graph::Vertex* v { g->get_vertex(i) };

        os << "g.add_node(" << v->get_id() << ")" << endl;
    }

    os << endl;

    // Add egdes.
    for (size_t i = 0; i < ec; ++i)
    {
        graph::Edge* e { g->get_edge(i) };

        os << "g.add_edge(" << e->get_a()->get_id()
           << ", " << e->get_b()->get_id()
           << ", color='" << colors[e->get_color()]
           << "')" << endl;
    }

    // Draw.
    os << endl;
    os << "_, edge_colors=zip(*nx.get_edge_attributes(g, 'color').items())" << endl;
    os << "plt.figure(1, figsize=(8, 8))" << endl;
    // Use edge_cmap=plt.cm.plasma if colors are set by numbers.
    os << "nx.draw(g, with_labels=True, font_size=8, font_color='white', "
       << "node_size=180, node_color='black', edge_color=edge_colors, width=4)" << endl;
    os << "plt.show()" << endl;

    end();
}

/// @}

}

}
