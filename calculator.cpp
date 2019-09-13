#include "calculator.h"
#include "ui_calculator.h"



Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Ekran->setText(QString::number(vrijednost));

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

    if((ekranVrijednost.toDouble() == 0) || (ekranVrijednost.toDouble() == 0.0))
        {
        ui->Ekran->setText(butVrijednost);
        }
    else
    {
        QString novaVrijednost = ekranVrijednost + butVrijednost;
        double dblNovaVrijednost = novaVrijednost.toDouble();
        ui->Ekran->setText(QString::number(dblNovaVrijednost, 'g', 16));
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

    if(QString::compare(butVrijednost, "/", Qt::CaseSensitive) == 0)
        dijeliTrig = true;
    else if(QString::compare(butVrijednost, "*", Qt::CaseSensitive) == 0)
        mnoziTrig = true;
    else if(QString::compare(butVrijednost, "+", Qt::CaseSensitive) == 0)
        plusTrig = true;
    else
        minusTrig = true;
    ui->Ekran->setText("");
}

void Calculator::StisnutJednako()
{
    double rjesenje = 0.0;

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
    ui->Ekran->setText(QString::number(rjesenje));
}

void Calculator::StisnutPromjeniZnak()
{
    QString ekranVrijednost = ui->Ekran->text();
    QRegExp reg("[-+]?[0-9.]*");

    if(reg.exactMatch(ekranVrijednost))
        {
            double dblEkranVrijednost = ekranVrijednost.toDouble();
            double dblEkranVrijednostZnak = -1 * dblEkranVrijednost;
            ui->Ekran->setText(QString::number(dblEkranVrijednostZnak));
        }
}

void Calculator::StisnutCisti()
{
    double rjesenje = 0.0;
    ui->Ekran->setText(QString::number(rjesenje));

}

