/// \file
/// \brief Debug functions implementation.

#include "utils_debug.h"

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Debug error function.
///
/// Say error and exit.
///
/// \param[in] s    Message string.
/// \param[in] file File where error occured.
/// \param[in] line Line where error occured.
void
debug_error(const string& s,
            const string& file,
            int line)
{
    cout << "Error : " << s << " (" << file << ", " << line << ")" << endl;

    throw runtime_error("error");
}

/// @}

}
