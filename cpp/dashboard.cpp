#include "dashboard.h"

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

        this->speedometer = new Speedometer(
            speedoXPos, 
            speedoYPos, 
            controlRadius,
            speedoAngleFrom,
            speedoAngleTo,
            maxSpeed
        );

        this->currentSpeed = 0;

        this->initAnimation = new InitAnimation(
            25, // frames per second
            4000 // total animation time in ms
        );
    }

    Dashboard::~Dashboard()
    {
        delete this->speedometer;
        this->speedometer = NULL;
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
        Glib::signal_timeout().connect( sigc::mem_fun(*this, &Dashboard::onTimer), 100 );
    }

    bool Dashboard::onTimer()
    {
        this->currentSpeed += 10;
        if (this->currentSpeed > 100) {
            return false;
        }

        this->forceRedraw();

        return true;
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