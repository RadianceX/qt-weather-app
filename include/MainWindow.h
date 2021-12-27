//
// Created by Admin on 27.12.2021.
//

#ifndef QT_WEATHER_APP_MAINWINDOW_H
#define QT_WEATHER_APP_MAINWINDOW_H
#include "QMainWindow"
#include "WeatherView.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    WeatherView* m_weatherView;
};


#endif //QT_WEATHER_APP_MAINWINDOW_H
