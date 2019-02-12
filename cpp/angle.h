#ifndef ANGLE_H
#define ANGLE_H

class Angle
{
    public:
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
        static double degToCairo(double deg);
    
    private:
        /**
         * Change a negative angle to a positive one.
         * 
         * deg Angle in degees
         * output Angle in positive degrees
         * 
         * Examples:
         *   deg = -90 -> output = 270
         *   deg = 90 -> output 90
         */
        static double makePositive(double deg);

        /**
         * Rotate from the standard definition (0 is North) to the Cairo
         * definition (0 is East)
         * 
         * Examples:
         *   rad = pi / 2 -> output = 0
         *   rad = pi -> output = pi / 2
         */
        static double standardToCairo(double rad);
};

#endif
