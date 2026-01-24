#include "MainWindow.hpp"

#include <stdio.h>
#include <cstdint>

#define WINDOW_DEFAULT_WIDTH 300

const char* TOGGLE_ON_TEXT = "Toggle on";
const char* TOGGLE_OFF_TEXT = "Toggle off";

MainWindow::MainWindow() : m_button(TOGGLE_ON_TEXT) {
    set_title("ADS controller");
    set_default_size(WINDOW_DEFAULT_WIDTH, 200);
    
    m_button.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_m_button_press)
    );
    add(m_button);
    
    show_all_children();
}

void MainWindow::on_m_button_press() {
    puts("Here");
}