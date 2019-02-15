#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "dashcontrol.h"

#include <gtkmm.h>
#include <string.h>

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
        void draw(const Cairo::RefPtr<Cairo::Context> &cr);

    private:
        /**
         * Angle in radians where the speedometer starts.
         */
        double angleFrom;

        /**
         * Angle in radians where the speedometer ends.
         */
        double angleTo;

        /**
         * The maximum speed displayed on the speedometer
         */
        int maxSpeed;

        /**
         * Radius of the arcs, as a fraction of the total radius
         */
        double outerMostArc;
        double outerArc;
        double innerArc;

        /**
         * Font defintions
         */
        int smallFontSize;
        int largeFontSize;
        std::string fontFamily;

        void drawMajorSpeedIndicators(const Cairo::RefPtr<Cairo::Context> &cr);
        void drawMinorSpeedIndicators(const Cairo::RefPtr<Cairo::Context> &cr);
        int getNumberOfDigits(int number);
};

#endif
