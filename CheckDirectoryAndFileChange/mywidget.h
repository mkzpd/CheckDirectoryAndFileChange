#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QDir>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDateTime>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractItemModel>
#include <QMessageBox>
#include <QFileIconProvider>

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    void BackupDirAndFileState(QString WantOperaDirToQstring);
    void appendToModel(QStandardItemModel *model, const QStringList & list, const QString & size);
    QStandardItem* findChilItem(QStandardItem *it, const QString & text);
    void FindStringInBackFileLineByLine(char* NeedToFindString, char* ReturnValue, int mode);
    int strindexP(char s[], char t[]);
    ~MyWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MyWidget* ui;
    QDir WantOperaDir;
    QString WantOperaDirToQstring;
    QDir WantSkipBackupDir;
    QString WantSkipBackupDirToQstring;
    QString BackupFileStateDir;
    QString BackupFileStateDirToQstring;
    int CheckWantOperaDirChooseIf;
    int CheckSkipDirChooseIf;
    QMessageBox::StandardButton reply;
    QStringList MyList;
    QFileSystemModel *dirModel2;
    QFileSystemModel *dirModel;
    QTreeView treeView;
    QTreeView* treeView_2;
    QDateTime CurrTime;
    QDateTime LastRecordTime;
    QStandardItem *parentItem;
    QStandardItem *item;
    QFileIconProvider provider;
    QString LastRecordTimeToString;
    QStandardItemModel model;
    QString ReceiveReturnPath;
    QString ReceiveReturnTime;



};
#endif // MYWIDGET_H
