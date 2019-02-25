#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>

namespace DramaMask {
    class Color;
    class InitAnimation;
    class Speedometer;
    
    class Dashboard : public Gtk::DrawingArea
    {
        public:
            Dashboard(int width, int height);
            virtual ~Dashboard();

            void start();
            InitAnimation *getInitAnimation();
            Color *getOuterArcColor();
            Color *getInnerArcColor();
            Color *getValueTextColor();
            Color *getValueIndBgColor();
            Color *getValueIndFgColor();
            Color *getInnerArcGlowColor();

        protected:
            // Override default signal handler:
            bool on_draw(Cairo::RefPtr<Cairo::Context> const &cr) override;

            bool onTimer();

        private:
            InitAnimation *initAnimation;
            Speedometer *speedometer;
            double currentSpeed;

            /**
             * Color definitions
             */
            Color *outerArcColor;
            Color *innerArcColor;
            Color *valueTextColor;
            Color *valueIndBgColor;
            Color *valueIndFgColor;
            Color *innerArcGlowColor;

            void forceRedraw();

            void getDimensions(int &width, int &height);
    };
}

#endif
