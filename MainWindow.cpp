#include "MainWindow.hpp"

#include <stdio.h>
#include <cstdint>
#include <cstring>

#define WINDOW_DEFAULT_WIDTH 200
#define TIMEOUT_PERIOD 400

const char* TOGGLE_ON_TEXT = "Toggle on";
const char* TOGGLE_OFF_TEXT = "Toggle off";
const char* DEFAULT_VALUE_TEXT = "0.0000";

MainWindow::MainWindow() : m_button(TOGGLE_ON_TEXT),
                            m_box(Gtk::ORIENTATION_VERTICAL, 5),
                            m_fh_label("Frequency"),
                            m_fv_label(DEFAULT_VALUE_TEXT) {
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

    signal_hide().connect(
        sigc::mem_fun(*this, &MainWindow::on_window_hide)
    );
    
    show_all_children();
}

void MainWindow::init_labels() {
    char buf[10];
    Gtk::Label* prev = Gtk::make_managed<Gtk::Label>("0.");
    prev->set_halign(Gtk::ALIGN_START);
    val_labels[0] = Gtk::make_managed<Gtk::Label>(DEFAULT_VALUE_TEXT);
    val_labels[0]->set_halign(Gtk::ALIGN_START);
    m_grid.add(*prev);
    m_grid.add(*val_labels[0]);
    for (int i = 1; i < ADSR::INPUT_COUNT; i++) {
        sprintf(buf, "%d.", i);
        Gtk::Label* l = Gtk::make_managed<Gtk::Label>(buf);
        m_grid.attach_next_to(*l, *prev, Gtk::POS_BOTTOM, 1, 1);
        prev = l;
        prev->set_halign(Gtk::ALIGN_START);
        l = Gtk::make_managed<Gtk::Label>(DEFAULT_VALUE_TEXT);
        m_grid.attach_next_to(*l, *val_labels[i - 1], Gtk::POS_BOTTOM, 1, 1);
        val_labels[i] = l;
        l->set_halign(Gtk::ALIGN_START);
    }
    m_grid.attach_next_to(m_fh_label, *prev, Gtk::POS_BOTTOM, 1, 1);
    m_grid.attach_next_to(m_fv_label, *val_labels[ADSR::INPUT_COUNT - 1], Gtk::POS_BOTTOM, 1, 1);
}

void MainWindow::on_m_button_press() {
    is_ads_active = !is_ads_active;
    if (is_ads_active) {
        try {
            ADSR::start();
            m_button.set_label(TOGGLE_OFF_TEXT);
            update_connection = Glib::signal_timeout().connect(
                sigc::mem_fun(*this, &MainWindow::on_timeout),
                TIMEOUT_PERIOD
            );
            update_timer.reset();
        }
        catch (std::runtime_error e) {
            is_ads_active = !is_ads_active;
        }
    }
    else {
        m_button.set_label(TOGGLE_ON_TEXT);
        update_connection.disconnect();
        ADSR::stop();
    }
}

bool MainWindow::on_timeout() {
    ADSR::AdsStats stats;
    double elapsed;

    ADSR::retrieve(stats);
    elapsed = update_timer.elapsed();

    char buf[20];
    for (int i = 0; i < ADSR::INPUT_COUNT; i++) {
        sprintf(buf, "%.4f", stats.average_v[i]);
        val_labels[i]->set_label(buf);
    }

    double frequency = stats.measurements / elapsed;
    sprintf(buf, "%.4f", frequency);
    m_fv_label.set_label(buf);

    update_timer.reset();
    return true;
}

void MainWindow::on_window_hide() {
    if (is_ads_active) {
        ADSR::stop();
    }
}