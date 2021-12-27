//
// Created by Admin on 27.12.2021.
//

#ifndef QT_WEATHER_APP_WEATHERVIEW_H
#define QT_WEATHER_APP_WEATHERVIEW_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

class WeatherView: public QWidget{
    Q_OBJECT
public:
    explicit WeatherView(QWidget* parent = Q_NULLPTR);

private:
    QLineEdit* m_cityNameInput;
    QLabel* m_temperature = new QLabel();
    static QString getWeatherForCity(const QString& cityName);

public slots:
    void onClickGetWeather();

};


#endif //QT_WEATHER_APP_WEATHERVIEW_H
