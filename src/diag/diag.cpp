/// \file
/// \brief Diagnostics functions implementation.
///
/// Diagnostics functions implementation.

#include "diag.h"

#include <iostream>

namespace caesar
{

namespace diag
{

/// \addtogroup diag
/// @{

/// \brief Warning message.
///
/// Say warning message.
///
/// \param[in] s    Message string.
/// \param[in] file File where error occured.
/// \param[in] line Line where error occured.
void
say_warning(const string& s,
            const string& file,
            int line)
{
    cout << "Warning : " << s << " (" << file << ", " << line << ")" << endl;
}

/// \brief Raise error.
///
/// Say error and raise exception.
///
/// \param[in] s    Message.
/// \param[in] file Name of file.
/// \param[in] line Line of file.
void
raise_error(const string& s,
            const string& file,
            int line)
{
    cout << "Error : " << s << " (" << file << ", " << line << ")" << endl;

    throw runtime_error("error");
}

/// @}

}

}
