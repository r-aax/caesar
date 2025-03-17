/// \file
/// \brief Diagnostics functions and macroses.
///
/// Diagnostic functions and macroses.

#ifndef CAESAR_DIAG_H
#define CAESAR_DIAG_H

#include <string>

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
/// We can not use name ERROR, it conflicts with wingdi.h in windows.
///
/// \param[in] S Message.
#define CAESAR_ERROR(S) diag::raise_error(S, __FILE__, __LINE__)

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
        CAESAR_ERROR(S); \
    }

/// \brief Error message for not implemented code.
///
/// Error message for not implemented code.
#define NOT_IMPLEMENTED CAESAR_ERROR("not implemented")

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
#define DEBUG_ERROR(S) CAESAR_ERROR(S)

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
say_warning(const std::string& s,
            const std::string& file,
            int line);

// Raise error.
void
raise_error(const std::string& s,
            const std::string& file,
            int line);

/// @}

}

}

#endif // !CAESAR_DIAG_H
