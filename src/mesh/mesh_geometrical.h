/// \file
/// \brief Object with geometry.
///
/// Object with geometry.
/// Object support three methods:
///   calc_geometry - calculate current geometry,
///   save_geometry - save current geometry to original,
///   restore_geometry - restore original geometry to current.
/// Original geometry is calculated only once.

#ifndef CAESAR_MESH_GEOMETRICAL_H
#define CAESAR_MESH_GEOMETRICAL_H

namespace caesar
{

namespace mesh
{

/// \addtogroup mesh
/// @{

/// \brief Geometrical class.
///
/// Class that holds original and current geometry.
class Geometrical
{

public:

    /// \brief Default destructor.
    ///
    /// Destructor.
    virtual
    ~Geometrical()
    {
    }

    /// \brief Calculate geometry.
    ///
    /// Calculate current geometry.
    virtual void
    calc_geometry() = 0;

    /// \brief Save geometry.
    ///
    /// Save current geometry to original.
    virtual void
    save_geometry() = 0;

    /// \brief Restore geometry.
    ///
    /// Restore geometry from original.
    virtual void
    restore_geometry() = 0;
};

/// @}

}

}

#endif // !CAESAR_MESH_GEOMETRICAL_H
