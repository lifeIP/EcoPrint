#include "listpage.h"
#include "ui_listpage.h"

ListPage::ListPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListPage)
{
    ui->setupUi(this);
}

ListPage::~ListPage()
{
    delete ui;
}
