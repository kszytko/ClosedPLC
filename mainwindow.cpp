#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "testmacro1.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<Adress*> range;
    range.push_back(new Adress("%I0.0"));
    range.push_back(new Adress("%I0.1"));
    range.push_back(new Adress("%I0.2"));
    range.push_back(new Adress("%I0.3"));


    QList<Variable*> vars;
    vars.push_back(new Variable("Var1", range[0], VAR_TYPE::BOOL));
    vars.push_back(new Variable("Var2", range[1], VAR_TYPE::BOOL));
    vars.push_back(new Variable("Var3", range[2], VAR_TYPE::BOOL));
    vars.push_back(new Variable("Var4", range[3], VAR_TYPE::BOOL));

    su = new SimulationUnit();
}

MainWindow::~MainWindow()
{
    delete ui;
}







void MainWindow::on_loadLibraryButton_clicked()
{
    su->loadLibrary(ui->libPathEdit->text());
}


void MainWindow::on_startSimUnitButton_clicked()
{
    su->runSimProject(ui->simPathEdit->text(), false);
}


void MainWindow::on_pushButton_clicked()
{
    su->writeIO(ui->symbol1->text(), ui->value1->text());
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->value2->setText(su->readIO(ui->symbol2->text()));
}

