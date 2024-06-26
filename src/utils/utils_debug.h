/// \file
/// \brief Debug functions declaration.

#ifndef UTILS_DEBUG_H
#define UTILS_DEBUG_H

#include "includes.h"

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Trace message.
///
/// Trace messgae.
///
/// \param[in] S Message.
#define TRACE(S) utils::say_trace(S, __FILE__, __LINE__)

/// \brief Warning message.
///
/// Warning message.
///
/// \param[in] S Message.
#define WARNING(S) utils::say_warning(S, __FILE__, __LINE__)

/// \brief Error message.
///
/// Error message.
///
/// \param[in] S Message.
#define ERROR(S) utils::say_error(S, __FILE__, __LINE__)

/// \brief Warning message.
///
/// Warning message.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition is not satisfied.
#define CHECK_WARNING(C, S) \
    if (!(C)) \
    { \
        WARNING(S); \
    }

/// \brief Error message.
///
/// Error message.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition is not satisfied.
#define CHECK_ERROR(C, S) \
    if (!(C)) \
    { \
        ERROR(S); \
    }

#ifdef DEBUG
/// \brief Debug error message.
///
/// Error message and finish terminate application.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition is not satisfied.
#define DEBUG_ERROR(S) utils::raise_error(S, __FILE__, __LINE__)
#else // !DEBUG
/// \brief Debug error message.
///
/// Error message and finish terminate application.
///
/// \param[in] S Message.
#define DEBUG_ERROR(S)
#endif // DEBUG

#ifdef DEBUG
/// \brief Debug error message.
///
/// Error message and finish terminate application.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition is not satisfied.
#define DEBUG_CHECK_ERROR(C, S) \
    if (!(C)) \
    { \
        DEBUG_ERROR(S); \
    }
#else // !DEBUG
/// \brief Debug error message.
///
/// Error message and finish terminate application.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition is not satisfied.
#define DEBUG_CHECK_ERROR(C, S)
#endif // DEBUG

#ifdef DEBUG
/// \brief Debug error message for not implemented code.
#define DEBUG_NOT_IMPLEMENTED DEBUG_CHECK_ERROR(false, "not implemented")
#else // !DEBUG
/// \brief Debug error message for not implemented code.
#define DEBUG_NOT_IMPLEMENTED
#endif // DEBUG

// Trace function.
void
say_trace(const string& s,
          const string& file,
          int line);

// Warning function.
void
say_warning(const string& s,
            const string& file,
            int line);

// Debug function.
void
say_error(const string& s,
          const string& file = "",
          int line = 0);

// Raise error.
void
raise_error(const string& s,
            const string& file,
            int line);

/// @}

}

#endif // !UTILS_DEBUG_H
