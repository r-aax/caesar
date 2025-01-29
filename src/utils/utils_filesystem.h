/// \file
/// \brief Filesystem.
///
/// Functions for work with files, directories, filenames.

#ifndef CAESAR_FILESYSTEM_H
#define CAESAR_FILESYSTEM_H

#include <string>

using namespace std;

namespace caesar {

namespace utils {

/// \addtogroup utils
/// @{

// Stem of filename.
string
filename_stem(const string& s);

/// @}

}

}

#endif // !CAESAR_FILESYSTEM_H
