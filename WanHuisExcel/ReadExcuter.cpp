#include "ReadExcuter.h"
static ReadExcuter * readerPtr = NULL;

ReadExcuter * ReadExcuter::getInstance()
{
    if(NULL == readerPtr){
        readerPtr = new ReadExcuter();
    }
    return readerPtr;
}

ReadExcuter::ReadExcuter(QObject *parent)
    : QObject(parent),
      maxRow(-1),
      maxCol(-1),
      xlsxDoc(NULL)
{
    initLetterDigiMap();
}

ReadExcuter::~ReadExcuter()
{
    if(NULL != xlsxDoc){
        delete xlsxDoc;
    }
}

int ReadExcuter::getExcelFile(QString filePath)
{
    int result = 0;

    xlsxDoc = new Document(filePath);
    if((*xlsxDoc).load()){
        result = 1;
    }

    return result;
}



Worksheet ReadExcuter::getSheetByName(QString selectedSheetName)
{
    AbstractSheet* currentSheet = xlsxDoc->sheet(selectedSheetName);
    int sheetIndex = 0;
    foreach(QString str, sheetNames){
        if(!selectedSheetName.compare(str)){
            break;
        }
        sheetIndex++;
    }
    currentSheet->workbook()->setActiveSheet(sheetIndex);
    Worksheet* wsheet = (Worksheet*) currentSheet->workbook()->activeSheet();
    return *wsheet;
}

QStringList ReadExcuter::getSheetNames()
{
    sheetNames.clear();
    sheetNames = xlsxDoc->sheetNames();
    return sheetNames;
}

QVector< QVector<QString> > ReadExcuter::getSheetAllCells()
{   Worksheet selectedSheet = getSheetByName("testSheet");
    cellValues.clear();
    QVector<CellLocation> clList = selectedSheet.getFullCells( &maxRow, &maxCol );
    qDebug("maxRow is %d  maxCol is %d \n", maxRow, maxCol);
    QVector< QVector<QString> > tempCellValues;
    for (int rc = 0; rc < maxRow; rc++)
    {
        QVector<QString> tempValue;
        for (int cc = 0; cc < maxCol; cc++)
        {
            tempValue.push_back(QString(""));
        }
        tempCellValues.push_back(tempValue);
    }

    for ( int ic = 0; ic < clList.size(); ++ic )
    {
        CellLocation cl = clList.at(ic); // cell location

        int row = cl.row - 1;
        int col = cl.col - 1;

        QSharedPointer<Cell> ptrCell = cl.cell; // cell pointer

        // value of cell
        QVariant var = cl.cell.data()->value();
        QString str = var.toString();

        tempCellValues[row][col] = str;
    }
    cellValues = tempCellValues;
    return cellValues;
}

void ReadExcuter::initLetterDigiMap()
{
    letterDigiMap.insert('A',1);
    letterDigiMap.insert('B',2);
    letterDigiMap.insert('C',3);
    letterDigiMap.insert('D',4);
    letterDigiMap.insert('E',5);
    letterDigiMap.insert('F',6);
    letterDigiMap.insert('G',7);
    letterDigiMap.insert('H',8);
    letterDigiMap.insert('I',9);
    letterDigiMap.insert('J',10);
    letterDigiMap.insert('K',11);
    letterDigiMap.insert('L',12);
    letterDigiMap.insert('M',13);
    letterDigiMap.insert('N',14);
    letterDigiMap.insert('O',15);
    letterDigiMap.insert('P',16);
    letterDigiMap.insert('Q',17);
    letterDigiMap.insert('R',18);
    letterDigiMap.insert('S',19);
    letterDigiMap.insert('T',20);
    letterDigiMap.insert('U',21);
    letterDigiMap.insert('V',22);
    letterDigiMap.insert('W',23);
    letterDigiMap.insert('X',24);
    letterDigiMap.insert('Y',25);
    letterDigiMap.insert('Z',26);

}

int ReadExcuter::parseColNumber(QString colNum)
{
    int ret = 0;

    for(int i = colNum.length() - 1; i >= 0; i--){
        QChar letter = colNum[i];
        int charValue = 0;
        qDebug("parseColNumber :: i == %d  letter == %c", i, letter);
        charValue = letterDigiMap.value(letter);
        if(i == (colNum.length() - 1)){

        }else{
            for(int j = 0; j < colNum.length() - 1 - i; j++){
                charValue *= 26;
            }
        }
        ret += charValue;
    }
    ret = ret - 1;
    qDebug("parseColNumber :: ret == %d", ret);
    return ret;
}

QString ReadExcuter::getColString(int colNum)
{
    QString result;
    for(int i = 0;i < maxRow; i++){
        if(cellValues[i][colNum].compare("") != 0){
            result += cellValues[i][colNum];
            result += ";";
        }
    }
    return result;
}
