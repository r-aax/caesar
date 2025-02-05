# caesar

1. Necessary packages.

Main functionality.

`sudo apt install libeigen3-dev` (for eigenvalues and eigenvectors)

Tests.

`sudo apt install catch2 ` (for unit-tests)

Documentation.

`sudo apt install doxygen` (for making documentation)

`sudo apt install texlive-full` (for making formulas for documentation)

`sudo apt install graphviz` (for generating drawings for documentation)

2. Additional flags for make.

Enable flags.

`-DCOMPILE_ENABLE_MPI` (make with MPI support)

Disable flags.

`-DCOMPILE_DISABLE_EIGEN` (make without Eigen library included)
