#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>

namespace DramaMask {
    class InitAnimation;
    class Speedometer;
    
    class Dashboard : public Gtk::DrawingArea
    {
        public:
            Dashboard(int width, int height);
            virtual ~Dashboard();

            void start();            

        protected:
            // Override default signal handler:
            bool on_draw(Cairo::RefPtr<Cairo::Context> const &cr) override;

            bool onTimer();

        private:
            InitAnimation *initAnimation;
            Speedometer *speedometer;
            double currentSpeed;

            void forceRedraw();

            void getDimensions(int &width, int &height);
    };
}

#endif
