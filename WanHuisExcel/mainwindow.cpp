#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMainWindow();
}

MainWindow::~MainWindow()
{
    if(NULL != ui){
        delete ui;
    }

    if(NULL != gridLayout){
        delete gridLayout;
    }

    if(NULL != centralWidget){
        delete centralWidget;
    }
}

void MainWindow::initMainWindow()
{
    tabWidget.clear();
    tabWidget.setParent(this);
    tabWidget.setTabShape(QTabWidget::Triangular);

    tabRead.setParent(this);
    tabWidget.addTab(&tabRead, "读取内容");

    centralWidget = new QWidget(this);
    gridLayout = new QGridLayout(centralWidget);

    gridLayout->addWidget(&tabWidget,0,0,1,1);

    this->QMainWindow::setCentralWidget(centralWidget);

    this->QMainWindow::setLayout(gridLayout);

    tabWidget.show();

    tabRead.show();

}
