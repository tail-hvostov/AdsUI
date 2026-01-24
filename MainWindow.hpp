#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#define INPUT_COUNT 8

class MainWindow : public Gtk::Window {
private:
    void on_m_button_press();

    void init_labels();

    Gtk::Button m_button;
    Gtk::Box m_box;
    Gtk::Grid m_grid;
    Gtk::Label* val_labels[INPUT_COUNT];
public:
    MainWindow();
    virtual ~MainWindow() = default;
};

#endif // MAIN_WINDOW_HPP