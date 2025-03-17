/// \file
/// \brief Functions for filesystem.
///
/// Implementation of functions for work with files, directories and filenames.

#include "utils_filesystem.h"

#include <iostream>
#include <fstream>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else // !_WIN32
#include <sys/stat.h>
#endif // _WIN32

#include "diag/diag.h"

namespace caesar
{

namespace utils
{

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
std::string
filename_stem(const std::string& s)
{
    if (s == "")
    {
        return "";
    }

    CHECK_ERROR((s.back() != '/') && (s.back() != '\\'), "wrong end symbol in filename")

    size_t n { s.size() };
    size_t slash_pos { n }, dot_pos { n };

    for (size_t i { n - 1 }; ; --i)
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

/// \brief Check is there a file with given name.
///
/// Check is there a file with given name.
///
/// \param[in] fn Name of file.
///
/// \return
/// true - if there is a file,
/// false - otherwise.
bool
exists_file(const std::string& fn)
{
    std::ifstream s(fn);

    return s.is_open();
}

/// \brief Check is there a directory with given name.
///
/// Check is there a directory with given name.
///
/// source:
/// https://www.geeksforgeeks.org/how-to-check-a-file-or-directory-exists-in-cpp/
/// 
/// \param[in] dn Name of directory.
///
/// \return
/// true - if there is a directory,
/// false - otherwise.
bool
exists_directory(const std::string& dn)
{
    struct stat sb;

    return stat(dn.c_str(), &sb) == 0;
}

/// \brief Create directory.
///
/// Create directory.
///
/// \param[in] dn Directory name.
///
/// \return
/// true - if directory is created,
/// false - otherwise.
bool
create_directory(const std::string& dn)
{
    int status{ false };

#ifdef _WIN32
    status = CreateDirectoryA(dn.c_str(), NULL);
#else // !_WIN32
    status = mkdir(dn.c_str(), 0777)
#endif // _WIN32

    return status == 0;
}

/// \brief Create directories.
///
/// Create directories (with nesting of any level).
///
/// \param[in] dn Name of directory.
///
/// \return
/// true - if directory is built,
/// false - otherwise.
bool
create_directories(const std::string& dn)
{
    size_t n { dn.size() };
    bool is_created { false };

    if (n == 0)
    {
        return is_created;
    }

    for (size_t i { 0 }; i < n; ++i)
    {
        if ((dn[i] == '/') || (dn[i] == '\\'))
        {
            is_created = create_directory(dn.substr(0, i));
        }
    }

    if ((dn.back() != '/') && (dn.back() != '\\'))
    {
        is_created = create_directory(dn);
    }

    return is_created;
}

/// @}

}

}
