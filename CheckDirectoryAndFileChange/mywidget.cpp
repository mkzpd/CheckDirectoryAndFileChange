#include "mywidget.h"
#include "ui_mywidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QTreeView>
#include <QFileSystemModel>
#include <filesystem>
#include <string>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QDateTime>
#include <QDirIterator>
#include <QStandardItem>
#include <QFileIconProvider>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStandardItem>
#include <QJsonObject>


MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

QStandardItem* findChilItem(QStandardItem* it, const QString & text){
    if(!it->hasChildren())
        return nullptr;
    for(int i=0; i< it->rowCount(); i++){
        if(it->child(i)->text() == text)
            return it->child(i);
    }
    return nullptr;
}

void appendToModel(QStandardItemModel *model, const QStringList & list, const QString & size){
    QStandardItem *parentItem = model->invisibleRootItem();
    QFileIconProvider provider;

    for(QStringList::const_iterator it = list.begin(); it != list.end(); ++it)
    {
        QStandardItem *item = findChilItem(parentItem, *it);
        if(item){
            parentItem = item;
            continue;
        }
        item = new QStandardItem(*it);
        if(std::next(it) == list.end()){
            item->setIcon(provider.icon(QFileIconProvider::File));
            parentItem->appendRow({item, new QStandardItem(size)});
        }
        else{
            item->setIcon(provider.icon(QFileIconProvider::Folder));
            parentItem->appendRow(item);
        }
        parentItem = item;
    }
}


void MyWidget::scanDir(QString WantOperaDirToQstring)
{

    QDirIterator it(WantOperaDirToQstring, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString dir = it.next();
        qDebug() << "\"name\":"<<dir;

        /*
        const std::string json = R"([
                             {"name": "/folder1/file1.txt";"size": "1KB"},
                             {"name": "/folder1/file2.txt";"size": "1KB"},
                             {"name": "/folder1/sub/file3.txt";"size": "1KB"},
                             {"name": "/folder2/file4.txt";"size": "1KB"},
                             {"name": "/folder2/file5.txt";"size": "1KB"}
                             ])";
         */

        // /etc/.
        // /etc/..
        // /etc/X11
        // /etc/X11/fs
        // ...

    }



}

//choose directory
void MyWidget::on_pushButton_clicked()
{
    QDir directory = QFileDialog::getExistingDirectory(this, tr("select directory"));

    qDebug() << "directory's Path is " << directory.absolutePath() + "/";

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Yes or NO", "You choose directory is: " + directory.absolutePath() + "/",
                                  QMessageBox::Save | QMessageBox::Cancel);

    if (reply == QMessageBox::Save) {
        WantOperaDir = directory.absolutePath() + "/";
        WantOperaDirToQstring = WantOperaDir.path() + "/";
        qDebug() << "Save was clicked, now you choice directory is: " << WantOperaDirToQstring;
    }
    if(reply == QMessageBox::Cancel)
    {
        ;
    }

    dirModel2 = new QFileSystemModel(); //Create new model
    dirModel2->setRootPath(WantOperaDirToQstring); //Set model path

    ui->treeView_2->setModel(dirModel2); //Add model to QTreeView

    QModelIndex idx2 = dirModel2->index(WantOperaDirToQstring); //Set the root item
    ui->treeView_2->setRootIndex(idx2);

}

// Display status of backup files and now file or directory different
void MyWidget::on_pushButton_2_clicked()
{
    //QStandardItemModel model;
    model.setHorizontalHeaderLabels({"Name", "Size"});
    const std::string json = R"([
                             {"name": "/folder1/file1.txt";"size": "1KB"},
                             {"name": "/folder1/file2.txt";"size": "1KB"},
                             {"name": "/folder1/sub/file3.txt";"size": "1KB"},
                             {"name": "/folder2/file4.txt";"size": "1KB"},
                             {"name": "/folder2/file5.txt";"size": "1KB"}
                             ])";

    QJsonParseError parse;
    // The string is not a valid json, the separator must be a comma
    // and not a semicolon, which is why it is being replaced
    QByteArray data = QByteArray::fromStdString(json).replace(";", ",");
    QJsonDocument const& jdoc =  QJsonDocument::fromJson(data, &parse);
    Q_ASSERT(parse.error == QJsonParseError::NoError);
    if(jdoc.isArray()){
        for(const QJsonValue &element : jdoc.array() ){
            QJsonObject obj = element.toObject();
            QString name = obj["name"].toString();
            QString size = obj["size"].toString();
            appendToModel(&model, name.split("/", Qt::SkipEmptyParts), size);
        }
    }

    //QTreeView viewLeft;
    //ui->treeView->setModel(model);
    viewLeft = new QTreeView(this);
    //viewLeft->setModel(model);

    viewLeft->move(30,60);
    viewLeft->show();

    //QModelIndex idxLeft = dirModel2->index(WantOperaDirToQstring); //Set the root item
    //ui->treeView_2->setRootIndex(idxLeft);

    /*
    dirModel2 = new QFileSystemModel(); //Create new model
    dirModel2->setRootPath(WantOperaDirToQstring); //Set model path

    ui->treeView_2->setModel(dirModel2); //Add model to QTreeView

    QModelIndex idx2 = dirModel2->index(WantOperaDirToQstring); //Set the root item
    ui->treeView_2->setRootIndex(idx2);
    */

}

//status of backup files
void MyWidget::on_pushButton_3_clicked()
{
    /*
    CurrTime = CurrTime.currentDateTime();
    qDebug() << "CurrTime is " << CurrTime;
    ui->lcdNumber->display(CurrTime);
    */

    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyy.MM.dd hh:mm:ss");
    //QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    qDebug() << "Date is:"+formattedTime;

    LastRecordTimeToString = formattedTime;




    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Yes or NO", "Now ready to status of backup files directory is: " + WantOperaDirToQstring,
                                  QMessageBox::Save | QMessageBox::Cancel);

    if (reply == QMessageBox::Save) {

        //需要实现文件状态的备份
        qDebug() << "Now ready to status of backup files that directory is: " << WantOperaDirToQstring;
        qDebug() << "*************** This function need to be do! ***************";
        qDebug() << "MyList is " << MyList;

        MyWidget::scanDir(WantOperaDirToQstring);

//        QDir dir(WantOperaDir);
//        if (!dir.exists())
//        {
//            dir.mkpath(WantOperaDirToQstring);
//        }

        /*
        QDir myPath(WantOperaDir);
        //myPath.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
        myPath.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
        QStringList FilesOrDicName = myPath.entryList(QDir::AllEntries);

//        for (int i = 1; i < FilesOrDicName.size(); i++)
//        {

//            qDebug() << "Filename " << i << " = " << myPath.filePath(FilesOrDicName.at(i));
//        }

        foreach(QString fn, FilesOrDicName){
            if (fn != ".." && fn != "."){
                qDebug() << "Filename " << WantOperaDirToQstring  + fn;
            }
        }
        */

    }
    if(reply == QMessageBox::Cancel)
    {
        ;
    }

}

//Display last time status of backup files date
void MyWidget::on_pushButton_4_clicked()
{

    ui->lcdNumber->setDigitCount(25);
    ui->lcdNumber->display(LastRecordTimeToString);

}

