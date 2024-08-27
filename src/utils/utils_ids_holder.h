/// \file
/// \brief Object with id and loc_id.
///
/// Object with id and loc_id.

#ifndef CAESAR_UTILS_IDS_HOLDER_H
#define CAESAR_UTILS_IDS_HOLDER_H

#include <string>

using namespace std;

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

class IdsHolder
{

private:

    /// \brief Identifier.
    int id { -1 };

    /// \brief Local identifer.
    int loc_id { -1 };

public:

    //
    // Getters.
    //

    /// \brief Get identifier.
    ///
    /// Get identifier.
    ///
    /// \return
    /// Identifier.
    inline int
    get_id() const
    {
        return id;
    }

    /// \brief Get local identifier
    ///
    /// Get local identifier.
    ///
    /// \return
    /// Local identifier.
    inline int
    get_loc_id() const
    {
        return loc_id;
    }

    //
    // Setters.
    //

    /// \brief Set identifier.
    ///
    /// Set identifier.
    ///
    /// \param[in] id_ Identifier.
    inline void
    set_id(int id_)
    {
        id = id_;
    }

    /// \brief Set local identifier.
    ///
    /// Set local identifier.
    ///
    /// \param[in] loc_id_ Identifier.
    inline void
    set_loc_id(int loc_id_)
    {
        loc_id = loc_id_;
    }

    //
    // Get string.
    //

    /// \brief Get string with identifiers.
    ///
    /// Get string with identifiers.
    ///
    /// \return
    /// String with identifiers.
    inline string
    get_ids_string() const
    {
        return to_string(id) + "/" + to_string(loc_id);
    }
};

/// @}

}

}

#endif // !CAESAR_UTILS_ID_HOLDER_H
