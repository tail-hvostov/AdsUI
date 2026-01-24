#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/main.h>
#include <glibmm/timer.h>

#define INPUT_COUNT 8

class MainWindow : public Gtk::Window {
private:
    void on_m_button_press();
    bool on_timeout();

    void init_labels();

    Gtk::Button m_button;
    Gtk::Box m_box;
    Gtk::Grid m_grid;
    Gtk::Label* val_labels[INPUT_COUNT];
    Gtk::Label m_fh_label;
    Gtk::Label m_fv_label;

    bool is_ads_active = false;
    sigc::connection update_connection;
    Glib::Timer update_timer;
public:
    MainWindow();
    virtual ~MainWindow() = default;
};

#endif // MAIN_WINDOW_HPP