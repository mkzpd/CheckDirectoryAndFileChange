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

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    void scanDir(QString WantOperaDirToQstring);
    void appendToModel(QStandardItemModel *model, const QStringList & list, const QString & size);
    QStandardItem* findChilItem(QStandardItem *it, const QString & text);
    ~MyWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MyWidget* ui;
    QDir WantOperaDir;
    QString WantOperaDirToQstring;
    QStringList MyList;
    //QAbstractItemModel model;
    QStandardItemModel model;
    QFileSystemModel *dirModel2;
    QFileSystemModel *dirModel;
    QTreeView* treeView;
    QTreeView* treeView_2;
    QDateTime CurrTime;
    QDateTime LastRecordTime;
    QTreeView* viewLeft;
    QString LastRecordTimeToString;


};
#endif // MYWIDGET_H
