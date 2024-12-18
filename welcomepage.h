#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>

namespace Ui {
class WelcomePage;
}

class WelcomePage : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage();

private slots:
    void on_pushButton_pressed();
    void slot_restart();
signals:
    void signal_pushButton_pressed();
private:
    Ui::WelcomePage *ui;
};

#endif // WELCOMEPAGE_H
