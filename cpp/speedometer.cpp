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

    this->outerMostArc = 0.9;
    this->outerArc = 0.85;
    this->innerArc = 0.75;
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
}

/**
 * draw major speed lines every 10 mph, taking maxSpeed into account.
 * try color 140 for those lines
 */
void Speedometer::drawMajorSpeedIndicators(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Define line and text colors
    double lineCC = Color::webToFraction(140);
    double textCC = Color::webToFraction(60);
    
    // Set line width
    cr->set_line_width(1);

    // Set font
    // TODO: find a nice font.
    // TODO: define the font somewhere in a central place
    cr->select_font_face("Ubuntu",
      Cairo::FontSlant::FONT_SLANT_NORMAL,
      Cairo::FontWeight::FONT_WEIGHT_NORMAL);
    cr->set_font_size(14);

    // Prepare for loop
    double increment = 10 * ((this->angleTo - this->angleFrom) / this->maxSpeed);

    double angle = this->angleFrom;
    bool done = false;
    double sinAngle;
    double cosAngle;
    double textX; 
    double textY;
    int speed = 0;

    // Loop to draw lines and text
    while (!done) {
        // Calculate line coordinates
        sinAngle = sin(angle);
        cosAngle = cos(angle);

        double x1 = this->xPos + ((this->innerArc - 0.02) * this->radius * cosAngle);
        double y1 = this->yPos + ((this->innerArc - 0.02) * this->radius * sinAngle);
        double x2 = this->xPos + ((this->outerArc + 0.04) * this->radius * cosAngle);
        double y2 = this->yPos + ((this->outerArc + 0.04) * this->radius * sinAngle);

        // Draw line
        cr->set_source_rgb(lineCC, lineCC, lineCC);
        cr->move_to(x1, y1);
        cr->line_to(x2, y2);
        cr->stroke();

        // Calculate text coordinates
        // TODO: come up with a formula to accuratly place the text
        textX = x1;
        textY = y1;

        // Draw text
        cr->set_source_rgb(textCC, textCC, textCC);
        cr->move_to(textX, textY);
        cr->show_text(std::to_string(speed));

        // Are we done?
        angle += increment;
        speed += 10;
        if (speed > this->maxSpeed) {
            done = true;
        }       
    }
}
