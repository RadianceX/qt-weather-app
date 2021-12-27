//
// Created by Admin on 27.12.2021.
//

#include <QPushButton>
#include <QVBoxLayout>
#include "MainWindow.h"

/**
 * Constructor
 * @param parent parent widget
 */
MainWindow::MainWindow(QWidget *parent):
        QMainWindow(parent)
{
    m_weatherView = new WeatherView(parent);
    this->setCentralWidget(m_weatherView);
    this->setWindowTitle("QtWeatherApp");
    this->setFixedSize(400,100);
    this->show();
}
