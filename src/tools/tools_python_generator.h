/// \file
/// \brief Python generator declaration.
///
/// Class for generating code for python.

#ifndef TOOLS_PYTHON_GENERATOR_H
#define TOOLS_PYTHON_GENERATOR_H

#include <iostream>
#include <vector>

#include "graph/graph.h"

namespace tools
{

/// \addtogroup tools
/// @{

/// \brief Python generator.
class PythonGenerator
{

private:

    // Begin generated code.
    static void
    begin(ostream& os = cout);

    // End generated code.
    static void
    end(ostream& os = cout);

public:

    // Generate simple chart for function.
    static void
    simple_function_chart(const vector<double>& xs,
                          const vector<double>& ys,
                          ostream& os = cout);

    // Generate simple chart for function.
    static void
    simple_function_chart(double (*f)(double, void *),
                          void *data,
                          const vector<double>& segm,
                          int n = 300,
                          ostream& os = cout);

    // Generate code for graph visualization.
    static void
    graph_visualization(graph::Graph* g,
                        ostream& os = cout);
};

/// @}

}

#endif // !TOOLS_PYTHON_GENERATOR_H
