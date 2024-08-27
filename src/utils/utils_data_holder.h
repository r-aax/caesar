/// \file
/// \brief Data holder imlementation.
///
/// Data holder implementation.

#ifndef CAESAR_UTILS_DATA_HOLDER_H
#define CAESAR_UTILS_DATA_HOLDER_H

#include "diag/diag.h"

namespace caesar
{

namespace utils
{

/// \addtogroup utils
/// @{

class DataHolder
{

private:

    /// \brief User data.
    void* data_ { nullptr };

public:

    /// \brief Default constructor.
    ///
    /// Default constructor.
    DataHolder()
    {
    }

    /// \brief Default destructor.
    ///
    /// Default destructor.
    ~DataHolder()
    {
        DEBUG_CHECK_ERROR(data_ == nullptr, "data leak from utils::DataHolder");
    }

    /// \brief Allocate memory for data.
    ///
    /// Allocate memory for data.
    ///
    /// \tparam T Type of allocated object.
    template<typename T>
    void
    allocate_data()
    {
        T* d { new T() };

        DEBUG_CHECK_ERROR(data_ == nullptr, "double allocation of data");

        data_ = static_cast<void*>(d);
    }

    /// \brief Allocate memory for data if it is null.
    ///
    /// Allocate memory if it is null.
    ///
    /// \tparam T Type of object.
    template<typename T>
    void
    allocate_data_if_null()
    {
        if (data_ == nullptr)
        {
            allocate_data<T>();
        }
    }

    /// \brief Free data.
    ///
    /// Free memory used by data.
    ///
    /// \tparam T Type of data.
    template<typename T>
    void
    free_data()
    {
        T* d { static_cast<T*>(data_) };

        DEBUG_CHECK_ERROR(data_ != nullptr, "try to free null data");

        delete d;

        data_ = nullptr;
    }

    /// \brief Free data if not null.
    ///
    /// Free data if not null.
    ///
    /// \tparam T Type of data.
    template<typename T>
    void
    free_data_if_not_null()
    {
        if (data_ != nullptr)
        {
            free_data<T>();
        }
    }

    /// \brief Get data.
    ///
    /// Get data.
    ///
    /// \tparam T Typpe of data.
    ///
    /// \return
    /// Data.
    template<typename T>
    T*
    get_data() const
    {
        DEBUG_CHECK_ERROR(data_ != nullptr, "try to get null data");

        T* d { static_cast<T*>(data_) };

        return d;
    }
};

/// @}

}

}

#endif // !CAESAR_UTILS_DATA_HOLDER_H
