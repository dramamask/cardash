#include <gtkmm.h>
#include <gtkmm/drawingarea.h>

class Canvas : public Gtk::DrawingArea
{
    public:
        Canvas();
        virtual ~Canvas();
};
