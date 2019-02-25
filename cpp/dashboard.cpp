#include "dashboard.h"

#include "color.h"
#include "initAnimation.h"
#include "speedometer.h"

namespace DramaMask
{
    Dashboard::Dashboard(int width, int height)
    {
        int controlRadius = 0.8 * (height / 2);

        int speedoXPos = width / 2;
        int speedoYPos = height / 2;
        int speedoAngleFrom = -135;
        int speedoAngleTo = 135;
        int maxSpeed = 160;

        this->outerArcColor = new DramaMask::Color(120, 120, 120);
        this->innerArcColor = new DramaMask::Color(80, 80, 80);
        this->valueTextColor = new DramaMask::Color(255, 255, 255);
        this->valueIndBgColor = new DramaMask::Color(51, 26, 0);
        this->valueIndFgColor = new DramaMask::Color(255, 170, 0);
        this->innerArcGlowColor = new DramaMask::Color(140, 77, 0);

        this->initAnimation = new InitAnimation(
            25, // frames per second
            1800, // total animation time in ms (not including initial wait time)
            400 // initial wait time in ms
        );

        this->speedometer = new Speedometer(
            speedoXPos, 
            speedoYPos, 
            controlRadius,
            speedoAngleFrom,
            speedoAngleTo,
            maxSpeed,
            this
        );

        this->currentSpeed = 0;
    }

    Dashboard::~Dashboard()
    {
        delete this->initAnimation;
        this->initAnimation = NULL;

        delete this->speedometer;
        this->speedometer = NULL;

        delete this->outerArcColor;
        this->outerArcColor = NULL;
        
        delete this->innerArcColor;
        this->innerArcColor = NULL;
        
        delete this->valueTextColor;
        this->valueTextColor = NULL;
        
        delete this->valueIndBgColor;
        this->valueIndBgColor = NULL;
        
        delete this->valueIndFgColor;
        this->valueIndFgColor = NULL;
        
        delete this->innerArcGlowColor;
        this->innerArcGlowColor = NULL;
    }

    bool Dashboard::on_draw(Cairo::RefPtr<Cairo::Context> const &cr)
    {
        // Set background color to black
        cr->set_source_rgb(0, 0, 0);
        cr->paint();

        // Draw the speedometer    
        this->speedometer->draw(cr, this->currentSpeed);

        return true;
    }

    void Dashboard::start()
    {
        Glib::signal_timeout().connect(
            sigc::mem_fun(*this, &Dashboard::onTimer), 
            this->initAnimation->getFrameTime()
        );
    }

    InitAnimation *Dashboard::getInitAnimation()
    {
        return this->initAnimation;
    }

    Color *Dashboard::getOuterArcColor()
    {
        return this->outerArcColor;
    }

    Color *Dashboard::getInnerArcColor()
    {
        return this->innerArcColor;
    }

    Color *Dashboard::getValueTextColor()
    {
        return this->valueTextColor;
    }

    Color *Dashboard::getValueIndBgColor()
    {
        return this->valueIndBgColor;
    }

    Color *Dashboard::getValueIndFgColor()
    {
        return this->valueIndFgColor;
    }

    Color *Dashboard::getInnerArcGlowColor()
    {
        return this->innerArcGlowColor;
    }

    bool Dashboard::onTimer()
    {
        bool keepGoing = this->initAnimation->onTimer();

        if (keepGoing) {
            this->forceRedraw();
            return true;
        }

        return false;
    }

    void Dashboard::forceRedraw()
    {
        // force our program to redraw the entire dashboard
        auto win = get_window();
        if (win)
        {
            Gdk::Rectangle r(
                0, 
                0, 
                get_allocation().get_width(),
                get_allocation().get_height()
            );
            win->invalidate_rect(r, false);
        }
    }

    void Dashboard::getDimensions(int &width, int &height)
    {
        Gtk::Allocation allocation = get_allocation();
        width = allocation.get_width();
        height = allocation.get_height();
    }
}