/// \file
/// \brief Variable with two points.
///
/// Variable with two points.

#ifndef PDE_VAR_2P_H
#define PDE_VAR_2P_H

namespace caesar
{

namespace pde
{

/// \addtogroup pde
/// @{

/// \brief Variable with 2 points.
///
/// Variable holds two values: present and previous.
class Var2P
{

private:

    /// \brief Present value.
    ///
    /// Present value (now, new).
    double n { 0.0 };

    /// \brief Previous value.
    ///
    /// Previous value.
    double p { 0.0 };

public:

    /// \brief Get value.
    ///
    /// Get present value.
    ///
    /// \return
    /// Present value.
    inline double
    get() const
    {
        return n;
    }

    /// \brief Get previous value.
    ///
    /// Get previous value.
    ///
    /// \return
    /// Previous value.
    inline double
    prev() const
    {
        return p;
    }

    /// \brief Set new present value.
    ///
    /// Set new present value.
    ///
    /// \param[in] v Value.
    inline void
    set(double v)
    {
        n = v;
    }

    /// \brief Get difference.
    ///
    /// Difference.
    ///
    /// \return
    /// Difference.
    inline double
    diff() const
    {
        return n - p;
    }

    /// \brief Save present value.
    ///
    /// Save present value.
    inline void
    save()
    {
        p = n;
    }

    /// \brief Roll back to previous value.
    ///
    /// Roll back to previous value.
    inline void
    back()
    {
        n = p;
    }

    /// \brief Dirrefence for mult of two vars.
    ///
    /// Difference of mul.
    ///
    /// \param[in] a First variable.
    /// \param[in] b Second variable.
    ///
    /// \return
    /// Difference of mul.
    static inline double
    mul_diff(const Var2P& a,
             const Var2P& b)
    {
        return a.get() * b.get() - a.prev() * b.prev();
    }
};

/// @}

}

}

#endif // !PDE_VAR_2P_H
