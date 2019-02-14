#include "speedometer.h"

#include <string.h>

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
    this->angleFrom = Angle::degToCairo(angleFrom);
    this->angleTo = Angle::degToCairo(angleTo);
    this->maxSpeed = maxSpeed;
}

void Speedometer::draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    //cr->rotate(Angle::getCairoRotateCorrection());
    //cr->translate()

    double cc;

    // Outer arc
    cc = Color::webToFraction(100);
    cr->set_source_rgb(cc, cc, cc);    
    cr->set_line_width(2);

    cr->arc(
        this->xPos, 
        this->yPos, 
        0.90 * this->radius, 
        this->angleFrom, 
        this->angleTo
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
        this->angleFrom, 
        this->angleTo
    );
    cr->stroke();

    cr->arc(
        this->xPos, 
        this->yPos, 
        0.75 * this->radius, 
        this->angleFrom, 
        this->angleTo
    );  
    cr->stroke();

    this->drawMajorSpeedIndicators(cr);

    // TODO: draw major speed lines every 20 mph, taking maxSpeed into account
    // try color 140 for those lines
}

void Speedometer::drawMajorSpeedIndicators(const Cairo::RefPtr<Cairo::Context> &cr)
{
    double x1 = this->xPos + (0.75 * this->radius * cos(this->angleFrom));
    double y1 = this->yPos + (0.75 * this->radius * sin(this->angleFrom));
    double x2 = this->xPos + (0.85 * this->radius * cos(this->angleFrom));
    double y2 = this->yPos + (0.85 * this->radius * sin(this->angleFrom));

    cr->move_to(x1, y1);
    cr->line_to(x2, y2);
    cr->stroke();
//     cr->select_font_face("Ubuntu",
//       Cairo::FontSlant::FONT_SLANT_NORMAL,
//       Cairo::FontWeight::FONT_WEIGHT_NORMAL);

//   cr->set_font_size(30);
//   cr->move_to(100, 100);
//   cr->show_text(std::to_string(x1));


}
