#ifndef ANGLE_H
#define ANGLE_H

class Angle
{
    public:
        static double degToRad(double deg);
        static double degToCairo(double deg);
        static double normalize(double deg); 
        static double standardToCairo(double rad);

    private:
        static double getCairoRotateCorrection();
    
};

#endif
