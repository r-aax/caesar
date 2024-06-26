/// \file
/// \brief Debug functions implementation.

#include "utils_debug.h"

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Trace function.
///
/// Say trace message.
///
/// \param[in] s    Message string.
/// \param[in] file File where error occured.
/// \param[in] line Line where error occured.
void
say_trace(const string& s,
          const string& file,
          int line)
{
    cout << "Trace : " << s << " (" << file << ", " << line << ")" << endl;
}

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

/// \brief Debug error function.
///
/// Say error and exit.
///
/// \param[in] s    Message string.
/// \param[in] file File where error occured.
/// \param[in] line Line where error occured.
void
say_error(const string& s,
          const string& file,
          int line)
{
    if (file == "")
    {
        cout << "Error : " << s << endl;
    }
    else
    {
        cout << "Error : " << s << " (" << file << ", " << line << ")" << endl;
    }
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
    say_error(s, file, line);

    throw runtime_error("error");
}

/// @}

}
