#ifndef READWIDGET_H
#define READWIDGET_H

#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ReadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReadWidget(QWidget *parent = nullptr);
    ~ReadWidget();
private:
    void initReadWidget();
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);
    int assertPath(QString path);
    void initCombomBox();
    void initSheetLabel();
    void initRawTip();
    void initColTip();
    void initCellTip();
    void initBtnGroup();
    void initConfirmBtn();
    void initTextEdit();
    void setRawTipVisible(bool status);
    void setColTipVisible(bool status);
    void setCellTipVisible(bool status);
    void showTextEdit(QString str);

private slots:
    void slot_radioGroupClicked(int btnId);
    void slot_confirmBtnClicked();

public:
    QString filePath;
    QComboBox comboBox;
    QLabel sheetLable;
    QButtonGroup radioGroup;
    QRadioButton rawRadioBtn;
    QRadioButton colRadioBtn;
    QRadioButton cellRadioBtn;

    QLabel rawLable;
    QLabel colLable;
    QLabel cellLable1;
    QLabel cellLable2;
    QLabel cellLable3;
    QLabel cellLable4;
    QLabel cellLable5;

    QLineEdit rawTextLine;
    QLineEdit colTextLine;
    QLineEdit cellRawMinTextLine;
    QLineEdit cellRawMaxTextLine;
    QLineEdit cellColMinTextLine;
    QLineEdit cellColMaxTextLine;

    QPushButton confirmBtn;

    QTextEdit textEdit;

private:
    bool haveInitConfirmBtn;
    bool haveInitTextEdit;
    QString finalString;


};



#endif // READWIDGET_H
