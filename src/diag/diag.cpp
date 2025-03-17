/// \file
/// \brief Diagnostics functions implementation.
///
/// Diagnostics functions implementation.

#include "diag.h"

#include <iostream>
#include <stdexcept>

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
say_warning(const std::string& s,
            const std::string& file,
            int line)
{
    std::cout << "Warning : " << s << " (" << file << ", " << line << ")" << std::endl;
}

/// \brief Raise error.
///
/// Say error and raise exception.
///
/// \param[in] s    Message.
/// \param[in] file Name of file.
/// \param[in] line Line of file.
void
raise_error(const std::string& s,
            const std::string& file,
            int line)
{
    std::cout << "Error : " << s << " (" << file << ", " << line << ")" << std::endl;

    throw std::runtime_error("error");
}

/// @}

}

}
