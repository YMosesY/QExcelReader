#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "ReadWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void initMainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout* gridLayout;
    QWidget* centralWidget;
    QTabWidget tabWidget;
    ReadWidget tabRead;

};
#endif // MAINWINDOW_H
