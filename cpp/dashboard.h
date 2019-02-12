#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>

class Speedometer;

class Dashboard : public Gtk::DrawingArea
{
    public:
        Dashboard(int width, int height);
        virtual ~Dashboard();

    protected:
        // Override default signal handler:
        bool on_draw(Cairo::RefPtr<Cairo::Context> const &cr) override;

    private:
        Speedometer *speedometer;

        void getDimensions(int &width, int &height);
};

#endif
