/// \file
/// \brief System utilities implementation.
///
/// System utilities implementation.

#include "utils_system.h"

#include <fstream>
#include <sys/stat.h>

using namespace std;

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Hash function for double.
///
/// Hash function is just unsigned 64-bit int representation.
///
/// \param[in] x Double number.
///
/// \return
/// Hash value.
uint64_t
double_hash(double x)
{
    union
    {
        double d;
        uint64_t i;
    }
    u;

    u.d = x;

    return u.i;
}

/// \brief Check if file exists.
///
/// Check if file exists.
///
/// \param[in] fn File name.
///
/// \return
/// true - if file exists,
/// false - otherwise.
bool
is_file_exist(string fn)
{
    bool is_exist { false };

    ifstream f(fn.c_str());

    if (f.is_open())
    {
        is_exist = true;
    }

    f.close();

    return is_exist;
}

/// \brief Check if directory exists.
///
/// Check if directory exists.
///
/// \param[in] dn Directoty name.
///
/// \return
/// true - if directory exists,
/// false - otherwise.
bool
is_directory_exist(string dn)
{
    const char* dir { dn.c_str() };
    struct stat sb;

    return stat(dir, &sb) == 0;
}

/// @}

}

}
