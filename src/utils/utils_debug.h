/// \file
/// \brief Debug functions declaration.

#ifndef UTILS_DEBUG_H
#define UTILS_DEBUG_H

#include "utils_includes.h"

namespace utils
{

/// \addtogroup utils
/// @{

#ifdef DEBUG
#define DEBUG_ERROR(S) \
    utils::debug_error(S, __FILE__, __LINE__)
#else // !DEBUG
#define DEBUG_ERROR(S)
#endif // DEBUG

// Debug function.
void
debug_error(const string& s,
            const string& file,
            int line);

/// @}

}

#endif // UTILS_DEBUG_H
