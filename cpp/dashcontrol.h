#ifndef DASHCONTROL_H
#define DASHCONTROL_H

class DashControl
{
    public:
        DashControl(
            int xPos, 
            int yPos, 
            int radius,
            int angleFrom, 
            int angleTo
        );

    protected:
        /**
         * X postion of the control
         */
        int xPos;

        /**
         * Y position of the control
         */
        int yPos;

        /**
         * radius of the control
         */
        int radius;

        /**
         * Angle in radians where the control starts.
         */
        double angleFrom;

        /**
         * Angle in radians where the control ends.
         */
        double angleTo;
};

#endif
