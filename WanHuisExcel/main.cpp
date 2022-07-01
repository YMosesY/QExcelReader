#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Excel读取格式化工具");
    w.show();

    return a.exec();
}
