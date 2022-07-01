#ifndef READEXCUTER_H
#define READEXCUTER_H

#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVariant>
#include <QDebug>

#include <iostream>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


class ReadExcuter : public QObject
{
    Q_OBJECT

public:
    static ReadExcuter * getInstance();
    ~ReadExcuter();
    int getExcelFile(QString filePath);
    QStringList getSheetNames();
    Worksheet getSheetByName(QString selectedSheetName);
    QVector< QVector<QString> > getSheetAllCells();
    int parseColNumber(QString colNum);
    QString getColString(int colNum);
private:
    explicit ReadExcuter(QObject *parent = nullptr);
    void initLetterDigiMap();



public:
    int maxRow;
    int maxCol;
    Document *xlsxDoc;
    QStringList sheetNames;
    QVector< QVector<QString> > cellValues;
    QMap<QChar, int> letterDigiMap;
private:


};

#endif // READEXCUTER_H
