/// \file
/// \brief Mapper class for support correspondence of string names and enum names.
///
/// Mapper for hold coherency between strings and enums.

#ifndef CAESAR_UTILS_MAPPER_H
#define CAESAR_UTILS_MAPPER_H

#include <vector>
#include <map>
#include <limits>

#include "diag/diag.h"

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

/// \brief Mapper class.
///
/// \tparam T Type of enumeration.
template <typename T>
class Mapper
{

private:

    /// \brief Object of mapper name.
    std::string what;

    /// \brief Vector of names.
    std::vector<std::string> names;

    /// \brief Low index of enum.
    size_t lo;

    /// \brief High index of enum.
    size_t hi;

    /// \brief Map of names and numbers.
    std::map<std::string, T> m;

public:

    /// \brief Constructor by list of names.
    ///
    /// Constructor by vector of names.
    ///
    /// \param[in] what_  Object name.
    /// \param[in] names_ Names vector.
    Mapper(std::string what_,
           std::vector<std::string> names_)
        : what { what_ },
          names { names_ },
          lo { static_cast<size_t>(T::First) },
          hi { static_cast<size_t>(T::Last) }
    {
        // Names count.
        size_t n { names.size() };

        CHECK_ERROR(n == (hi - lo + 1), "wrong number of names in mapper " + what);

        // Create map.
        for (size_t i { 0 }; i < n; ++i)
        {
            m[names[i]] = static_cast<T>(i + lo);
        }
    }

    /// \brief Destructor.
    ///
    /// Default destructor.
    ~Mapper()
    {
    }

    /// \brief Get name by enumeration.
    ///
    /// We suppose numeration starts from 0 and without gaps.
    ///
    /// \param[in] e Enumeration.
    ///
    /// \return
    /// Name.
    inline const std::string&
    name(T e) const
    {
        return names[static_cast<size_t>(e) - lo];
    }

    /// \brief Get string representation.
    ///
    /// Get string representation.
    ///
    /// \param[in] e Enumeration.
    ///
    /// \return
    /// String representation.
    inline const std::string
    repr(T e) const
    {
        return name(e) + " (" + std::to_string(static_cast<int>(e)) + ")";
    }

    /// \brief Try to find name.
    ///
    /// Try to find name.
    ///
    /// \param[in] name Name.
    ///
    /// \return
    /// true - if mapper has name,
    /// false - otherwise.
    inline bool
    has(const std::string& name) const
    {
        return m.find(name) != m.end();
    }

    /// \brief Get enum.
    ///
    /// Get enum from map.
    ///
    /// \param[in] name Name.
    ///
    /// \return
    /// Enumeration.
    T
    num(const std::string& name) const
    {
        if (has(name))
        {
            return m.find(name)->second;
        }
        else
        {
            CAESAR_ERROR("unknown " + what + " " + name);

            // We have to return value not corresponded with any name.
            return static_cast<T>(static_cast<int>(T::Last) + 1);
        }
    }

    /// \brief Append all names to vector.
    ///
    /// Append names to the end of given vector.
    ///
    /// \param[out] v Target vector.
    void
    append_names_to(std::vector<std::string>& v)
    {
        for (std::string& name : names)
        {
            v.push_back(name);
        }
    }

    /// \brief Get string with all possible names.
    ///
    /// Get string with all possible names.
    ///
    /// \return
    /// String with all possible names.
    std::string
    all_names_string() const
    {
        std::string s { names[0] };

        for (size_t i { 1 }; i < names.size(); ++i)
        {
            s = s + "," + names[i];
        }

        return s;
    }
};

/// @}

}

}

#endif // !CAESAR_UTILS_MAPPER_H
