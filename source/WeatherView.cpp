//
// Created by Admin on 27.12.2021.
//

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "WeatherView.h"

/**
 * Constructor
 * @param parent parent widget
 */
WeatherView::WeatherView(QWidget *parent):
        QWidget(parent)
{
    // All widgets will be inside vertical layout
    auto viewLayout = new QVBoxLayout;

    // Create city input form
    m_cityNameInput = new QLineEdit();
    m_cityNameInput->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    auto getWeatherForCityButton = new QPushButton("Get Weather");
    viewLayout->addWidget(m_cityNameInput);
    viewLayout->addWidget(getWeatherForCityButton);

    // Create temperature output form
    auto weatherData = new QWidget();
    auto weatherDataContainer = new QHBoxLayout;
    weatherDataContainer->addWidget(new QLabel("Temperature:"));
    weatherDataContainer->addWidget(m_temperature);
    weatherData->setLayout(weatherDataContainer);
    viewLayout->addWidget(weatherData);

    // Assign created layout to this class (QWidget)
    this->setLayout(viewLayout);

    // Configure slots
    connect(getWeatherForCityButton, SIGNAL(clicked()), this, SLOT(onClickGetWeather()));
    connect(m_cityNameInput, SIGNAL(editingFinished()), this, SLOT(onClickGetWeather()));
}

/**
 * Return temperature for desired city
 * @param cityName name of the city as QString
 * @return QString with temperature or error message
 */
QString WeatherView::getWeatherForCity(const QString& cityName) {
    // Create custom temporary event loop
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // Configure HTTP request
    QNetworkRequest req(QUrl(
    QString("http://api.weatherapi.com/v1/current.json?key=102159d41c644319a60173651212512&q=%1&aqi=no").arg(cityName)
    ));
    QNetworkReply* reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    // Convert reply to JSON object
    QByteArray replyData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyData);
    QJsonObject jsonObj = jsonResponse.object();

    // Parse temperature
    QString temperature;
    if (!reply->error()){
        QJsonObject current = jsonObj.value("current").toObject();
        double temperature_value = current.value("temp_c").toDouble();
        temperature = QString::number(temperature_value);
    } else {
        QJsonObject error = jsonObj.value("error").toObject();
        temperature = error.value("message").toString();
    }
    delete reply;
    return temperature;
}

/**
 * Get temperature for desired city and update the label
 */
void WeatherView::onClickGetWeather() {
    QString city = this->m_cityNameInput->text();
    QString temperature = this->getWeatherForCity(city);
    m_temperature->setText(temperature);
}
