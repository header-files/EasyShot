#include "shotarea.h"

ShotArea::ShotArea()
{
}

// 判断鼠标是否在截图区域内
bool ShotArea::ifInArea(QPoint point)
{
    int x = point.x();
    int y = point.y();

    return (x >= leftUp.x() && x <= rightDown.x() &&
            y >= leftUp.y() && y <= rightDown.y());
}

// 更新截图区域坐标
void ShotArea::updateArea(QPoint nowPoint)
{
    checkArea(); // 先检查左上以及右下坐标是否符合要求

    int delX = nowPoint.x() - moveStart.x();
    int delY = nowPoint.y() - moveStart.y();

    leftUp.setX(leftUp.x() + delX);
    leftUp.setY(leftUp.y() + delY);
    rightDown.setX(rightDown.x() + delX);
    rightDown.setY(rightDown.y() + delY);

    if(leftUp.x() < 0){
        rightDown.setX(rightDown.x() - leftUp.x());
        leftUp.setX(0);
    }

    if(leftUp.y() < 0){
        rightDown.setY(rightDown.y() - leftUp.y());
        leftUp.setY(0);
    }

    if(rightDown.x() > screenW){
        leftUp.setX(screenW - (rightDown.x() - leftUp.x()));
        rightDown.setX(screenW);
    }

    if(rightDown.y() > screenH){
        leftUp.setY(screenH - (rightDown.y() - leftUp.y()));
        rightDown.setY(screenH);
    }

    shotStart.setX(leftUp.x()); // 修改截图区域起点坐标，防止影响后面的 checkArea
    shotStart.setY(leftUp.y());
}

// 检查起点以及终点坐标是否符合一个在左上一个在右下
void ShotArea::checkArea()
{
    int startX = shotStart.x();
    int startY = shotStart.y();

    int endX = rightDown.x();
    int endY = rightDown.y();

    if(startX > endX){
        leftUp.setX(endX);
        rightDown.setX(startX);
    }

    if(startY > endY){
        leftUp.setY(endY);
        rightDown.setY(startY);
    }
}


void ShotArea::setScreenW(int w)
{
    screenW = w;
}
int ShotArea::getScreenW()
{
    return screenW;
}

void ShotArea::setScreenH(int h)
{
    screenH = h;
}
int ShotArea::getScreenH()
{
    return screenH;
}


void ShotArea::setStatus(STATUS status)
{
    this->status = status;
}
ShotArea::STATUS ShotArea::getStatus()
{
    return status;
}

void ShotArea::setLeftUp(QPoint leftUp)
{
    this->leftUp = leftUp;
}
QPoint ShotArea::getLeftUp()
{
    return leftUp;
}

void ShotArea::setRightDown(QPoint rightDown)
{
    this->rightDown = rightDown;
}
QPoint ShotArea::getRightDown()
{
    return rightDown;
}


void ShotArea::setShotStart(QPoint shotStart)
{
    this->shotStart = shotStart;
}
QPoint ShotArea::getShotStart()
{
    return shotStart;
}

void ShotArea::setMoveStart(QPoint moveStart)
{
    this->moveStart = moveStart;
}
QPoint ShotArea::getMoveStart()
{
    return moveStart;
}
