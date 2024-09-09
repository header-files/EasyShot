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
    int delX = nowPoint.x() - moveStart.x();
    int delY = nowPoint.y() - moveStart.y();

    if((leftUp.x() + delX) < 0){
        rightDown.setX(rightDown.x() - leftUp.x());
        leftUp.setX(0);
    }else{
        leftUp.setX(leftUp.x() + delX);
    }

    if((leftUp.y() + delY) < 0){
        rightDown.setY(rightDown.y() - leftUp.y());
        leftUp.setY(0);
    }else{
        leftUp.setY(leftUp.y() + delY);
    }

    if((rightDown.x() + delX) > screenW){
        leftUp.setX(screenW - (rightDown.x() - leftUp.x()));
        rightDown.setX(screenW);
    }else{
        rightDown.setX(rightDown.x() + delX);
    }

    if((rightDown.y() + delY) > screenH){
        rightDown.setY(screenH - (rightDown.y() - leftUp.y()));
        rightDown.setY(screenH);
    }else{
        rightDown.setY(rightDown.y() + delY);
    }
}

// 检查起点以及终点坐标是否符合一个在左上一个在右下
void ShotArea::checkArea()
{
    int startX = leftUp.x();
    int startY = leftUp.y();

    int endX = rightDown.x();
    int endY = rightDown.y();

    int temp = 0;
    if(startX > endX){
        temp = startX;
        leftUp.setX(rightDown.x());
        rightDown.setX(temp);
    }

    if(startY > endY){
        temp = startY;
        leftUp.setY(rightDown.y());
        rightDown.setY(temp);
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

void ShotArea::setMoveStart(QPoint moveStart)
{
    this->moveStart = moveStart;
}
QPoint ShotArea::getMoveStart()
{
    return moveStart;
}
