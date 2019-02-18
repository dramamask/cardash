#include "dashboard.h"

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

        // Draw a dash controls    
        this->speedometer->draw(cr);

        return true;
    }

    void Dashboard::getDimensions(int &width, int &height)
    {
        Gtk::Allocation allocation = get_allocation();
        width = allocation.get_width();
        height = allocation.get_height();
    }
}