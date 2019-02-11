#include <gtkmm.h>

class Canvas;

class DashControl
{
    public:
        void draw(Canvas *canvas, Cairo::RefPtr<Cairo::Context> const & cr);
};
