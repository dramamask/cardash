#include "speedometer.h"

#include "angle.h"
#include "color.h"

Speedometer::Speedometer(
    int xPos, 
    int yPos, 
    int radius, 
    int angleFrom, 
    int angleTo,
    int maxSpeed
)
    : DashControl(xPos, yPos, radius)
{
    this->angleFrom = angleFrom;
    this->angleTo = angleTo;
    this->maxSpeed = maxSpeed;
}

void Speedometer::draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    double cc;

    // Outer arc
    cc = Color::webToFraction(100);
    cr->set_source_rgb(cc, cc, cc);    
    cr->set_line_width(2);

    cr->arc(
        this->xPos, 
        this->yPos, 
        0.90 * this->radius, 
        Angle::degToCairo(this->angleFrom), 
        Angle::degToCairo(this->angleTo)
    );  
    cr->stroke();

    // Inner two arcs
    cc = Color::webToFraction(60);
    cr->set_source_rgb(cc, cc, cc);
    cr->set_line_width(1);
    
    cr->arc(
        this->xPos, 
        this->yPos, 
        0.85 * this->radius, 
        Angle::degToCairo(this->angleFrom), 
        Angle::degToCairo(this->angleTo)
    );
    cr->stroke();

    cr->arc(
        this->xPos, 
        this->yPos, 
        0.75 * this->radius, 
        Angle::degToCairo(this->angleFrom), 
        Angle::degToCairo(this->angleTo)
    );  
    cr->stroke();

    // TODO: draw major speed lines every 20 mph, taking maxSpeed into account
    // try color 140 for those lines
}
