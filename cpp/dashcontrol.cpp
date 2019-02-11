#include "dashcontrol.h"

#include <gtkmm/drawingarea.h>

#include "angle.h"
#include "canvas.h"
#include "color.h"

void DashControl::draw(Canvas *canvas, Cairo::RefPtr<Cairo::Context> const & cr)
{
    int width;
    int height;
    canvas->getDimensions(width, height);

    double gr = Color::webToFraction(120);
    cr->set_source_rgb(gr, gr, gr);
    cr->set_line_width(1);
    
    double angle1 = Angle::degToRad(135);
    double angle2 = Angle::degToRad(45);
    cr->arc(width/2, height/2, width/4, angle1, angle2);
    
    cr->stroke();
}