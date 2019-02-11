#include "canvas.h"
#include "dashcontrol.h"

Canvas::Canvas()
{

}

Canvas::~Canvas()
{

}

void Canvas::getDimensions(int &width, int &height)
{
    Gtk::Allocation allocation{ get_allocation() };
    width = (double)allocation.get_width();
    height = (double)allocation.get_height();
}

bool Canvas::on_draw(Cairo::RefPtr<Cairo::Context> const &cr)
{
    // Set canvas background color to black
    cr->set_source_rgb(0, 0, 0);
    cr->paint();

    // Draw a speedometer
    DashControl *speedometer = new DashControl();
    speedometer->draw(this, cr);

    return true;
}
