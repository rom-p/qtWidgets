#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qanimatedtimer.h"
//#include "qvumeter.h"

namespace Ui
{
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void onStartClicked();
    void onStopClicked();
    void onPauseClicked();
    void onFadeClicked();
    void onYellowChanged(int); // user changes the yellow threshold
    void onRedChanged(int);    // user changes the red threshold

protected:
    void resizeEvent(QResizeEvent *);
    void recalcLabels();

private:
    Ui::MainWindow *ui;
    bool _timerVisible;
};

#endif // MAINWINDOW_H
