/// \file
/// \brief Python generator declaration.
///
/// Class for generating code for python.

#ifndef CAESAR_TOOLS_PYTHON_GENERATOR_H
#define CAESAR_TOOLS_PYTHON_GENERATOR_H

#include <iostream>
#include <vector>

#include "graph/graph.h"
#include "mth/mth.h"

namespace caesar
{

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
                          mth::Segment segment,
                          int n = 300,
                          ostream& os = cout);

    // Generate code for graph visualization.
    static void
    graph_visualization(graph::Graph* g,
                        ostream& os = cout);
};

/// @}

}

}

#endif // !CAESAR_TOOLS_PYTHON_GENERATOR_H
