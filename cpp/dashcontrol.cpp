#include "dashcontrol.h"

#include <gtkmm/drawingarea.h>

#include "angle.h"

DashControl::DashControl(int xPos, int yPos, int radius)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->radius = radius;

    this->angleFrom = Angle::degToCairo(angleFrom);
    this->angleTo = Angle::degToCairo(angleTo);
}
