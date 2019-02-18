#include "color.h"

#include "colorComponent.h"

namespace DramaMask
{
    Color::Color(int r, int g, int b)
    {
        this->r = ColorComponent::webToFraction(r);
        this->g = ColorComponent::webToFraction(g);
        this->b = ColorComponent::webToFraction(b);
    }

    double Color::getR()
    {
        return this->r;
    }

    double Color::getG()
    {
        return this->g;
    }

    double Color::getB()
    {
        return this->b;
    }
}