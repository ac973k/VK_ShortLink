#include "vk_shortlink.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VK_ShortLink w;
    w.show();
    return a.exec();
}
