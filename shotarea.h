#ifndef SHOTAREA_H
#define SHOTAREA_H

#include<QPoint>

// 截图区域
class ShotArea
{
public:
    ShotArea();

    // 截图区域状态
    // 未选择， 已设置起点（左上）， 已设置终点（右下）， 拖拽区域
    enum STATUS{N_SELECT, START, END, MOVE};

    // 判断鼠标是否在截图区域内
    bool ifInArea(QPoint point);

    // 更新截图区域坐标
    void updateArea(QPoint nowPoint);

    // 检查起点以及终点坐标是否符合一个在左上一个在右下
    void checkArea();

    void setScreenW(int w);
    int getScreenW();

    void setScreenH(int h);
    int getScreenH();

    void setStatus(STATUS status);
    STATUS getStatus();

    void setLeftUp(QPoint leftUp);
    QPoint getLeftUp();

    void setRightDown(QPoint rightDown);
    QPoint getRightDown();

    void setShotStart(QPoint shotStart);
    QPoint getShotStart();

    void setMoveStart(QPoint moveStart);
    QPoint getMoveStart();

private:
    STATUS status; // 截图区域状态

    int screenW, screenH; // 屏幕宽、高

    QPoint leftUp, rightDown, shotStart, moveStart; // 截图区域左上以及右下坐标、截图区域起点、拖拽起始坐标
};

#endif // SHOTAREA_H
