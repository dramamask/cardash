#include "speedometer.h"

#include "angle.h"
#include "color.h"

Speedometer::Speedometer(int xPos, int yPos, int radius, int angleFrom, int angleTo)
    : DashControl(xPos, yPos, radius)
{
    this->angleFrom = angleFrom;
    this->angleTo = angleTo;
}

void Speedometer::draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    double gr = Color::webToFraction(120);
    cr->set_source_rgb(gr, gr, gr);
    cr->set_line_width(1);
    
    cr->arc(
        this->xPos, 
        this->yPos, 
        this->radius, 
        Angle::degToCairo(this->angleFrom), 
        Angle::degToCairo(this->angleTo)
    );
    cr->stroke();

    cr->arc(
        this->xPos, 
        this->yPos, 
        0.9 * this->radius, 
        Angle::degToCairo(this->angleFrom), 
        Angle::degToCairo(this->angleTo)
    );  
    cr->stroke();
}
