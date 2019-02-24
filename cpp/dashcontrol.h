#ifndef DASHCONTROL_H
#define DASHCONTROL_H

class DashControl
{
    public:
        DashControl(int xPos, int yPos, int radius);

    protected:
        /**
         * 
         */
        int xPos;

        /**
         * 
         */
        int yPos;

        /**
         * 
         */
        int radius;

        /**
         * Angle in radians where the speedometer starts.
         */
        double angleFrom;

        /**
         * Angle in radians where the speedometer ends.
         */
        double angleTo;
};

#endif
