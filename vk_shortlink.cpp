#include "vk_shortlink.h"

#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

VK_ShortLink::VK_ShortLink(QWidget *parent)
    : QWidget(parent)
{
    SLLayout = new QGridLayout; //инициализируем верстку

    lblLink = new QLabel("Enter Link: "); //тексты

    lineLink = new QLineEdit;

    textSL = new QTextEdit; //тут будет ссылка сокращенная

    btnShortLink = new QPushButton("Get Link"); //кнопка получения ссылки

    token = ""; //сюда вставляем свой access_token

    SLLayout->addWidget(lblLink, 0, 0); //распологаем кнопки и всякие виджеты как нам удобно
    SLLayout->addWidget(lineLink, 1, 0);
    SLLayout->addWidget(textSL, 2, 0, 1, 2);
    SLLayout->addWidget(btnShortLink, 3, 0, 1, 2);

    setLayout(SLLayout); //показываем то, как все красиво мы сделали

    QObject::connect(btnShortLink, SIGNAL(clicked()), this, SLOT(getLink())); //вызываем метод отправки записи на стену
}

VK_ShortLink::~VK_ShortLink()
{
    delete networkManager;
    delete btnShortLink;
    delete textSL;
    delete lineLink;
    delete lblLink;
    delete SLLayout;
}

void VK_ShortLink::getLink()
{
    networkManager = new QNetworkAccessManager(); //инициализируем сетевой манагер

    link = lineLink->text(); //поле ввода текста

    QString url; //тут будет наш URL адрес

    url = "https://api.vk.com/method/utils.getShortLink?url=" + link + "&access_token=" + token + "&v=5.126";

    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*))); //отправляем данные и получаем ответ от вк успешно или ошибка
    networkManager->get(QNetworkRequest(url));
}

void VK_ShortLink::onResult(QNetworkReply *reply)
{
    #ifdef QT_DEBUG
        qDebug() << "Running a debug build";
    #else
        qDebug() << "Running a release build";
    #endif

    // Если ошибки отсутсвуют
    if(!reply->error())
    {
        QString str = reply->readAll();
        str.replace("\\", "");

        #ifdef QT_DEBUG
            textSL->append(str);
        #else
            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject json = doc.object();
            QJsonObject texts = json.value("response").toObject();
            QJsonValue jv = texts.value("short_url");

            textSL->clear();;
            textSL->append(jv.toString()); //результат работы выводим
        #endif
        reply->deleteLater();
    }
    else {
        textSL->setText(reply->errorString());
    }
    reply->deleteLater();
}
