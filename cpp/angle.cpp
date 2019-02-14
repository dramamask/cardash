#include "angle.h"

#include <math.h>

/**
 * Take an angle in degrees and convert it to radians.
 */
double Angle::degToRad(double deg)
{
    return ((deg / 360) * 2 * M_PI);
}

/**
 * Convert degrees to radians, and rotate to the Cairo definition.
 * In the Cairo definition, East is 0, instead of North being 0.
 * 
 * deg Angle in degrees
 * output Angle in radians
 * 
 * Examples:
 *   deg = 90 -> output = 0
 *   deg = 180 -> output = pi / 2
 *   deg = -90 -> output = pi
 * 
 */
double Angle::degToCairo(double deg)
{
    return standardToCairo(degToRad(deg));
}

/**
 * Normale the angle (in degrees)
 * If the angle is more than 360 degrees or less than -360 degrees we normalize
 * it back within that range.
 */
double Angle::normalize(double deg)
{
    while (deg < 0) {
        deg += 360;
    }

    while (deg > 360) {
        deg -= 360;
    }

    return deg;
}

/**
 * Rotate from the standard definition (0 is North) to the Cairo
 * definition (0 is East)
 * 
 * Examples:
 *   rad = pi / 2 -> output = 0
 *   rad = pi -> output = pi / 2
 */
double Angle::standardToCairo(double rad)
{
    return rad + getCairoRotateCorrection();
}

/**
 * Return the angle that you need to rotate the drawing with
 * to get to the angle that you would expect (where 0 is North)
 */
double Angle::getCairoRotateCorrection()
{
    return (0 - (M_PI / 2));
}
