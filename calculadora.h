#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <QMainWindow>

namespace Ui {
class Calculadora;
}

class Calculadora : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculadora(QWidget *parent = nullptr);
    ~Calculadora();

private slots:
    void NumClicked();
    void OperatorClicked();
    void EqualClicked();
    void PointClicked();
    void ChangeSignClicked();
    void BackSpaceClicked();
    void ClearClicked();
    void ClearAllClicked();


    void FirstRingClicked();
    void SecondRingClicked();
    void MultiplierClicked();
    void ToleranceClicked();
    void EnterClicked();
    void EnterColorsClicked();

private:
    Ui::Calculadora *ui;
};

#endif // CALCULADORA_H
