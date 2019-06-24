#include "calculadora.h"
#include "ui_calculadora.h"
#include <QLCDNumber>
#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <math.h>

static double CalcValue = 0.0;
static bool divTrigger = false;
static bool multTrigger = false;
static bool addTrigger = false;
static bool subTrigger = false;
static bool inverseTrigger = false;
static bool squaredTrigger = false;
static bool sqrtTrigger = false;

static QString firstring;
static QString secondring;
static QString multiplier;
static QString tolerance;
static QString colors = "";
static double resistor = 0.0;
static double resistor1 = 0.0;
static double resistor2 = 0.0;
static double resistor3 = 0.0;

const QString Brown = "background-color:rgb(170,85,0);";
static QString Red = "background-color:rgb(255,0,0);";
static QString Orange = "background-color:rgb(255,85,0);";
static QString Yellow = "background-color:rgb(255,255,0);";
static QString Green = "background-color:rgb(0,170,0);";
static QString Blue = "background-color:rgb(0,0,255);";
static QString White = "background-color:rgb(255,255,255);";
static QString Gray = "background-color: rgb(140,140,105);";
static QString Silver = "background-color:rgb(179,179,134);";
static QString Gold= "background-color:rgb(239,206,15);";
static QString Purple = "background-color:rgb(170,0,127);";
static QString Black = "background-color:rgb(0,0,0);";

Calculadora::Calculadora(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculadora)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/heloi/Desktop/Resistor.png");
    ui->label_image->setPixmap(pix);

    ui->label_edit->setText(QString::number(CalcValue));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++){
        QString butName = "_" + QString::number(i);
        numButtons[i] = Calculadora::findChild<QPushButton*>(butName);
        connect(numButtons[i], SIGNAL(clicked()), this,
                SLOT(NumClicked()));
    }

    connect(ui->_Sum, SIGNAL(clicked()), this, SLOT(OperatorClicked()));
    connect(ui->_DIV, SIGNAL(clicked()), this, SLOT(OperatorClicked()));
    connect(ui->_Multiplier, SIGNAL(clicked()), this, SLOT(OperatorClicked()));
    connect(ui->_Less, SIGNAL(clicked()), this, SLOT(OperatorClicked()));
    connect(ui->_SQRT, SIGNAL(clicked()), this, SLOT(OperatorClicked()));
    connect(ui->_Squared, SIGNAL(clicked()), this, SLOT(OperatorClicked()));
    connect(ui->_Inverse, SIGNAL(clicked()), this, SLOT(OperatorClicked()));

    connect(ui->_Point, SIGNAL(clicked()), this, SLOT(PointClicked()));
    connect(ui->_Equal, SIGNAL(clicked()), this, SLOT(EqualClicked()));
    connect(ui->_ChangeSign, SIGNAL(clicked()), this, SLOT(ChangeSignClicked()));
    connect(ui->_BackSpace, SIGNAL(clicked()), this, SLOT(BackSpaceClicked()));
    connect(ui->_Clear, SIGNAL(clicked()), this, SLOT(ClearClicked()));
    connect(ui->_ClearAll, SIGNAL(clicked()), this, SLOT(ClearAllClicked()));

    connect(ui->_Brown1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));
    connect(ui->_Red1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));
    connect(ui->_Orange1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));
    connect(ui->_Yellow1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));
    connect(ui->_Green1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));
    connect(ui->_Blue1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));
    connect(ui->_Purple1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));
    connect(ui->_Gray1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));
    connect(ui->_White1, SIGNAL(clicked()), this, SLOT(FirstRingClicked()));

    connect(ui->_Black2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_Brown2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_Red2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_Orange2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_Yellow2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_Green2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_Blue2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_Purple2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_Gray2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));
    connect(ui->_White2, SIGNAL(clicked()), this, SLOT(SecondRingClicked()));

    connect(ui->_Black3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));
    connect(ui->_Brown3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));
    connect(ui->_Red3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));
    connect(ui->_Orange3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));
    connect(ui->_Yellow3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));
    connect(ui->_Green3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));
    connect(ui->_Silver3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));
    connect(ui->_Gold3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));
    connect(ui->_Blue3, SIGNAL(clicked()), this, SLOT(MultiplierClicked()));

    connect(ui->_Gray4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));
    connect(ui->_Brown4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));
    connect(ui->_Red4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));
    connect(ui->_Purple4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));
    connect(ui->_Blue4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));
    connect(ui->_Green4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));
    connect(ui->_Silver4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));
    connect(ui->_Gold4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));
    connect(ui->_Black4, SIGNAL(clicked()), this, SLOT(ToleranceClicked()));

    connect(ui->_Enter, SIGNAL(clicked()), this, SLOT(EnterClicked()));
    connect(ui->_EnterColors, SIGNAL(clicked()), this, SLOT(EnterColorsClicked()));
}

Calculadora::~Calculadora()
{
    delete ui;
}

void Calculadora::NumClicked()
{
      //Sender returns a pointer to the button pressed
      QPushButton *button = static_cast<QPushButton *>(sender());
      // Get number on button pressed
      QString butVal = button->text();
      // Get the value in the display
      QString displayVal = ui->label_edit->text();
      QString newVal = displayVal + butVal;
      // Double version of number
      double dblNewVal = newVal.toDouble();
      // Set value in display and allow up to 16 digits before using exponents
      ui->label_edit->setText(QString::number(dblNewVal, 'g', 16));
}

void Calculadora::OperatorClicked()
{
    // Cancel out previous math button clicks
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    // Store current value in Display
    QString displayVal = ui->label_edit->text();
    CalcValue = displayVal.toDouble();

    // Sender returns a pointer to the button pressed
    QPushButton *button = static_cast<QPushButton *>(sender());

    // Get math symbol on the button
    QString butVal = button->text();
    //ui->label_edit->setText(butVal);

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "x", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    } else if(QString::compare(butVal, "1/x", Qt::CaseInsensitive) == 0){
        inverseTrigger = true;
    } else if(QString::compare(butVal, "Sqrt", Qt::CaseInsensitive) == 0){
        sqrtTrigger = true;
    }else {
        squaredTrigger = true;
    }

    // Clear display
    ui->label_edit->setText("");
}

void Calculadora::EqualClicked()
{
    // Holds new calculation
    double result = 0.0;
    // Get value in display
    QString displayVal = ui->label_edit->text();
    double dblDisplayVal = displayVal.toDouble();
    result = dblDisplayVal;

    // Make sure a math button was pressed
    if(addTrigger || subTrigger || multTrigger || divTrigger || inverseTrigger || squaredTrigger || sqrtTrigger){
        if(addTrigger){
            result = CalcValue + dblDisplayVal;
        } else if(subTrigger){
            result = CalcValue - dblDisplayVal;
        } else if(multTrigger){
            result = CalcValue * dblDisplayVal;
        } else if(divTrigger){
            result = CalcValue / dblDisplayVal;
        } else if(inverseTrigger){
            result = 1 / CalcValue;
        } else if(sqrtTrigger){
            result = sqrt(CalcValue);
        }else {
            result = CalcValue*CalcValue;
        }
    }
    // Put result in display
    ui->label_edit->setText(QString::number(result));
}

void Calculadora::ChangeSignClicked()
{

    // Get the value in the display
    QString displayVal = ui->label_edit->text();

    // Regular expression checks if it is a number
    // plus sign
    QRegExp reg("[-+]?[0-9.]*");

    // If it is a number change the sign
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        // Put solution in display
        ui->label_edit->setText(QString::number(dblDisplayValSign));
    }
}

void Calculadora:: PointClicked()
{
    ui->label_edit->setText(ui->label_edit->text() + tr("."));
}

void Calculadora::BackSpaceClicked()
{
    QString text = ui->label_edit->text();
    text.chop(1);
    ui->label_edit->setText(text);
}

void Calculadora::ClearClicked()
{
     ui->label_edit->setText("0");
}

void Calculadora::ClearAllClicked()
{
    CalcValue = 0.0;
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    inverseTrigger = false;
    squaredTrigger = false;
    sqrtTrigger = false;
    ui->label_edit->clear();
    ui->label_edit->setText("0");
}

void Calculadora::FirstRingClicked()
{
    //ui->_Color2->setStyleSheet(White);
    //ui->_Color3->setStyleSheet(White);
    //Sender returns a pointer to the button pressed
    QPushButton *button = static_cast<QPushButton *>(sender());
    // Get color on button pressed
    QString buttonColor = button->toolTip();
    firstring = buttonColor;
    ui->_DisplayColor->setText(buttonColor + colors);

    if(QString::compare(buttonColor, "Brown", Qt::CaseInsensitive) == 0){
        resistor1 = 1;
        ui->_Color1->setStyleSheet(Brown);
    }else if(QString::compare(buttonColor, "Red", Qt::CaseInsensitive) == 0){
        resistor1 = 2;
        ui->_Color1->setStyleSheet(Red);
    }else if(QString::compare(buttonColor, "Orange", Qt::CaseInsensitive) == 0){
        resistor1 = 3;
        ui->_Color1->setStyleSheet(Orange);
    }else if(QString::compare(buttonColor, "Yellow", Qt::CaseInsensitive) == 0){
        resistor1 = 4;
        ui->_Color1->setStyleSheet(Yellow);
    }else if(QString::compare(buttonColor, "Green", Qt::CaseInsensitive) == 0){
        resistor1 = 5;
        ui->_Color1->setStyleSheet(Green);
    }else if(QString::compare(buttonColor, "Blue", Qt::CaseInsensitive) == 0){
        resistor1 = 6;
        ui->_Color1->setStyleSheet(Blue);
    }else if(QString::compare(buttonColor, "Purple", Qt::CaseInsensitive) == 0){
        resistor1 = 7;
        ui->_Color1->setStyleSheet(Purple);
    }else if(QString::compare(buttonColor, "Gray", Qt::CaseInsensitive) == 0){
        resistor1 = 8;
        ui->_Color1->setStyleSheet(Gray);
    }else if(QString::compare(buttonColor, "White", Qt::CaseInsensitive) == 0){
        resistor1 = 9;
        ui->_Color1->setStyleSheet(White);
    }
}
void Calculadora::SecondRingClicked()
{
    //ui->_Color3->setStyleSheet(White);

    //Sender returns a pointer to the button pressed
    QPushButton *button = static_cast<QPushButton *>(sender());
    // Get color on button pressed
    QString buttonColor = button->toolTip();
    secondring = firstring + ",";
    secondring+= buttonColor;
    ui->_DisplayColor->setText(secondring);

    if(QString::compare(buttonColor, "Black", Qt::CaseInsensitive) == 0){
        resistor2 = 0;
        ui->_Color2->setStyleSheet(Black);
    }else if(QString::compare(buttonColor, "Brown", Qt::CaseInsensitive) == 0){
        resistor2 = 1;
        ui->_Color2->setStyleSheet(Brown);
    }else if(QString::compare(buttonColor, "Red", Qt::CaseInsensitive) == 0){
        resistor2 = 2;
        ui->_Color2->setStyleSheet(Red);
    }else if(QString::compare(buttonColor, "Orange", Qt::CaseInsensitive) == 0){
        resistor2 = 3;
        ui->_Color2->setStyleSheet(Orange);
    }else if(QString::compare(buttonColor, "Yellow", Qt::CaseInsensitive) == 0){
        resistor2 = 4;
        ui->_Color2->setStyleSheet(Yellow);
    }else if(QString::compare(buttonColor, "Green", Qt::CaseInsensitive) == 0){
        resistor2 = 5;
        ui->_Color2->setStyleSheet(Green);
    }else if(QString::compare(buttonColor, "Blue", Qt::CaseInsensitive) == 0){
        resistor2 = 6;
        ui->_Color2->setStyleSheet(Blue);
    }else if(QString::compare(buttonColor, "Purple", Qt::CaseInsensitive) == 0){
        resistor2 = 7;
        ui->_Color2->setStyleSheet(Purple);
    }else if(QString::compare(buttonColor, "Gray", Qt::CaseInsensitive) == 0){
        resistor2 = 8;
        ui->_Color2->setStyleSheet(Gray);
    }else if(QString::compare(buttonColor, "White", Qt::CaseInsensitive) == 0){
        resistor2 = 9;
        ui->_Color2->setStyleSheet(White);
    }
}
void Calculadora::MultiplierClicked()
{

    //Sender returns a pointer to the button pressed
    QPushButton *button = static_cast<QPushButton *>(sender());
    // Get color on button pressed
    QString buttonColor = button->toolTip();
    multiplier = secondring + ",";
    multiplier += buttonColor;
    ui->_DisplayColor->setText(multiplier);

    if(QString::compare(buttonColor, "Black", Qt::CaseInsensitive) == 0){
        resistor3 = 1.0;
        ui->_Color3->setStyleSheet(Black);
    }else if(QString::compare(buttonColor, "Brown", Qt::CaseInsensitive) == 0){
        resistor3 = 10.0;
    ui->_Color3->setStyleSheet(Brown);
    }else if(QString::compare(buttonColor, "Red", Qt::CaseInsensitive) == 0){
        resistor3 = 100.0;
        ui->_Color3->setStyleSheet(Red);
    }else if(QString::compare(buttonColor, "Orange", Qt::CaseInsensitive) == 0){
        resistor3 = 1000.0;
        ui->_Color3->setStyleSheet(Orange);
    }else if(QString::compare(buttonColor, "Yellow", Qt::CaseInsensitive) == 0){
        resistor3 = 10000.0;
        ui->_Color3->setStyleSheet(Yellow);
    }else if(QString::compare(buttonColor, "Green", Qt::CaseInsensitive) == 0){
        resistor3 = 100000.0;
        ui->_Color3->setStyleSheet(Green);
    }else if(QString::compare(buttonColor, "Blue", Qt::CaseInsensitive) == 0){
        resistor3 = 10000000.0;
        ui->_Color3->setStyleSheet(Blue);
    }else if(QString::compare(buttonColor, "Silver", Qt::CaseInsensitive) == 0){
        resistor3 = 0.01;
        ui->_Color3->setStyleSheet(Silver);
    }else if(QString::compare(buttonColor, "Gold", Qt::CaseInsensitive) == 0){
        resistor3 = 0.1;
        ui->_Color3->setStyleSheet(Gold);
    }
}
void Calculadora::ToleranceClicked()
{
    //Sender returns a pointer to the button pressed
    QPushButton *button = static_cast<QPushButton *>(sender());
    // Get color on button pressed
    QString buttonColor = button->toolTip();
    tolerance = multiplier + ",";
    tolerance += buttonColor;
    ui->_DisplayColor->setText(tolerance);

    if(QString::compare(buttonColor, "Gray", Qt::CaseInsensitive) == 0){
        tolerance = "0.05%";
        ui->_Color4->setStyleSheet(Gray);
    }else if(QString::compare(buttonColor, "Purple", Qt::CaseInsensitive) == 0){
        tolerance = "0.1%";
        ui->_Color4->setStyleSheet(Purple);
    }else if(QString::compare(buttonColor, "Blue", Qt::CaseInsensitive) == 0){
        tolerance = "0.25%";
        ui->_Color4->setStyleSheet(Blue);
    }else if(QString::compare(buttonColor, "Green", Qt::CaseInsensitive) == 0){
        tolerance = "0.5%";
        ui->_Color4->setStyleSheet(Green);
    }else if(QString::compare(buttonColor, "Brown", Qt::CaseInsensitive) == 0){
        tolerance = "1%";
        ui->_Color4->setStyleSheet(Brown);
    }else if(QString::compare(buttonColor, "Red", Qt::CaseInsensitive) == 0){
        tolerance = "2%";
        ui->_Color4->setStyleSheet(Red);
    }else if(QString::compare(buttonColor, "Gold", Qt::CaseInsensitive) == 0){
        tolerance = "5%";
        ui->_Color4->setStyleSheet(Gold);
    }else if(QString::compare(buttonColor, "Silver", Qt::CaseInsensitive) == 0){
        tolerance = "10%";
        ui->_Color4->setStyleSheet(Silver);
    }else if(QString::compare(buttonColor, "Black", Qt::CaseInsensitive) == 0){
        tolerance = "20%";
        ui->_Color4->setStyleSheet(Black);
    }
}
void Calculadora::EnterClicked()
{
    resistor = (resistor1*10 + resistor2)*resistor3;
    ui->_DisplayRes->setText(QString::number(resistor));
    ui->_DisplayTol->setText(tolerance);
    resistor = 0.0;

}
void Calculadora::EnterColorsClicked()
{
    colors = "";
    QString displayColor = ui->_DisplayRes->text();
    QString color;

    ui->_Color1->setStyleSheet(White);
    ui->_Color2->setStyleSheet(White);
    ui->_Color3->setStyleSheet(White);
    ui->_Color4->setStyleSheet(White);

    color = displayColor.data()[0];
    if(QString::compare(color, "1", Qt::CaseInsensitive) == 0){
        colors += "Brown, ";
        ui->_Color1->setStyleSheet(Brown);
    }else if(QString::compare(color, "2", Qt::CaseInsensitive) == 0){
        colors += "Red, ";
        ui->_Color1->setStyleSheet(Red);
    }else if(QString::compare(color, "3", Qt::CaseInsensitive) == 0){
        colors += "Orange ,";
        ui->_Color1->setStyleSheet(Orange);
    }else if(QString::compare(color, "4", Qt::CaseInsensitive) == 0){
        colors += "Yellow ,";
        ui->_Color1->setStyleSheet(Yellow);
    }else if(QString::compare(color, "5", Qt::CaseInsensitive) == 0){
        colors += "Green, ";
        ui->_Color1->setStyleSheet(Green);
    }else if(QString::compare(color, "6", Qt::CaseInsensitive) == 0){
        colors += "Blue, ";
        ui->_Color1->setStyleSheet(Blue);
    }else if(QString::compare(color, "7", Qt::CaseInsensitive) == 0){
        colors += "Purple, ";
        ui->_Color1->setStyleSheet(Purple);
    }else if(QString::compare(color, "8", Qt::CaseInsensitive) == 0){
        colors += "Gray, ";
        ui->_Color1->setStyleSheet(Gray);
    }else if(QString::compare(color, "9", Qt::CaseInsensitive) == 0){
        colors += "White, ";
        ui->_Color1->setStyleSheet(White);
    }
    color = displayColor.data()[1];
    if(QString::compare(color, "0", Qt::CaseInsensitive) == 0){
        colors += "Black, ";
        ui->_Color2->setStyleSheet(Black);
    }else if(QString::compare(color, "1", Qt::CaseInsensitive) == 0){
        colors += "Brown, ";
        ui->_Color2->setStyleSheet(Brown);
    }else if(QString::compare(color, "2", Qt::CaseInsensitive) == 0){
        colors += "Red, ";
        ui->_Color2->setStyleSheet(Red);
    }else if(QString::compare(color, "3", Qt::CaseInsensitive) == 0){
        colors += "Orange ,";
        ui->_Color2->setStyleSheet(Orange);
    }else if(QString::compare(color, "4", Qt::CaseInsensitive) == 0){
        colors += "Yellow ,";
        ui->_Color2->setStyleSheet(Yellow);
    }else if(QString::compare(color, "5", Qt::CaseInsensitive) == 0){
        colors += "Green, ";
        ui->_Color2->setStyleSheet(Green);
    }else if(QString::compare(color, "6", Qt::CaseInsensitive) == 0){
        colors += "Blue, ";
        ui->_Color2->setStyleSheet(Blue);
    }else if(QString::compare(color, "7", Qt::CaseInsensitive) == 0){
        colors += "Purple, ";
        ui->_Color2->setStyleSheet(Purple);
    }else if(QString::compare(color, "8", Qt::CaseInsensitive) == 0){
        colors += "Gray, ";
        ui->_Color2->setStyleSheet(Gray);
    }else if(QString::compare(color, "9", Qt::CaseInsensitive) == 0){
        colors += "White, ";
        ui->_Color2->setStyleSheet(White);
    }


    color = QString::number(displayColor.size()-2);
    if(QString::compare(color, "0", Qt::CaseInsensitive) == 0){
        colors += "Black";
        ui->_Color3->setStyleSheet(Black);
    }else if(QString::compare(color, "1", Qt::CaseInsensitive) == 0){
        colors += "Brown";
        ui->_Color3->setStyleSheet(Brown);
    }else if(QString::compare(color, "2", Qt::CaseInsensitive) == 0){
        colors += "Red";
        ui->_Color3->setStyleSheet("background-color:red;");
    }else if(QString::compare(color, "3", Qt::CaseInsensitive) == 0){
        colors += "Orange";
        ui->_Color3->setStyleSheet(Orange);
    }else if(QString::compare(color, "4", Qt::CaseInsensitive) == 0){
        colors += "Yellow";
        ui->_Color3->setStyleSheet(Yellow);
    }else if(QString::compare(color, "5", Qt::CaseInsensitive) == 0){
        colors += "Green";
        ui->_Color3->setStyleSheet(Green);
    }else if(QString::compare(color, "6", Qt::CaseInsensitive) == 0){
        colors += "Blue";
        ui->_Color3->setStyleSheet(Blue);
    }

    tolerance = ui->_DisplayTol->text();
    if(QString::compare(tolerance, "0.05%", Qt::CaseInsensitive) == 0){
        colors += ", Gray";
        ui->_Color4->setStyleSheet(Gray);
    }else if(QString::compare(tolerance, "0.1%", Qt::CaseInsensitive) == 0){
        colors += ", Purple";
        ui->_Color4->setStyleSheet(Purple);
    }else if(QString::compare(tolerance, "0.25%", Qt::CaseInsensitive) == 0){
        colors += ", Blue";
        ui->_Color4->setStyleSheet(Blue);
    }else if(QString::compare(tolerance, "0.5%", Qt::CaseInsensitive) == 0){
        colors += ", Green";
        ui->_Color4->setStyleSheet(Green);
    }else if(QString::compare(tolerance, "1%", Qt::CaseInsensitive) == 0){
        colors += ", Brown";
        ui->_Color4->setStyleSheet(Brown);
    }else if(QString::compare(tolerance, "2%", Qt::CaseInsensitive) == 0){
        colors += ", Red";
        ui->_Color4->setStyleSheet(Red);
    }else if(QString::compare(tolerance, "5%", Qt::CaseInsensitive) == 0){
        colors += ", Gold";
        ui->_Color4->setStyleSheet(Gold);
    }else if(QString::compare(tolerance, "10%", Qt::CaseInsensitive) == 0){
        colors += ", Silver";
        ui->_Color4->setStyleSheet(Silver);
    }else if(QString::compare(tolerance, "20%", Qt::CaseInsensitive) == 0){
        colors += ", Black";
        ui->_Color4->setStyleSheet("background-color:rgb(0,0,0);");
    }

    ui->_DisplayColor->setText(colors);

}

