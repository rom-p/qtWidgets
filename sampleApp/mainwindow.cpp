#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _timerVisible(true)
    , _vuPlaying(false)
{
    ui->setupUi(this);

    ui->_fadeDuration->setValue(1.5);
    ui->_fadeDuration->setSingleStep(.1);
    ui->_yellowThreshold->setValue(ui->_timer->yellowThreshold());
    ui->_redThreshold->setValue(ui->_timer->redThreshold());
    recalcLabels();

    // animated timer section
    connect(ui->_start, SIGNAL(clicked()), this, SLOT(onStartClicked()));
    connect(ui->_stop, SIGNAL(clicked()), this, SLOT(onStopClicked()));
    connect(ui->_pause, SIGNAL(clicked()), this, SLOT(onPauseClicked()));
    connect(ui->_fade, SIGNAL(clicked()), this, SLOT(onFadeClicked()));
    connect(ui->_yellowThreshold, SIGNAL(valueChanged(int)), this, SLOT(onYellowChanged(int)));
    connect(ui->_redThreshold, SIGNAL(valueChanged(int)), this, SLOT(onRedChanged(int)));

    // vu meter section
    connect(ui->_enable, SIGNAL(clicked()), this, SLOT(onEnableVU()));
    connect(ui->_disable, SIGNAL(clicked()), this, SLOT(onDisableVU()));
    connect(ui->_play, SIGNAL(clicked()), this, SLOT(onPlayVU()));
    connect(ui->_vuMeter, SIGNAL(selectionChanged(float)), this, SLOT(onSelectionChanged(float)));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onStartClicked()
{
    ui->_timer->start();
}


void MainWindow::onStopClicked()
{
    ui->_timer->stop();
}


void MainWindow::onPauseClicked()
{
    ui->_timer->pause();
}


void MainWindow::onFadeClicked()
{
    ui->_fade->setText(_timerVisible ? "Fade In" : "Fade Out");
    if (_timerVisible)
    {
        ui->_timer->fadeOut(ui->_fadeDuration->value());
    }
    else
    {
        ui->_timer->fadeIn(ui->_fadeDuration->value());
    }
    _timerVisible = !_timerVisible;
}


void MainWindow::onYellowChanged(int val)
{
    ui->_timer->setYellowThreshold(val);
    if (ui->_redThreshold->value() < val)
    {
        ui->_redThreshold->setValue(val);
    }
    recalcLabels();
}


void MainWindow::onRedChanged(int val)
{
    ui->_timer->setRedThreshold(val);
    if (ui->_yellowThreshold->value() > val)
    {
        ui->_yellowThreshold->setValue(val);
    }
    recalcLabels();
}


void MainWindow::onEnableVU()
{
    ui->_vuMeter->setDimmed(false);
}


void MainWindow::onDisableVU()
{
    ui->_vuMeter->setDimmed(true);
}


void MainWindow::onPlayVU()
{
    _vuClock.start(100, this);
}


void MainWindow::onSelectionChanged(float val)
{
    ui->_selection->setText(QString::number(val));
}


void MainWindow::timerEvent(QTimerEvent *event)
{
    static float val = 0;
    val = qBound(0.f, val + rand() % 30 - 15, 100.f);
    ui->_vuMeter->setValue(val);
}


void MainWindow::recalcLabels()
{
    QString yellow("yellow zone starts at ");
    yellow.append(QString::number(ui->_yellowThreshold->value()));
    yellow.append(" sec");
    ui->_yellowLabel->setText(yellow);

    QString red("red zone starts at ");
    red.append(QString::number(ui->_redThreshold->value()));
    red.append(" sec");
    ui->_redLabel->setText(red);
}

