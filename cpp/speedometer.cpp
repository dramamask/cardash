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
    this->smallFontSize = 14;
    this->largeFontSize = 60;
    this->fontFamily = "Ubuntu";
}

void Speedometer::draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    double currentSpeed = 47;

    double cc;

    // Outer arc
    cc = Color::webToFraction(100);
    cr->set_source_rgb(cc, cc, cc);    
    cr->set_line_width(2);

    cr->arc(
        this->xPos, 
        this->yPos, 
        this->outerMostArc * this->radius, 
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
        this->outerArc * this->radius, 
        this->angleFrom, 
        this->angleTo
    );
    cr->stroke();

    cr->arc(
        this->xPos, 
        this->yPos, 
        this->innerArc * this->radius, 
        this->angleFrom, 
        this->angleTo
    );  
    cr->stroke();

    // Speed indicator background arc
    this->drawBackgroundSpeedIndicator(cr);

    // Speed lines
    this->drawMajorSpeedLines(cr);
    this->drawMinorSpeedLines(cr);

    // The actual speed indicators
    this->drawForegroundSpeedIndicator(cr, currentSpeed);
    //TODO: this->drawSpeedText(cr, currentSpeed);

}

void Speedometer::drawBackgroundSpeedIndicator(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Dark orange color
    cr->set_source_rgb(0.20, 0.10, 0);

    // Set arc line with
    double lineWidth = ((this->outerArc - this->innerArc - 0.02) * this->radius);
    cr->set_line_width(lineWidth);

    // Calculate arc radius
    double radius = 0.5 * (this->outerArc + this->innerArc) * this->radius;

    // Draw arc
    cr->arc(
        this->xPos, 
        this->yPos, 
        radius, 
        this->angleFrom, 
        this->angleTo
    );
    cr->stroke();
}

void Speedometer::drawForegroundSpeedIndicator(
            const Cairo::RefPtr<Cairo::Context> &cr, 
            double currentSpeed
        )
{
    // Dark orange color
    cr->set_source_rgb(1, 0.74, 0);

    // Set arc line with
    double lineWidth = ((this->outerArc - this->innerArc - 0.02) * this->radius);
    cr->set_line_width(lineWidth);
    
    // Calculate arc radius and to-angle
    double radius = 0.5 * (this->outerArc + this->innerArc) * this->radius;
    double angleTo = this->getSpeedAngle(currentSpeed);

    // Draw the first part of the arc (no line cap at the bottom)    
    cr->arc(
        this->xPos, 
        this->yPos, 
        radius, 
        this->angleFrom, 
        angleTo - 0.15
    );
    cr->stroke();

    // Draw the last part of the arc (line cap round)
    cr->set_line_cap(Cairo::LineCap::LINE_CAP_ROUND);
    cr->arc(
        this->xPos, 
        this->yPos, 
        radius, 
        angleTo - 0.15,
        angleTo
    );
    cr->stroke();

    // Set the line cap back to "none"
    cr->set_line_cap(Cairo::LineCap::LINE_CAP_BUTT);

    // TODO: make the inner and outer arcs orange upto the currentSpeed
    // TODO: add glow around the end of the speed indicator arc
}

/**
 * Draw major speed lines every 10 mph (taking maxSpeed into account).
 */
void Speedometer::drawMajorSpeedLines(const Cairo::RefPtr<Cairo::Context> &cr)
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
    cr->set_font_size(this->smallFontSize);

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
        double x2 = this->xPos + ((this->outerArc + 0.02) * this->radius * cosAngle);
        double y2 = this->yPos + ((this->outerArc + 0.02) * this->radius * sinAngle);

        // Draw line
        cr->set_source_rgb(lineCC, lineCC, lineCC);
        cr->move_to(x1, y1);
        cr->line_to(x2, y2);
        cr->stroke();

        // Calculate text coordinates
        int numOfDigits = this->getNumberOfDigits(speed);
        textX = x1 -
            (0.5 * this->smallFontSize) -
            (cosAngle * 0.185 * this->smallFontSize * numOfDigits * numOfDigits);
        textY = y1 -
            (sinAngle * 1.2 * this->smallFontSize)
            + 2;

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

/**
 * Draw minor speed lines in between the 10 mph lines.
 */
void Speedometer::drawMinorSpeedLines(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Define line and text colors
    double lineCC = Color::webToFraction(60);
    cr->set_source_rgb(lineCC, lineCC, lineCC);
    
    // Set line width
    cr->set_line_width(1);

    // Prepare for loop
    double increment = 10 * ((this->angleTo - this->angleFrom) / this->maxSpeed);

    double angle = this->angleFrom + (0.5 * increment);
    bool done = false;
    double sinAngle;
    double cosAngle;

    // Loop to draw lines and text
    while (!done) {
        // Calculate line coordinates
        sinAngle = sin(angle);
        cosAngle = cos(angle);

        double x1 = this->xPos + ((this->innerArc + 0.01) * this->radius * cosAngle);
        double y1 = this->yPos + ((this->innerArc + 0.01) * this->radius * sinAngle);
        double x2 = this->xPos + ((this->outerArc - 0.01) * this->radius * cosAngle);
        double y2 = this->yPos + ((this->outerArc - 0.01) * this->radius * sinAngle);

        // Draw line
        cr->move_to(x1, y1);
        cr->line_to(x2, y2);
        cr->stroke();

        // Are we done?
        angle += increment;
        if (angle > this->angleTo) {
            done = true;
        }       
    }
}

/**
 * Returns number of digits in a number. 
 * Works for number < 1000.
 */
int Speedometer::getNumberOfDigits(int number)
{
    if (number < 100 ) {
        if (number < 10) {
            return 1;
        }

        return 2;
    }        

    return 3;
}

/**
 * Get arc angle for a certain speed
 */
double Speedometer::getSpeedAngle(double speed)
{
    return this->angleFrom + (speed * ((this->angleTo - this->angleFrom) / this->maxSpeed));
}
