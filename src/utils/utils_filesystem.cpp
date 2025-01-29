/// \file
/// \brief Functions for filesystem.
///
/// Implementation of functions for work with files, directories and filenames.

#include "utils_filesystem.h"

#include <iostream>

#include "diag/diag.h"

namespace caesar {

namespace utils {

/// \addtogroup utils
/// @{

/// \brief Stem of filename.
///
/// Stem of filename (base name, without direcrory and extension).
///
/// \param[in] s Input string.
///
/// \return
/// Stem.
string
filename_stem(const string& s)
{
    CHECK_ERROR(s != "", "zero string in filename_stem")
    CHECK_ERROR((s.back() != '/') && (s.back() != '\\'), "wrong end symbol in filename")

    auto n { s.size() };
    auto slash_pos { n }, dot_pos { n };

    for (auto i { n - 1 }; ; --i)
    {
        if (i == 0)
        {
            // begin of the string
            break;
        }

        if ((s[i] == '.') && (dot_pos == n))
        {
            dot_pos = i;
        }

        if ((s[i] == '/') || (s[i] == '\\'))
        {
            slash_pos = i;

            // slash is found
            break;
        }
    }

    if (slash_pos == n)
    {
        if (dot_pos == n)
        {
            // filename is stem itself
            return s;
        }
        else
        {
            // filename has only extension
            return s.substr(0, dot_pos);
        }
    }
    else
    {
        if (dot_pos == n)
        {
            // no extension
            return s.substr(slash_pos + 1);
        }
        else
        {
            DEBUG_CHECK_ERROR(dot_pos > slash_pos,
                              "dot position must be greater than slash position");

            // common case
            return s.substr(slash_pos + 1, dot_pos - slash_pos - 1);
        }
    }
}

/// @}

}

}
