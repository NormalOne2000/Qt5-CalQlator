#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    double presentVal;
    std::vector<double> calcMemory;
    char recentSymbol;
    std::string signTable;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
    void on_Clear_released();
    void on_MemAdd_released();
    void on_MemClear_released();
    void on_MemGet_released();
};

#endif // CALCULATOR_H
