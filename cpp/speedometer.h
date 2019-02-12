#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "dashcontrol.h"

#include <gtkmm.h>

class Speedometer : public DashControl
{
    public:
        Speedometer(
            int xPos, 
            int yPos, 
            int radius, 
            int angleFrom, 
            int angleTo,
            int MaxSpeed
        );
        void draw(Cairo::RefPtr<Cairo::Context> const & cr);

    private:
        /**
         * Angle in degrees where the speedometer starts.
         */
        int angleFrom;

        /**
         * Angle in degrees where the speedometer ends.
         */
        int angleTo;

        /**
         * The maximum speed displayed on the speedometer
         */
        int maxSpeed;
};

#endif