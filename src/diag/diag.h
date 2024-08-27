/// \file
/// \brief Diagnostics functions and macroses.
///
/// Diagnostic functions and macroses.

#ifndef CAESAR_DIAG_H
#define CAESAR_DIAG_H

#include <string>

using namespace std;

namespace caesar
{

namespace diag
{

/// \addtogroup diag
/// @{

/// \brief Warning message.
///
/// Warning message.
///
/// \param[in] S Message.
#define WARNING(S) diag::say_warning(S, __FILE__, __LINE__)

/// \brief Error.
///
/// Raising error.
///
/// \param[in] S Message.
#define ERROR(S) diag::raise_error(S, __FILE__, __LINE__)

/// \brief Warning message with check.
///
/// Warning message with check.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition is not satisfied.
#define CHECK_WARNING(C, S) \
    if (!(C)) \
    { \
        WARNING(S); \
    }

/// \brief Error with check.
///
/// Raising error if check is failed.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition does not hold.
#define CHECK_ERROR(C, S) \
    if (!(C)) \
    { \
        ERROR(S); \
    }

#ifdef DEBUG

/// \brief Debug warning message.
///
/// Debug warning message.
///
/// \param[in] S Message.
#define DEBUG_WARNING(S) WARNING(S)

/// \brief Debug error.
///
/// Debug raising error.
///
/// \param[in] S Message.
#define DEBUG_ERROR(S) ERROR(S)

/// \brief Debug warning message with check.
///
/// Debug warning message with check.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition is not satisfied.
#define DEBUG_CHECK_WARNING(C, S) CHECK_WARNING(C, S)

/// \brief Debug error with check.
///
/// Debug raising error if check is failed.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition does not hold.
#define DEBUG_CHECK_ERROR(C, S) CHECK_ERROR(C, S)

/// \brief Debug error message for not implemented code.
///
/// Debug error message for not implemented code.
#define DEBUG_NOT_IMPLEMENTED DEBUG_ERROR("not implemented")

#else // !DEBUG

/// \brief Debug warning message.
///
/// Debug warning message.
///
/// \param[in] S Message.
#define DEBUG_WARNING(S)

/// \brief Debug error.
///
/// Debug raising error.
///
/// \param[in] S Message.
#define DEBUG_ERROR(S)

/// \brief Debug warning message with check.
///
/// Debug warning message with check.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition is not satisfied.
#define DEBUG_CHECK_WARNING(C, S)

/// \brief Debug error with check.
///
/// Debug raising error if check is failed.
///
/// \param[in] C Condition.
/// \param[in] S Message if condition does not hold.
#define DEBUG_CHECK_ERROR(C, S)

/// \brief Debug error message for not implemented code.
///
/// Debug error message for not implemented code.
#define DEBUG_NOT_IMPLEMENTED

#endif // DEBUG

// Warning function.
void
say_warning(const string& s,
            const string& file,
            int line);

// Raise error.
void
raise_error(const string& s,
            const string& file,
            int line);

/// @}

}

}

#endif // !CAESAR_DIAG_H
