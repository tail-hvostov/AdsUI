#include "MainWindow.hpp"

#include <stdio.h>
#include <cstdint>
#include <cstring>

#define WINDOW_DEFAULT_WIDTH 300

const char* TOGGLE_ON_TEXT = "Toggle on";
const char* TOGGLE_OFF_TEXT = "Toggle off";

MainWindow::MainWindow() : m_button(TOGGLE_ON_TEXT),
                            m_box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_title("ADS controller");
    set_default_size(WINDOW_DEFAULT_WIDTH, 200);
    
    init_labels();

    m_grid.set_column_spacing(10);
    m_grid.set_row_spacing(5);
    
    m_box.set_margin_top(10);
    m_box.set_margin_bottom(10);
    m_box.set_margin_start(10);
    m_box.set_margin_end(10);

    add(m_box);
    m_box.pack_start(m_grid);
    m_box.pack_start(m_button);

    m_button.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_m_button_press)
    );
    
    show_all_children();
}

void MainWindow::init_labels() {
    char buf[10];
    Gtk::Label* prev = Gtk::make_managed<Gtk::Label>("0.");
    val_labels[0] = Gtk::make_managed<Gtk::Label>("0");
    m_grid.add(*prev);
    m_grid.add(*val_labels[0]);
    for (int i = 1; i < INPUT_COUNT; i++) {
        sprintf(buf, "%d.", i);
        Gtk::Label* l = Gtk::make_managed<Gtk::Label>(buf);
        m_grid.attach_next_to(*l, *prev, Gtk::POS_BOTTOM, 1, 1);
        prev = l;
        l = Gtk::make_managed<Gtk::Label>("0");
        m_grid.attach_next_to(*l, *val_labels[i - 1], Gtk::POS_BOTTOM, 1, 1);
        val_labels[i] = l;
    }
}

void MainWindow::on_m_button_press() {
    puts("Here");
}