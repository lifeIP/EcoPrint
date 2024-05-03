#ifndef LISTPAGE_H
#define LISTPAGE_H

#include <QWidget>

namespace Ui {
class ListPage;
}

class ListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ListPage(QWidget *parent = nullptr);
    ~ListPage();

private:
    Ui::ListPage *ui;
};

#endif // LISTPAGE_H
