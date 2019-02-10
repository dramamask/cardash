#include <gtkmm.h>
#include <gtkmm/drawingarea.h>

class Canvas : public Gtk::DrawingArea
{
    public:
        Canvas();
        virtual ~Canvas();
        
    protected:
        // Override default signal handler:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;    
};
