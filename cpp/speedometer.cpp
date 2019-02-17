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
    this->fontSizeSmall = 14;
    this->fontSizeLarge = 160;
    this->fontSizeMph = 20;
    this->fontFamily = "Ubuntu";

    // TODO: find a nice font.
}

void Speedometer::draw(Cairo::RefPtr<Cairo::Context> const & cr)
{
    double currentSpeed = 47;

    this->drawOuterArc(cr);
    this->drawInnerArcs(cr);

    this->drawBackgroundSpeedIndicator(cr);

    this->drawMajorSpeedLines(cr);
    this->drawMinorSpeedLines(cr);

    this->drawMph(cr);

    this->drawForegroundSpeedIndicator(cr, currentSpeed);
    this->drawSpeedText(cr, currentSpeed);
}

void Speedometer::drawOuterArc(const Cairo::RefPtr<Cairo::Context> &cr)
{
    double cc = Color::webToFraction(100);
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
}

void Speedometer::drawInnerArcs(const Cairo::RefPtr<Cairo::Context> &cr)
{
    double cc = Color::webToFraction(60);
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
}

void Speedometer::drawBackgroundSpeedIndicator(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Dark orange color    
    cr->set_source_rgb(0.2, 0.1, 0);

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
    // Make sure we end the previous drawing path
    cr->begin_new_path();

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

    // Draw glow around the end of the arc
    Cairo::RefPtr<Cairo::RadialGradient> radial = Cairo::RadialGradient::create(100, 100, 50, 100, 100, 10);
    radial->add_color_stop_rgba(0, 1, 0.74, 0, 0);
    radial->add_color_stop_rgba(1, 1, 0.74, 0, 1);
    cr->set_source(radial);
    cr->arc(100, 100, 50, 0, 2 * M_PI);
    cr->fill();
    // TODO: fix and finish

    // Set the line cap back to "none"
    cr->set_line_cap(Cairo::LineCap::LINE_CAP_BUTT);

    // TODO: make the inner and outer arcs orange upto the currentSpeed
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
    cr->select_font_face(this->fontFamily,
      Cairo::FontSlant::FONT_SLANT_NORMAL,
      Cairo::FontWeight::FONT_WEIGHT_NORMAL);
    cr->set_font_size(this->fontSizeSmall);

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
            (0.5 * this->fontSizeSmall) -
            (cosAngle * 0.185 * this->fontSizeSmall * numOfDigits * numOfDigits);
        textY = y1 -
            (sinAngle * 1.2 * this->fontSizeSmall)
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

void Speedometer::drawMph(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Set color
    cr->set_source_rgb(1, 1, 1);

    // Set font
    cr->select_font_face(this->fontFamily,
      Cairo::FontSlant::FONT_SLANT_NORMAL,
      Cairo::FontWeight::FONT_WEIGHT_NORMAL);
    cr->set_font_size(this->fontSizeMph);

    // Calculate text location
    double xPos = this->xPos - (0.9 * this->fontSizeMph);
    double yPos = this->yPos + (0.5 * this->fontSizeLarge);
    cr->move_to(xPos, yPos);

    // Draw text
    cr->show_text("mph");
}

/**
 * Draw the actual speed in the middle of the dial
 */
void Speedometer::drawSpeedText(const Cairo::RefPtr<Cairo::Context> &cr, double currentSpeed)
{
    // Set color
    cr->set_source_rgb(1, 1, 1);

    // Set font
    cr->select_font_face(this->fontFamily,
      Cairo::FontSlant::FONT_SLANT_NORMAL,
      Cairo::FontWeight::FONT_WEIGHT_NORMAL);
    cr->set_font_size(this->fontSizeLarge);

    // Calculate text location
    double xPos = 
        this->xPos - 
        (0.3 * this->getNumberOfDigits(currentSpeed) * this->fontSizeLarge);
    double yPos = 
        this->yPos + 
        (0.3 * this->fontSizeLarge);

    // Go to text position
    cr->move_to(xPos, yPos);

    // Draw text
    cr->show_text(std::to_string((int)currentSpeed));
}
