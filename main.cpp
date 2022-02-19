#include "vk_shortlink.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion("20220219");
    a.setApplicationName("VK ShrotLink");
    a.setApplicationDisplayName("VK ShortLink");

    VK_ShortLink w;
    w.show();
    return a.exec();
}
