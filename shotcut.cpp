#include "shotcut.h"

ShotCut::ShotCut(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    showFullScreen();
}

ShotCut::~ShotCut()
{
    delete bgImg;
}

// 获取全屏截图
QPixmap ShotCut::captureScreen()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
    {
        return QPixmap();
    }

    QRect rect = screen->geometry();
    return screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());
}

// 重写窗口显示事件（窗口初次显示或重新显示）
void ShotCut::showEvent(QShowEvent *enent)
{
    screenShot = captureScreen();

    // 调整窗口大小以匹配截图
    resize(screenShot.size());

    // 为全屏图片设置遮挡
    bgImg = new QPixmap(screenShot);
    QPainter painter(bgImg);
    // 添加灰色不透明遮挡
    QPixmap grayPix(screenShot.size().width(), screenShot.size().height());
    grayPix.fill((QColor(127,127,127,100))); // 灰色， 透明度 100
    painter.drawPixmap(0, 0, grayPix);
}

// 重写绘图事件（窗口更新）
void ShotCut::paintEvent(QPaintEvent *enent){
    QPainter painter(this);
    painter.drawPixmap(rect(), *bgImg);
}

// 重写keyPressEvent以处理ESC键
void ShotCut::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Escape) {
        hide();
    } else {
        QWidget::keyPressEvent(event);
    }
}
