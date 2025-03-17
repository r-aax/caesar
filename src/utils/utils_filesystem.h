/// \file
/// \brief Filesystem.
///
/// Functions for work with files, directories, filenames.

#ifndef CAESAR_FILESYSTEM_H
#define CAESAR_FILESYSTEM_H

#include <string>

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

// Stem of filename.
std::string
filename_stem(const std::string& s);

// Check is there a file with given name.
bool
exists_file(const std::string& fn);

// Check is there a directory with given name.
bool
exists_directory(const std::string& dn);

// Create directory.
bool
create_directory(const std::string& dn);

// Create directories.
bool
create_directories(const std::string& dn);

/// @}

}

}

#endif // !CAESAR_FILESYSTEM_H
