#include "angle.h"

#include <math.h>

double Angle::degToCairo(double deg)
{
    return standardToCairo((makePositive(deg) / 360) * 2 * M_PI);
}

double Angle::makePositive(double deg)
{
    while (deg < 0) {
        deg += 360;
    }

    return deg;
}

double Angle::standardToCairo(double rad)
{
    return rad - (M_PI / 2);
}