#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    double vrijednost = 0.0;

    bool dijeliTrig = false;
    bool mnoziTrig = false;
    bool plusTrig = false;
    bool minusTrig = false;

private:
    Ui::Calculator *ui;


private slots:
    void StisnutPromjeniZnak();
    void StisnutBroj();
    void StisnutMatBroj();
    void StisnutJednako();
    void StisnutCisti();


};

#endif // CALCULATOR_H
