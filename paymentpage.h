#ifndef PAYMENTPAGE_H
#define PAYMENTPAGE_H

#include <QWidget>

namespace Ui {
class PaymentPage;
}

class PaymentPage : public QWidget
{
    Q_OBJECT

public:
    explicit PaymentPage(QWidget *parent = nullptr);
    ~PaymentPage();

private:
    Ui::PaymentPage *ui;
};

#endif // PAYMENTPAGE_H
