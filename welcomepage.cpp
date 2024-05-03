#include "welcomepage.h"
#include "ui_welcomepage.h"

WelcomePage::WelcomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomePage)
{
    ui->setupUi(this);
}

WelcomePage::~WelcomePage()
{
    delete ui;
}

void WelcomePage::on_pushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    signal_pushButton_pressed();
}

void WelcomePage::slot_restart()
{
    ui->stackedWidget->setCurrentIndex(0);
}

