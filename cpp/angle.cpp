#include "angle.h"

#include <math.h>

double Angle::degToRad(double angle)
{
    return (angle/360) * 2 * M_PI;
}