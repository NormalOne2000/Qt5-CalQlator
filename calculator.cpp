#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(0.0));
    calcMemory = {0.0};
    presentVal = 0.0;
    recentSymbol = '\0';
    signTable = "/*+-";
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i){
        QString bName = "Button"+QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton*>(bName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton*)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    }else{
        QString newVal = displayVal+butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed(){
    QString dispVal = ui->Display->text();
    presentVal = dispVal.toDouble();
    QPushButton *button = (QPushButton*)sender();
    QString butVal = button->text();
    recentSymbol = (butVal.toStdString())[0];
    ui->Display->setText(butVal);
}

void Calculator::EqualButton(){
    double solution = presentVal;
    QString dispVal = ui->Display->text();
    double dblDispVal = dispVal.toDouble();

    switch(signTable.find(recentSymbol)){
    case 0:{
        solution /= dblDispVal;
        break;
    }
    case 1:{
        solution *= dblDispVal;
        break;
    }
    case 2:{
        solution += dblDispVal;
        break;
    }
    case 3:{
        solution -= dblDispVal;
        break;
    }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString dispVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(dispVal)){
        ui->Display->setText(QString::number(-1*(dispVal.toDouble())));
    }
}

void Calculator::on_Clear_released()
{
    calcMemory.clear();
    calcMemory.push_back(0.0);
    ui->Display->setText(QString::number(0));
}

void Calculator::on_MemAdd_released()
{
    calcMemory.push_back((ui->Display->text()).toDouble());
    ui->Display->clear();
}

void Calculator::on_MemClear_released()
{
    if(!calcMemory.empty())
        calcMemory.pop_back();
    else
        calcMemory.push_back(0.0);
}

void Calculator::on_MemGet_released()
{
    ui->Display->setText(QString::number(calcMemory.back()));
}
