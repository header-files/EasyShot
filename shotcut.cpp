#include "shotcut.h"

ShotCut::ShotCut(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    showFullScreen();

    shotArea.setStatus(ShotArea::N_SELECT);

    QSize screenSize = QGuiApplication::primaryScreen()->size();

    shotArea.setScreenW(screenSize.width());
    shotArea.setScreenH(screenSize.height());

    QPoint point(-1, -1);
    shotArea.setLeftUp(point);
    shotArea.setRightDown(point);
    shotArea.setMoveStart(point);
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
    // 添加灰色透明遮挡
    QPixmap grayPix(screenShot.size().width(), screenShot.size().height());
    grayPix.fill((QColor(127,127,127,100))); // 灰色， 透明度 100
    painter.drawPixmap(0, 0, grayPix);
}

// 重写绘图事件（窗口更新）
void ShotCut::paintEvent(QPaintEvent *enent){
    QPainter painter(this);
    painter.drawPixmap(rect(), *bgImg); // 显示带灰色透明遮挡全屏图片

    shotArea.checkArea(); // 检查并修正截图区域坐标

    QPoint leftUp = shotArea.getLeftUp();
    QPoint rightDown = shotArea.getRightDown();

    int startX = leftUp.x();
    int startY = leftUp.y();

    int areaW = rightDown.x() - startX;
    int areaH = rightDown.y() - startY;

    // 显示截图区域
    painter.drawPixmap(startX, startY,
                       screenShot.copy(startX, startY, areaW, areaH));

    // 沿截图区域绘制矩形框
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);

    painter.setPen(pen);
    painter.drawRect(startX, startY, areaW, areaH);
}

// 重写keyPressEvent以处理ESC键
void ShotCut::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Escape) {
        hide();
    } else {
        QWidget::keyPressEvent(event);
    }
}

// 重写鼠标按下事件
void ShotCut::mousePressEvent(QMouseEvent *event)
{
    QPoint globalPos = event->globalPos(); // 鼠标相对于屏幕的坐标
    ShotArea::STATUS status = shotArea.getStatus();

    if(status == ShotArea::N_SELECT){ // 未选择，按下鼠标，设置起点
        shotArea.setLeftUp(globalPos);
        shotArea.setStatus(ShotArea::START);
    }else if(status == ShotArea::END){ // 已设置终点，按下鼠标
        if(shotArea.ifInArea(globalPos)){ // 在选择区域内，拖拽区域
            shotArea.setMoveStart(globalPos); // 设置拖拽起始点
            shotArea.setStatus(ShotArea::MOVE);
        }else{ // 在区域外，重新设置起点
            shotArea.setLeftUp(globalPos);
            shotArea.setStatus(ShotArea::START);
        }
    }

    update();
}

// 重写鼠标释放事件
void ShotCut::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint globalPos = event->globalPos();
    ShotArea::STATUS status = shotArea.getStatus();

    if(status == ShotArea::START){ // 已设置起点，释放鼠标，设置终点
        shotArea.setRightDown(globalPos);
        shotArea.setStatus(ShotArea::END);
    }else if(status == ShotArea::MOVE){ // 拖拽结束，返回已设置终点状态
        shotArea.setStatus(ShotArea::END);
    }

    update();
}

// 重写鼠标移动事件
void ShotCut::mouseMoveEvent(QMouseEvent *event)
{
    ShotArea::STATUS status = shotArea.getStatus();

    if(status == ShotArea::MOVE){ // 已设置拖拽起点，实时更新截图区域坐标
        QPoint globalPos = event->globalPos();
        shotArea.updateArea(globalPos);
    }

    update();
}
