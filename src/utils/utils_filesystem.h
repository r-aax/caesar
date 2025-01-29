/// \file
/// \brief Filesystem.
///
/// Functions for work with files, directories, filenames.

#ifndef CAESAR_FILESYSTEM_H
#define CAESAR_FILESYSTEM_H

#include <string>

using namespace std;

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

// Stem of filename.
string
filename_stem(const string& s);

// Check is there a file with given name.
bool
exists_file(const string& fn);

// Check is there a directory with given name.
bool
exists_directory(const string& dn);

// Create directory.
bool
create_directory(const string& dn);

// Create directories.
bool
create_directories(const string& dn);

/// @}

}

}

#endif // !CAESAR_FILESYSTEM_H
