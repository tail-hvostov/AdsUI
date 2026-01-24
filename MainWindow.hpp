#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm/window.h>
#include <gtkmm/button.h>

class MainWindow : public Gtk::Window {
private:
    void on_m_button_press();

    Gtk::Button m_button;
public:
    MainWindow();
    virtual ~MainWindow() = default;
};

#endif // MAIN_WINDOW_HPP