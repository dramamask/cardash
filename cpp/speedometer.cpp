#include "speedometer.h"

#include <string.h>

#include "color.h"
#include "colorComponent.h"
#include "initAnimation.h"

namespace DramaMask
{
    Speedometer::Speedometer(
        int xPos, 
        int yPos, 
        int radius, 
        int angleFrom, 
        int angleTo,
        int maxSpeed,
        InitAnimation *initAnimation
    )
        : DashControl(xPos, yPos, radius, angleFrom, angleTo)
    {        
        this->maxSpeed = maxSpeed;

        this->initAnimation = initAnimation;

        this->outerMostArc = 0.9;
        this->outerArc = 0.85;
        this->innerArc = 0.75;
        this->fontSizeSmall = 14;
        this->fontSizeLarge = 160;
        this->fontSizeMph = 20;
        this->fontFamily = "Ubuntu";

        this->outerArcColor = new DramaMask::Color(120, 120, 120);
        this->innerArcColor = new DramaMask::Color(80, 80, 80);
        this->speedTextColor = new DramaMask::Color(255, 255, 255);
        this->speedIndBgColor = new DramaMask::Color(51, 26, 0);
        this->speedIndFgColor = new DramaMask::Color(255, 170, 0);
        this->innerArcGlowColor = new DramaMask::Color(140, 77, 0);
    }

    Speedometer::~Speedometer()
    {
        delete this->outerArcColor;
        this->outerArcColor = NULL;
        
        delete this->innerArcColor;
        this->innerArcColor = NULL;
        
        delete this->speedTextColor;
        this->speedTextColor = NULL;
        
        delete this->speedIndBgColor;
        this->speedIndBgColor = NULL;
        
        delete this->speedIndFgColor;
        this->speedIndFgColor = NULL;
        
        delete this->innerArcGlowColor;
        this->innerArcGlowColor = NULL;
    }

    void Speedometer::draw(Cairo::RefPtr<Cairo::Context> const & cr, double currentSpeed)
    {
        this->currentSpeed = currentSpeed;

        this->handleInitAnimation(cr);

        this->drawOuterArc(cr);
        this->drawInnerArcs(cr, this->angleTo, this->innerArcColor);

        this->drawBackgroundSpeedIndicator(cr);

        this->drawMajorSpeedLines(cr);
        this->drawMinorSpeedLines(cr);

        this->drawMph(cr);

        this->drawForegroundSpeedIndicator(cr);
        this->drawSpeedText(cr);
    }

    void Speedometer::drawOuterArc(const Cairo::RefPtr<Cairo::Context> &cr)
    {
        cr->set_source_rgb(
            this->outerArcColor->getR(),
            this->outerArcColor->getG(),
            this->outerArcColor->getB()
        );
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

    void Speedometer::drawInnerArcs(
        const Cairo::RefPtr<Cairo::Context> &cr,
        double angleTo,
        DramaMask::Color *color
    )
    {
        cr->set_source_rgb(color->getR(), color->getG(), color->getB());
        cr->set_line_width(1);
        
        cr->arc(
            this->xPos, 
            this->yPos, 
            this->outerArc * this->radius, 
            this->angleFrom, 
            angleTo
        );
        cr->stroke();

        cr->arc(
            this->xPos, 
            this->yPos, 
            this->innerArc * this->radius, 
            this->angleFrom, 
            angleTo
        );  
        cr->stroke();
    }

    void Speedometer::drawBackgroundSpeedIndicator(const Cairo::RefPtr<Cairo::Context> &cr)
    {
        // Dark orange color    
        cr->set_source_rgb(
            this->speedIndBgColor->getR(),
            this->speedIndBgColor->getG(),
            this->speedIndBgColor->getB()
        );

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

    void Speedometer::drawForegroundSpeedIndicator(const Cairo::RefPtr<Cairo::Context> &cr)
    {
        // Make sure we end the previous drawing path
        cr->begin_new_path();

        // Dark orange color
        cr->set_source_rgb(
            this->speedIndFgColor->getR(),
            this->speedIndFgColor->getG(),
            this->speedIndFgColor->getB()
        );

        // Set arc line with
        double lineWidth = ((this->outerArc - this->innerArc - 0.02) * this->radius);
        cr->set_line_width(lineWidth);
        
        // Calculate arc radius and to-angle
        double radius = 0.5 * (this->outerArc + this->innerArc) * this->radius;
        double angleTo = this->getSpeedAngle(this->currentSpeed);

        // Draw the first part of the arc (no line cap at the bottom)    
        cr->arc(
            this->xPos, 
            this->yPos, 
            radius, 
            this->angleFrom, 
            angleTo
        );
        cr->stroke();

        // Draw the round line cap
        cr->set_line_cap(Cairo::LineCap::LINE_CAP_ROUND);
        cr->arc(
            this->xPos, 
            this->yPos, 
            radius, 
            angleTo,
            angleTo
        );
        cr->stroke();

        // Set the line cap back to "none"
        cr->set_line_cap(Cairo::LineCap::LINE_CAP_BUTT);

        // Draw glowing inner arcs
        this->drawInnerArcs(cr, angleTo, this->innerArcGlowColor);

        // Calculate the position of the tip of the arc
        double tipX = this->xPos + cos(angleTo) * radius;
        double tipY = this->yPos + sin(angleTo) * radius;

        // Define the radial gradient pattern for the tip of the speed indication arc
        Cairo::RefPtr<Cairo::RadialGradient> gradientCircle;
        gradientCircle = Cairo::RadialGradient::create(tipX, tipY, 20, tipX, tipY, 1);
        gradientCircle->add_color_stop_rgba(0, 1, 0.74, 0, 0);
        gradientCircle->add_color_stop_rgba(1, 1, 0.74, 0, 1);
        cr->set_source(gradientCircle);
        cr->arc(tipX, tipY, 25, 0, 2 * M_PI);
        cr->fill();
    }

    /**
     * Draw major speed lines every 10 mph (taking maxSpeed into account).
     */
    void Speedometer::drawMajorSpeedLines(const Cairo::RefPtr<Cairo::Context> &cr)
    {        
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
            cr->set_source_rgb(      
                this->outerArcColor->getR(),
                this->outerArcColor->getG(),
                this->outerArcColor->getB()
            );
            cr->move_to(x1, y1);
            cr->line_to(x2, y2);
            cr->stroke();

            // Calculate text coordinates
            int numOfDigits = this->getNumberOfDigits(speed);
            if (numOfDigits < 2) {
                numOfDigits = 2; // Hack to properly position 1 digit numbers
            }
            textX = x1 -
                (0.5 * this->fontSizeSmall) -
                (cosAngle * 0.185 * this->fontSizeSmall * numOfDigits * numOfDigits);
            textY = y1 -
                (sinAngle * 1.2 * this->fontSizeSmall)
                + 2;

            // Draw text
            cr->set_source_rgb(
                this->innerArcColor->getR(),
                this->innerArcColor->getG(),
                this->innerArcColor->getB()
            );
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
        // Define line color
        cr->set_source_rgb(
            this->innerArcColor->getR(),
            this->innerArcColor->getG(),
            this->innerArcColor->getB()
        );
    
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
        cr->set_source_rgb(
            this->speedTextColor->getR(),
            this->speedTextColor->getG(),
            this->speedTextColor->getB()
        );

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
    void Speedometer::drawSpeedText(const Cairo::RefPtr<Cairo::Context> &cr)
    {
        // Set color
        cr->set_source_rgb(
            this->speedTextColor->getR(),
            this->speedTextColor->getG(),
            this->speedTextColor->getB()
        );

        // Set font
        cr->select_font_face(this->fontFamily,
        Cairo::FontSlant::FONT_SLANT_NORMAL,
        Cairo::FontWeight::FONT_WEIGHT_NORMAL);
        cr->set_font_size(this->fontSizeLarge);

        // Calculate text location
        double xPos = 
            this->xPos - 
            (0.3 * this->getNumberOfDigits(this->currentSpeed) * this->fontSizeLarge);
        double yPos = 
            this->yPos + 
            (0.3 * this->fontSizeLarge);

        // Go to text position
        cr->move_to(xPos, yPos);

        // Draw text
        cr->show_text(std::to_string((int)this->currentSpeed));
    }

    // Handle the initialization animation
    void Speedometer::handleInitAnimation(const Cairo::RefPtr<Cairo::Context> &cr)
    {
        // Get the current frame information
        int currentFrame;
        int totalNumOfFrames;
        this->initAnimation->getFrameInfo(currentFrame, totalNumOfFrames);

        // Calcuate the mph increment for each frame
        double mphPerFrame = (double)(2 * this->maxSpeed) / (double)totalNumOfFrames;

        // Calculate the current speed to be displayed
        this->currentSpeed += ((double)currentFrame * mphPerFrame);

        if (currentFrame > (totalNumOfFrames / 2)) {
            this->currentSpeed = this->maxSpeed - (this->currentSpeed - this->maxSpeed);
        }
    }
}
