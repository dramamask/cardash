#include <gtkmm.h>
#include <gtkmm/drawingarea.h>

class Canvas : public Gtk::DrawingArea
{
    public:
        Canvas();
        virtual ~Canvas();

        /**
         * Return the dimensions of the canvas
         */ 
        void getDimensions(int &width, int &height);

    protected:
        // Override default signal handler:
        bool on_draw(Cairo::RefPtr<Cairo::Context> const &cr) override;
};
