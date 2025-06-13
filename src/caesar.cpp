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

#if 0

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

    // parl::AllToAllExchanger -------------------

#if 0

    if (parl::is_mpi_rank_0())
    {
        cout << "[test_parl, all_to_all_exchanger, size = " << parl::mpi_size() << "]" << endl;
        cout << "----------" << endl;
    }

    parl::mpi_barrier();

    if (parl::mpi_size() == 3)
    {
        parl::AllToAllExchanger a2a;
        size_t s { parl::mpi_size() };
        size_t r { parl::mpi_rank() };

        a2a.allocate();

        if (r == 0)
        {
            for (size_t i { 0 }; i < s; ++i)
            {
                a2a.set_size(i, 10);
                a2a.buffers[i].fill_out_data(0.0, 0.01);
            }
        }
        else if (r == 1)
        {
            for (size_t i { 0 }; i < s; ++i)
            {
                a2a.set_size(i, 10);
                a2a.buffers[i].fill_out_data(1.0, 0.01);
            }
        }
        else
        {
            for (size_t i { 0 }; i < s; ++i)
            {
                a2a.set_size(i, 10);
                a2a.buffers[i].fill_out_data(2.0, 0.01);
            }
        }

        a2a.exchange();
        a2a.print_all();
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
