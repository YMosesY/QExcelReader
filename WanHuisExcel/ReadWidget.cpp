#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ReadWidget.h"
#include "ReadExcuter.h"

enum RADIO_BTN_ID{
    RAW_RADIO_BTN,
    COL_RADIO_BTN,
    CELL_RADIO_BTN
};

ReadWidget::ReadWidget(QWidget *parent)
    : QWidget(parent),
      filePath(""),
      haveInitConfirmBtn(false),
      haveInitTextEdit(false)
{
    initReadWidget();
    this->setAcceptDrops(true);
}

ReadWidget::~ReadWidget()
{

}

void ReadWidget::initReadWidget()
{
    initCombomBox();
    initSheetLabel();
    initBtnGroup();
    initRawTip();
    initColTip();
    initCellTip();
}

void ReadWidget::dragEnterEvent(QDragEnterEvent* e)
{
    //对拖放事件进行筛选
    if (true)
    {
        e->acceptProposedAction();	//放行，否则不会执行dropEvent()函数
    }
}
void ReadWidget::dropEvent(QDropEvent* e)
{
    //获取文件路径 (QString)
    QList<QUrl> urls = e->mimeData()->urls();
    if (urls.isEmpty()) return;
    filePath = urls.first().toLocalFile();
    qDebug("FilePath is %s \n", filePath.toStdString().c_str());
    if(assertPath(filePath)){
        int ret = ReadExcuter::getInstance()->ReadExcuter::getExcelFile(filePath);
        qDebug("ret is %d \n", ret);
        if(ret){
            //read file successed
            ReadExcuter::getInstance()->ReadExcuter::getSheetNames();
            ReadExcuter::getInstance()->ReadExcuter::getSheetAllCells();
            initCombomBox();
//            rawRadioBtn.setEnabled(true);
            colRadioBtn.setEnabled(true);
//            cellRadioBtn.setEnabled(true);
        }else{
            //error
        }
    }
    //转为char*
//    QByteArray qByteArrary = qStr.toLatin1();
//    char* filePath = qByteArrary.data();
}

int ReadWidget::assertPath(QString path)
{
    int result = 0;
    if((!path.isNull()) && (!path.isEmpty())){
        int pos = path.lastIndexOf(".");
        QString extension = path.mid(pos+1);
        qDebug("extension is %s \n", extension.toStdString().c_str());
        if(!extension.compare("xls", Qt::CaseInsensitive)||
                !extension.compare("xlsx", Qt::CaseInsensitive)||
                !extension.compare("xlsm", Qt::CaseInsensitive)){
            result = 1;
        }else{
            // not excel file
        }
    }
    return result;
}

void ReadWidget::initCombomBox()
{
    comboBox.setParent(this);
    comboBox.move(100,30);
    comboBox.setFixedWidth(200);
    comboBox.setEditable(false);
    comboBox.addItems(ReadExcuter::getInstance()->sheetNames);
    comboBox.show();
}

void ReadWidget::initSheetLabel()
{
    sheetLable.setParent(this);
    sheetLable.move(20,32);
    sheetLable.setText("请选择sheet:");
    sheetLable.show();

}

void ReadWidget::initBtnGroup()
{
    rawRadioBtn.setParent(this);
    rawRadioBtn.setText("读取整行");
    rawRadioBtn.move(20,70);
    rawRadioBtn.show();
    rawRadioBtn.setEnabled(false);

    colRadioBtn.setParent(this);
    colRadioBtn.setText("读取整列");
    colRadioBtn.move(100,70);
    colRadioBtn.show();
    colRadioBtn.setEnabled(false);

    cellRadioBtn.setParent(this);
    cellRadioBtn.setText("读取范围单元格");
    cellRadioBtn.move(180,70);
    cellRadioBtn.show();
    cellRadioBtn.setEnabled(false);

    radioGroup.addButton(&rawRadioBtn, RAW_RADIO_BTN);
    radioGroup.addButton(&colRadioBtn, COL_RADIO_BTN);
    radioGroup.addButton(&cellRadioBtn, CELL_RADIO_BTN);
    radioGroup.setExclusive(true);

    connect(&radioGroup, SIGNAL(idClicked(int)), this, SLOT(slot_radioGroupClicked(int)));
}

void ReadWidget::slot_radioGroupClicked(int btnId)
{
    do{
        if(NULL == ReadExcuter::getInstance()->xlsxDoc){
            qDebug("slot_radioGroupClicked :: click radio button without drag file btnId == %d", btnId);
            break;
        }
        switch(btnId){
        case RAW_RADIO_BTN:
            if(rawRadioBtn.isChecked()){
                setRawTipVisible(true);
                setColTipVisible(false);
                setCellTipVisible(false);
            }else{
                setRawTipVisible(false);
            }
            break;
        case COL_RADIO_BTN:
            if(colRadioBtn.isChecked()){
                setColTipVisible(true);
                setRawTipVisible(false);
                setCellTipVisible(false);
            }else{
                setColTipVisible(false);
            }
            break;
        case CELL_RADIO_BTN:
            if(cellRadioBtn.isChecked()){
                setCellTipVisible(true);
                setRawTipVisible(false);
                setColTipVisible(false);
            }else{
                setCellTipVisible(false);
            }
            break;
        default:
            qDebug("btnGroup status changed id == %d", btnId);
            break;
        }
        if(!haveInitConfirmBtn){
            initConfirmBtn();
        }
        if(!haveInitTextEdit){
            initTextEdit();
        }
    }while(0);
}

void ReadWidget::initRawTip()
{
    rawLable.setParent(this);
    rawLable.move(20,110);
    rawLable.setText("请输入行号:");
    rawLable.setVisible(false);

    rawTextLine.setParent(this);
    rawTextLine.move(100,110);
    rawTextLine.setFixedSize(50,20);
    QRegularExpression regularExpression("^[1-9][0-9]*$");
    QRegularExpressionValidator digiValidator(regularExpression);
    rawTextLine.setValidator(&digiValidator);
    rawTextLine.setVisible(false);

}

void ReadWidget::initColTip()
{
    colLable.setParent(this);
    colLable.move(20,110);
    colLable.setText("请输入列号:");
    colLable.setVisible(false);

    colTextLine.setParent(this);
    colTextLine.move(100,110);
    colTextLine.setFixedSize(50,20);
    QRegularExpression regularExpression("^[a-zA-Z]+$");
    QRegularExpressionValidator letterValidator(regularExpression);
    colTextLine.setValidator(&letterValidator);
    colTextLine.setVisible(false);
}

void ReadWidget::initCellTip()
{
    cellLable1.setParent(this);
    cellLable1.move(20,110);
    cellLable1.setText("请输入单元格范围:");
    cellLable1.setVisible(false);

    cellLable2.setParent(this);
    cellLable2.move(20,150);
    cellLable2.setText("行范围:");
    cellLable2.setVisible(false);

    cellRawMinTextLine.setParent(this);
    cellRawMinTextLine.move(80,150);
    cellRawMinTextLine.setFixedSize(50,20);
    QRegularExpression regularExpression("^[1-9][0-9]*$");
    QRegularExpressionValidator digiValidator(regularExpression);
    cellRawMinTextLine.setValidator(&digiValidator);
    cellRawMinTextLine.setVisible(false);

    cellLable3.setParent(this);
    cellLable3.move(150,150);
    cellLable3.setText("~");
    cellLable3.setVisible(false);

    cellRawMaxTextLine.setParent(this);
    cellRawMaxTextLine.move(180,150);
    cellRawMaxTextLine.setFixedSize(50,20);
    cellRawMaxTextLine.setValidator(&digiValidator);
    cellRawMaxTextLine.setVisible(false);

    cellLable4.setParent(this);
    cellLable4.move(20,190);
    cellLable4.setText("列范围:");
    cellLable4.setVisible(false);

    cellColMinTextLine.setParent(this);
    cellColMinTextLine.move(80,190);
    cellColMinTextLine.setFixedSize(50,20);
    QRegularExpression regularExpression1("^[a-zA-Z]+$");
    QRegularExpressionValidator letterValidator(regularExpression1);
    cellColMinTextLine.setValidator(&letterValidator);
    cellColMinTextLine.setVisible(false);

    cellLable5.setParent(this);
    cellLable5.move(150,190);
    cellLable5.setText("~");
    cellLable5.setVisible(false);

    cellColMaxTextLine.setParent(this);
    cellColMaxTextLine.move(180,190);
    cellColMaxTextLine.setFixedSize(50,20);
    cellColMaxTextLine.setValidator(&letterValidator);
    cellColMaxTextLine.setVisible(false);
}

void ReadWidget::initConfirmBtn()
{
    haveInitConfirmBtn = true;
    confirmBtn.setParent(this);
    confirmBtn.setText("确认");
    confirmBtn.move(20,230);
    confirmBtn.setFixedSize(40,20);
    confirmBtn.show();

    connect(&confirmBtn, SIGNAL(clicked()), this, SLOT(slot_confirmBtnClicked()));
}

void ReadWidget::slot_confirmBtnClicked()
{
    int checkedId = radioGroup.checkedId();
    qDebug("slot_confirmBtnClicked ::  checkedId == %d", checkedId);
    switch(checkedId){
    case RAW_RADIO_BTN:
    {
        QString rawNum = rawTextLine.text();
        qDebug("slot_confirmBtnClicked ::  rawNum == %s", rawNum.toStdString().c_str());
    }
        break;
    case COL_RADIO_BTN:
    {
        QString colNum = colTextLine.text();
        int col = ReadExcuter::getInstance()->parseColNumber(colNum.toUpper());
        QString finalResult = ReadExcuter::getInstance()->getColString(col);
        textEdit.setText(finalResult);

    }
        break;
    case CELL_RADIO_BTN:
    {

    }
        break;
    default:
        break;
    }
}

void ReadWidget::initTextEdit(){
    textEdit.setParent(this);
    textEdit.move(20,270);
    textEdit.setFixedSize(700,220);
    textEdit.show();
    haveInitTextEdit = true;
}

void ReadWidget::setRawTipVisible(bool status)
{
    rawLable.setVisible(status);
    rawTextLine.setVisible(status);
}

void ReadWidget::setColTipVisible(bool status)
{
    colLable.setVisible(status);
    colTextLine.setVisible(status);
}

void ReadWidget::setCellTipVisible(bool status)
{
    cellLable1.setVisible(status);
    cellLable2.setVisible(status);
    cellRawMinTextLine.setVisible(status);
    cellLable3.setVisible(status);
    cellRawMaxTextLine.setVisible(status);
    cellLable4.setVisible(status);
    cellColMinTextLine.setVisible(status);
    cellLable5.setVisible(status);
    cellColMaxTextLine.setVisible(status);
}


