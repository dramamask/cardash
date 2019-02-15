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
        int fontSizeSmall;
        int fontSizeLarge;
        int fontSizeMph;
        std::string fontFamily;

        void drawOuterArc(const Cairo::RefPtr<Cairo::Context> &cr);
        void drawInnerArcs(const Cairo::RefPtr<Cairo::Context> &cr);

        void drawBackgroundSpeedIndicator(const Cairo::RefPtr<Cairo::Context> &cr);
        void drawForegroundSpeedIndicator(
            const Cairo::RefPtr<Cairo::Context> &cr, 
            double currentSpeed
        );

        void drawMajorSpeedLines(const Cairo::RefPtr<Cairo::Context> &cr);
        void drawMinorSpeedLines(const Cairo::RefPtr<Cairo::Context> &cr);
        int getNumberOfDigits(int number);
  
        double getSpeedAngle(double speed);

        void drawSpeedText(const Cairo::RefPtr<Cairo::Context> &cr, double currentSpeed);
        void drawMph(const Cairo::RefPtr<Cairo::Context> &cr);
};

#endif
