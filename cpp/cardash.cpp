#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include "dashboard.h"

int main(int argc, char** argv)
{
    const int windowWidth = 800;
    const int windowHeight = 600;

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.resize(windowWidth, windowHeight);
    window.set_title("Car Dash");

    DramaMask::Dashboard dashboard(windowWidth, windowHeight);
    window.add(dashboard);
    dashboard.show();
    dashboard.start();

    return app->run(window);
}

