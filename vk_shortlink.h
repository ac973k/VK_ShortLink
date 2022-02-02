#ifndef VK_SHORTLINK_H
#define VK_SHORTLINK_H

#include <QWidget>

#include <QPushButton> //класс кнопок
#include <QLabel>
#include <QTextEdit> //класс текстового окна
#include <QGridLayout> //класс верстки
#include <QLineEdit>

#include <QNetworkAccessManager> //класс для работы с сетью

class VK_ShortLink : public QWidget
{
    Q_OBJECT

public:
    VK_ShortLink(QWidget *parent = nullptr);
    ~VK_ShortLink();

private:
    QString token; //токен авторизации
    QString user_id; //id пользователя
    QString link; //сообщение

    QGridLayout *SLLayout; //верстка

    QPushButton *btnShortLink; //кнопка отправить


    QLabel *lblLink; //текст
    QLineEdit *lineLink;

    QTextEdit *textSL; //поле, куда будем писать наше сообщение

    QNetworkAccessManager *networkManager; //инициализируем сетевой менеджер

private slots:
    void getLink(); //метод, который отправляет запись на стену
    void onResult(QNetworkReply *reply); //вывод результата
};
#endif // VK_SHORTLINK_H
