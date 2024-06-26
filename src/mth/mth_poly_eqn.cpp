///
/// @file
/// @brief Решение полиномиальных уравнений.
///

#include "mth_poly_eqn.h"
#include "mth_basics.h"

#include <iostream>
#include <complex>
#include <limits>

using namespace std;

namespace mth
{

/// @addtogroup mth
/// @{

/// @brief Поиск вещественных корней квадратного уравнения.
///
/// @param [in] a - Значение параметра при x^2.
/// @param [in] b - Значение параметра при x.
/// @param [in] c - Значение свободного члена.
/// @param [out] roots - Указатель на результаты.
///
/// @return
/// Количество вещественных корней уравнения (от 0 до 2).
/// Корни могут повторяться, это не проверяется.
int
find_real_roots_eq2(double a,
                    double b,
                    double c,
                    double *roots)
{
    if (mth::is_zero(a))
    {
        // Вырожденные уравнения игнорируем.
        return 0;
    }

    double d = b * b - 4.0 * a * c;

    if (d < 0.0)
    {
        return 0;
    }

    double sd = sqrt(d);

    roots[0] = (-b + sd) / (2.0 * a);
    roots[1] = (-b - sd) / (2.0 * a);

    return 2;
}

/// @brief Поиск корней кубического уравнения для нахождения толщины подледной пленки.
/// Берутся только вещественные корни.
///
/// @param [in] a - Значение параметра при x^3.
/// @param [in] b - Значение параметра при x^2.
/// @param [in] c - Значение параметра при x.
/// @param [in] d - Значение свободного члена.
/// @param [out] roots - Указатель на результаты.
/// @param [in] eps_ai_bi_zero - Малая величина для проверки подходящих alfa, beta.
/// @param [in] eps_image - Малая величина для отсечения комплексных корней.
///
/// @return
/// Количество вещественных корней кубического уравнения (от 0 до 3).
/// Корни могут повторяться, это не проверяется.
int
find_real_roots_eq3(double a,
                    double b,
                    double c,
                    double d,
                    double *roots,
                    double eps_ai_bi_zero,
                    double eps_image)
{
    if (mth::is_zero(a))
    {
        return find_real_roots_eq2(b, c, d, roots);
    }

    // Коэффициенты для приведения уравнения.
    double p = (3.0 * a * c - b * b) / (3.0 * a * a);
    double q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);

    // Считаем Q. Сразу создаем комплексное число, так как все равно корень извлекать.
    complex<double> Q(p * p * p / 27.0 + q * q / 4.0, 0.0);
    complex<double> sQ = sqrt(Q);

    // Генерируем альфы и беты.
    complex<double> alfas[3], betas[3];
    complex<double> s(0.0, sqrt(3.0));
    complex<double> pl;

    // Вычисляем альфы и беты.
    pl = -q / 2.0 + sQ;
    alfas[0] = pow(pl, 1.0 / 3.0);
    alfas[1] = alfas[0] * (-1.0 + s) / 2.0;
    alfas[2] = alfas[0] * (-1.0 - s) / 2.0;
    pl = -q / 2.0 - sQ;
    betas[0] = pow(pl, 1.0 / 3.0);
    betas[1] = betas[0] * (-1.0 + s) / 2.0;
    betas[2] = betas[0] * (-1.0 - s) / 2.0;

    // Сопрягаем альфы и беты.
    int root_i = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            complex<double> ch = alfas[i] * betas[j] + p / 3.0;

            if (abs(ch) < eps_ai_bi_zero)
            {
                complex<double> x = alfas[i] + betas[j] - b / (3.0 * a);

                if (abs(imag(x)) < eps_image)
                {
                    roots[root_i] = real(x);
                    root_i++;
                }

                break;
            }
        }
    }

    return root_i;
}

/// @brief Поиск ближайшего корня.
///
/// @param [in] x - Старый корень.
/// @param [in] roots - Корни.
/// @param [in] roots_count - Количество корней.
///
/// @return
/// Новое значение корня.
double
nearest_root(double x,
             double *roots,
             int roots_count)
{
    double cur_r = x;
    double cur_diff = numeric_limits<double>::max();

    for (int i = 0; i < roots_count; i++)
    {
        double r = roots[i];
        double diff = abs(r - x);

        if (diff < cur_diff)
        {
            cur_r = r;
            cur_diff = diff;
        }
    }

    return cur_r;
}

/// @brief Направленный поиск ближайшего корня.
///
/// Поиск ближайшего корня с учетом напрвления.
/// Сначала выполняется безусловный поиск ближайшего корня.
/// Потом учиывается направление:
/// dir > 0 - попытка найти ближайший корень, больше текущего,
/// dir < 0 - попытка найти ближайший корень, меньше текущего,
/// dir == 0 - возвращается ближайший как есть.
///
/// @param [in] x - Старый корень.
/// @param [in] roots - Корни.
/// @param [in] roots_count - Количество корней.
/// @param [in] dir - Направление поиска.
/// @param [in] max_possible_diff - Максимальное допустимое отклонение при направленном поиске.
///
/// @return
/// Новое значение корня.
double
directed_nearest_root(double x,
                      double *roots,
                      int roots_count,
                      double dir,
                      double max_possible_diff)
{
    double cur_r = nearest_root(x, roots, roots_count);
    double cur_diff = numeric_limits<double>::max();

    if (dir > 0.0)
    {
        for (int i = 0; i < roots_count; i++)
        {
            double r = roots[i];

            if (r > x)
            {
                double diff = abs(r - x);

                if ((diff < cur_diff) && (diff < max_possible_diff))
                {
                    cur_r = r;
                    cur_diff = diff;
                }
            }
        }
    }
    else if (dir < 0.0)
    {
        for (int i = 0; i < roots_count; i++)
        {
            double r = roots[i];

            if (r < x)
            {
                double diff = abs(r - x);

                if ((diff < cur_diff) && (diff < max_possible_diff))
                {
                    cur_r = r;
                    cur_diff = diff;
                }
            }
        }
    }

    return cur_r;
}

/// @}

}
