#include "calculator.h"
#include "ui_calculator.h"



Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Ekran->setText(QString::number(vrijednost));
    ui->Ekran->setEnabled(false);

    QPushButton *brojeviButtons[10];

    for(int i = 0; i < 10; ++i)
    {
        QString imeButton = "Button" + QString::number(i);
        brojeviButtons[i] = Calculator::findChild<QPushButton *>(imeButton);
        connect(brojeviButtons[i], SIGNAL(released()), this, SLOT(StisnutBroj()));
    }

connect(ui->Plus, SIGNAL(released()), this, SLOT(StisnutMatBroj()));
connect(ui->Minus, SIGNAL(released()), this, SLOT(StisnutMatBroj()));
connect(ui->Mnozi, SIGNAL(released()), this, SLOT(StisnutMatBroj()));
connect(ui->Dijeli, SIGNAL(released()), this, SLOT(StisnutMatBroj()));
connect(ui->Jednako, SIGNAL(released()), this, SLOT(StisnutJednako()));
connect(ui->MjenjajZnak, SIGNAL(released()), this, SLOT(StisnutPromjeniZnak()));
connect(ui->Cisti, SIGNAL(released()), this, SLOT(StisnutCisti()));
connect(ui->Tocka, SIGNAL(released()), this, SLOT(StisnutTocka()));
connect(ui->Brisi, SIGNAL(released()), this, SLOT(StisnutBrisi()));


}


Calculator::~Calculator()
{
    delete ui;
}

void Calculator::StisnutBroj()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVrijednost = button->text();
    QString ekranVrijednost = ui->Ekran->text();

    if(ekranVrijednost.toDouble() == 0)
        {
        ui->Ekran->setText(butVrijednost);
        }
    else
    {
        QString novaVrijednost = ekranVrijednost + butVrijednost;
        ui->Ekran->setText(novaVrijednost);
    }
}

void Calculator::StisnutMatBroj()
{
    dijeliTrig = false;
    mnoziTrig = false;
    plusTrig = false;
    minusTrig = false;

    QString ekranVrijednost = ui->Ekran->text();
    vrijednost = ekranVrijednost.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVrijednost = button->text();

    if(butVrijednost == "/")
        dijeliTrig = true;
    else if(butVrijednost == "*")
        mnoziTrig = true;
    else if(butVrijednost == "+")
        plusTrig = true;
    else
        minusTrig = true;
    ui->Ekran->setText(ekranVrijednost+butVrijednost);
}

void Calculator::StisnutJednako()
{
    double rjesenje;

    QString ekranVrijednost = ui->Ekran->text();
    double dblEkranVrijednost = ekranVrijednost.toDouble();

    if(plusTrig || minusTrig || mnoziTrig || dijeliTrig)
        {
        if(plusTrig)
            rjesenje = vrijednost + dblEkranVrijednost;
        else if(minusTrig)
            rjesenje = vrijednost - dblEkranVrijednost;
        else if(mnoziTrig)
            rjesenje = vrijednost * dblEkranVrijednost;
        else
            rjesenje = vrijednost / dblEkranVrijednost;
        }
    else
        rjesenje = dblEkranVrijednost;
    if(rjesenje == dblEkranVrijednost)
        ui->Ekran->setText(QString::number(dblEkranVrijednost));
    else
        ui->Ekran->setText(QString::number(rjesenje));
    dijeliTrig = false;
    mnoziTrig = false;
    plusTrig = false;
    minusTrig = false;
}

void Calculator::StisnutPromjeniZnak()
{
    QString ekranVrijednost = ui->Ekran->text();

    QRegExp reg("[-+]?[0-9.]*");

    if(ekranVrijednost.contains('/',Qt::CaseSensitive) || ekranVrijednost.contains('*',Qt::CaseSensitive) || ekranVrijednost.contains('+',Qt::CaseSensitive) || ekranVrijednost.contains('-',Qt::CaseSensitive))
        ekranVrijednost.chop(1);

    if(reg.exactMatch(ekranVrijednost))
        {
            double dblEkranVrijednost = ekranVrijednost.toDouble();
            dblEkranVrijednost *= -1;
            ui->Ekran->setText(QString::number(dblEkranVrijednost));
        }
}

void Calculator::StisnutCisti()
{
    ui->Ekran->clear();
    ui->Ekran->setText("0");

}

void Calculator::StisnutTocka()
{
    QString ekranVrijednost = ui->Ekran->text();
    if(ekranVrijednost.length() >= (DIGIT_LIMIT - 1) || ekranVrijednost.contains('.',Qt::CaseSensitive))
        return;
    if(ekranVrijednost.length() == 0)
        ekranVrijednost = "0";
    ekranVrijednost.append('.');
    ui->Ekran->setText(ekranVrijednost);
}

void Calculator::StisnutBrisi()
{
    QString ekranVrijednost = ui->Ekran->text();
    ekranVrijednost.QString::chop(1);
    ui->Ekran->setText(ekranVrijednost);
    if(ekranVrijednost.length() == 0)
        ui->Ekran->setText("0");

}

