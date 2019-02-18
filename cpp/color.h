#ifndef COLOR_H
#define COLOR_H

namespace DramaMask
{
    class Color
    {
        public:
            // r, g and b are a number from 0 to 255
            Color(int r, int g, int b);

            // Get r, g or b as a fraction from 0 to 1
            double getR();
            double getG();
            double getB();

        private:
            double r;
            double g;
            double b;
    };
}

#endif