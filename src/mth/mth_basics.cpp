///
/// @file
/// @brief Реализация математических примитивов.
///

#include "mth_basics.h"

#include <iostream>
#include <cassert>
#include <cmath>

namespace mth
{

/// @addtogroup mth
/// @{

/// @brief Применение теоремы Пифагора в трехмерном случае.
///
/// @param [in] a - Расстояние вдоль оси <c>OX</c>.
/// @param [in] b - Расстояние вдоль оси <c>OY</c>.
/// @param [in] c - Расстояние вдоль оси <c>OZ</c>.
///
/// @return
/// Длина гипотенузы.
double
pyth(double a,
     double b,
     double c)
{
    return sqrt(a * a + b * b + c * c);
}

/// @}

}
