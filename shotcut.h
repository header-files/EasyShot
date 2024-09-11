#ifndef SHOTCUT_H
#define SHOTCUT_H

#include "shotarea.h"

#include <QWidget>
#include <QPaintEvent>

class ShotCut : public QWidget
{
    Q_OBJECT
public:
    explicit ShotCut(QWidget *parent = nullptr);
    ~ShotCut();

signals:

protected:
    // 获取全屏截图
    QPixmap captureScreen();

    // 重写窗口显示事件（窗口初次显示或重新显示）
    void showEvent(QShowEvent *event) override;
    // 重写绘图事件（窗口更新）
    void paintEvent(QPaintEvent *event) override;

    // 重写keyPressEvent以处理ESC键
    void keyPressEvent(QKeyEvent *event) override;

    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;
    // 重写鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override;
    // 重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPixmap screenShot; // 全屏对象
    QPixmap* bgImg; // 遮挡
    ShotArea shotArea; // 截图区域
};

#endif // SHOTCUT_H
