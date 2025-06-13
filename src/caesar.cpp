/// \file
/// \brief Main module.
///
/// Main module.

#include "caesar.h"

using namespace std;
using namespace caesar;

/// \brief Test parl.
///
/// Test parl module.
///
/// \param[in] argc Number of arguments.
/// \param[in] argv Arguments.
void
test_parl(int *argc,
          char ***argv)
{
    parl::mpi_init(argc, argv);

    // parl::Buffer ------------------------------

#if 1

    if (parl::is_mpi_rank_0())
    {
        cout << "[test_parl, buffer, size = " << parl::mpi_size() << "]" << endl;
        cout << "----------" << endl;
    }

    parl::mpi_barrier();

    if (parl::mpi_size() == 2)
    {
        parl::Buffer b(parl::mpi_rank(), 1 - parl::mpi_rank()); // buffer 0 <-> 1

        b.set_size(10);
        b.fill_out_data(static_cast<double>(parl::mpi_rank()), 0.001);
        b.exchange();
        b.print_all();
    }

#endif

    // -------------------------------------------

    parl::mpi_finalize();
}

/// \brief Main function.
///
/// Main function - entry point into application.
///
/// \param[in] argc Number of arguments.
/// \param[in] argv Arguments.
///
/// \return
/// Return code.
int
main(int argc, char** argv)
{
    test_parl(&argc, &argv);

    return 0;
}
