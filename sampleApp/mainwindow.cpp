#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _timerVisible(true)
{
    ui->setupUi(this);

    ui->_fadeDuration->setValue(1.5);
    ui->_fadeDuration->setSingleStep(.1);
    ui->_yellowThreshold->setValue(ui->_timer->yellowThreshold());
    ui->_redThreshold->setValue(ui->_timer->redThreshold());
    recalcLabels();

    connect(ui->_start, SIGNAL(clicked()), this, SLOT(onStartClicked()));
    connect(ui->_stop, SIGNAL(clicked()), this, SLOT(onStopClicked()));
    connect(ui->_pause, SIGNAL(clicked()), this, SLOT(onPauseClicked()));
    connect(ui->_fade, SIGNAL(clicked()), this, SLOT(onFadeClicked()));
    connect(ui->_yellowThreshold, SIGNAL(valueChanged(int)), this, SLOT(onYellowChanged(int)));
    connect(ui->_redThreshold, SIGNAL(valueChanged(int)), this, SLOT(onRedChanged(int)));
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
    if (_timerVisible)
    {
        ui->_timer->fadeOut(ui->_fadeDuration->value());
        ui->_fade->setText("Fade In");
    }
    else
    {
        ui->_timer->fadeIn(ui->_fadeDuration->value());
        ui->_fade->setText("Fade Out");
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


void MainWindow::resizeEvent(QResizeEvent */*pEvent*/)
{
    QRect sz;
    QRect g = ui->_fieldSpacer->geometry();

    sz.setRect((g.width() - 80) / 2, (g.height() - 80) / 2, 80, 80);
    ui->_timer->setGeometry(sz);
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

