#include "paymentpage.h"
#include "ui_paymentpage.h"

PaymentPage::PaymentPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaymentPage)
{
    ui->setupUi(this);
}

PaymentPage::~PaymentPage()
{
    delete ui;
}
