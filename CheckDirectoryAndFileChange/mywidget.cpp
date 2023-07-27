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
#include <QMimeDatabase>
#include <QMimeType>


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

QStandardItem* MyWidget::findChilItem(QStandardItem* it, const QString & text){
    if(!it->hasChildren())
        return nullptr;
    for(int i=0; i< it->rowCount(); i++){
        if(it->child(i)->text() == text)
            return it->child(i);
    }
    return nullptr;
}

int MyWidget::strindexP(char s[], char t[]){
    int i, j, k;
    for(i = 0; s[i] != '\0'; i++){
        for(j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++,k++)
            ;
        if(k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

void MyWidget::appendToModel(QStandardItemModel *model, const QStringList & list, const QString & LastModifiedTime){

    //MyWidget::FindStringInBackFile(char* NeedToFindString, char* ReturnValue);

    parentItem = model->invisibleRootItem();

    //qDebug() << "Begin parentItem is:" << parentItem;

    //char NeedToFindTime[] = "Last time backup file state time:";
    //char NeedToFindBackFilePath[] = "backup file path:";
    char ReceiveNeedToFindNameByteArrayToCharPointer[1000] = {0};
    //char ReceiveQMimeTypeForCheckeByteArrayToCharPointer[1000] = {0};

    //MyWidget::FindStringInBackFileLineByLine(NeedToFindNameByteArrayToCharPointer, QMimeTypeForCheckeByteArrayToCharPointer, 1);


    //for(QStringList::const_iterator it = list.begin(); it != list.end(); ++it)
    for(QStringList::const_iterator it = list.begin(); it != list.end(); ++it)
    {
        //qDebug() << "-------In QStringList::const_iterator function it is:" << *it;
        item = findChilItem(parentItem, *it);
        if(item){
            //qDebug() << "findChilItemitem  return item is:" << item;
            parentItem = item;
            continue;
        }
        item = new QStandardItem(*it);
        //qDebug() << "QStandardItem item is:" << item;
        item->setEditable(false);

        //MyWidget::FindStringInBackFileLineByLine(NeedToFindNameByteArrayToCharPointer, QMimeTypeForCheckeByteArrayToCharPointer, 1);
        qDebug() << "********************************************************************print list is:" << list;
        QList BeforeGoCheckDirOrFile = list;
        QString JudgeDirOrFile;
        for ( const auto& CheckValue : BeforeGoCheckDirOrFile )
        {
            qDebug() << "CheckValue is:" << CheckValue;

            JudgeDirOrFile.append(CheckValue);
            JudgeDirOrFile.append('/');

        }
        qDebug() << "JudgeDirOrFile is:" << JudgeDirOrFile;

        QByteArray JudgeDirOrFileByteArray = JudgeDirOrFile.toLocal8Bit();

        char JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks[1000] = {0};
        char* JudgeDirOrFileByteArrayToCharPointer = JudgeDirOrFileByteArray.data();
        int m = 0;
        for(; m < strlen(JudgeDirOrFileByteArrayToCharPointer); m++){
            JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks[m] = JudgeDirOrFileByteArrayToCharPointer[m];
        }
        JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks[m] = {'\"'};

        int NowCheckIsDir = 0;
        char QMimeTypePPP[] = "QMimeType";
        char directoryPPP[] = "directory";
        MyWidget::FindStringInBackFileLineByLine(JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks, ReceiveNeedToFindNameByteArrayToCharPointer, 1);
        qDebug() << "JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks is:" << JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks;
        qDebug() << "ReceiveNeedToFindNameByteArrayToCharPointer is " << ReceiveNeedToFindNameByteArrayToCharPointer;

        if((MyWidget::strindexP(ReceiveNeedToFindNameByteArrayToCharPointer, QMimeTypePPP) >= 0)){
            if((MyWidget::strindexP(ReceiveNeedToFindNameByteArrayToCharPointer, directoryPPP) >= 0)){
                NowCheckIsDir = 1;
            }
        }

        if(1 == NowCheckIsDir){
            qDebug() << "ReceiveNeedToFindNameByteArrayToCharPointer is " << ReceiveNeedToFindNameByteArrayToCharPointer << " that is directory." ;
        }else{
            qDebug() << "ReceiveNeedToFindNameByteArrayToCharPointer is " << ReceiveNeedToFindNameByteArrayToCharPointer << " that is not directory." ;
        }


        if(std::next(it) == list.end() && NowCheckIsDir != 1){
            qDebug() << "---File----In std::next(it) == list.end() list is:" << list;
            item->setIcon(provider.icon(QFileIconProvider::File));
            parentItem->appendRow({item, new QStandardItem(LastModifiedTime)});
        }
        else if(NowCheckIsDir == 1){
            qDebug() << "****Folder****In std::next(it) != list.end() list is:" << list;
            item->setIcon(provider.icon(QFileIconProvider::Folder));
            parentItem->appendRow(item);
        }
        parentItem = item;
    }


}


void MyWidget::BackupDirAndFileState(QString WantOperaDirToQstring)
{
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyy.MM.dd hh:mm:ss");
    //QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    qDebug() << "Date is:"+formattedTime;

    LastRecordTimeToString = formattedTime;

    QDir BackupFileStateDir = BackupFileStateDir.currentPath();
    QString  BackupFileStateDirToQstring= BackupFileStateDir.path() + "/";
    qDebug() << "APPCurrentPath is:" << BackupFileStateDir;
    qDebug() << "APPCurrentPathToString is:" << BackupFileStateDirToQstring;

    QFile file(BackupFileStateDirToQstring + "rememberFileState.txt");
    QFileInfo check_file(file);

    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        file.remove();
    } else {
        ;
    }

    //QFile file(APPCurrentPathToString + "rememberFileState.txt");
    file.open(QIODevice::ReadWrite); // Or QIODevice::ReadWrite or QIODevice::WriteOnly


    QTextStream out(&file);
    out << "This file is generated by Qt, please don't modify\n";
    out << "backup file path:" << WantOperaDirToQstring + "\n";
    out << "Last time backup file state time:" << formattedTime << "\n";
    out << "R\"([" << "\n";

    // optional, as QFile destructor will already do it:


    /*
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyy.MM.dd hh:mm:ss");
    //QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    qDebug() << "Date is:"+formattedTime;

    LastRecordTimeToString = formattedTime;
    */

    QDirIterator it(WantOperaDirToQstring, QDirIterator::Subdirectories);
    //WantSkipBackupDirToQstring = "C:/my-win10-document/software---install";
    quint64 LineNum = 0;
    while (it.hasNext()) {

        QString dir = it.next();

        if(1 == CheckSkipDirChooseIf)
        {
            if(!dir.contains(WantSkipBackupDirToQstring, Qt::CaseSensitive)
                && !dir.endsWith("/.", Qt::CaseSensitive) && !dir.endsWith("/..", Qt::CaseSensitive)){

                QFile file(dir);
                QFileInfo check_file(file);

                QMimeDatabase db;
                QMimeType mime = db.mimeTypeForFile(check_file, QMimeDatabase::MatchDefault);

                qDebug() << "In (1 == CheckSkipDirChooseIf) check_file is:"<< check_file << " mime is: " << mime;

                //QFileInfo info(file);
                QDateTime lastModifiedTime = check_file.lastModified();
                //lastModified = QDateTime::fromString("2010-10-25 10:28:58", "yyyy-MM-dd HH:mm:ss");
                //lastModified.setTimeSpec(Qt::UTC);
                //QDateTime lastModifiedLocalTime = lastModified.toLocalTime();

                //QString LastModifiedTimeToString = lastModifiedTime.toString("yyyy.MM.dd hh:mm:ss");
                qint64 lastModifiedTimeToqint64 = lastModifiedTime.toSecsSinceEpoch();
                //            bool ok;
                //            uint LastModifiedTimeToStringToHex = LastModifiedTimeToString.toUInt(&ok, 16);


                //            QDate date = QDate(1935,3,30);
                //            QString date_string = date.toString("yyyyMMdd");
                //            QByteArray data=QByteArray(date_string.toLocal8Bit());
                //            QByteArray bcd=QByteArray::fromHex(data);

                //            qDebug()<<"date_string is:" << date_string<<bcd.toHex();
                //QString lastModifiedTimeToqint64ForCheck = QString::number(lastModifiedTimeToqint64, 10);
                QString lastModifiedTimeToqint64ForCheck = QDateTime::fromSecsSinceEpoch(lastModifiedTimeToqint64).toLocalTime().toString("yyyy.MM.dd hh:mm:ss");
                //QString lastModifiedTimeToqint64ForCheckOk = QString::number(lastModifiedTimeToqint64, 10);

                QString CheckQint64Time = QString::number(lastModifiedTimeToqint64);

                LineNum = LineNum + 1;
                if(LineNum % 50 == 0){
                    out << ")\" R\"(" << "\n";
                }

                //out << "\"name\":"<<dir << ";" << "\"LastModifiedTime\":" << lastModified.toString() << "\n";
                out << "{" << "\"name\": "<< "\"" << dir << "/" << "\"" << ";" << "\"CheckQint64Time\": " <<  "\"" << CheckQint64Time
                    << "\"" << ";" << "\"QMimeType\": " << "\"" << mime.name() << "\""<< ";" <<  "\"LastModifiedTime\": " << "\"" << lastModifiedTimeToqint64ForCheck << "\"" << "}," << "\n";
                //qDebug() << "\"name\":"<<dir;

            }
        }else{
            if(!dir.endsWith("/.", Qt::CaseSensitive) && !dir.endsWith("/..", Qt::CaseSensitive)){


                QFile file(dir);
                QFileInfo check_file(file);

                QMimeDatabase db;
                QMimeType mime = db.mimeTypeForFile(check_file, QMimeDatabase::MatchDefault);

                qDebug() << "In (1 != CheckSkipDirChooseIf) check_file is:"<< check_file << " mime is: " << mime;

                //QFileInfo info(file);
                QDateTime lastModifiedTime = check_file.lastModified();
                //lastModified = QDateTime::fromString("2010-10-25 10:28:58", "yyyy-MM-dd HH:mm:ss");
                //lastModified.setTimeSpec(Qt::UTC);
                //QDateTime lastModifiedLocalTime = lastModified.toLocalTime();

                //QString LastModifiedTimeToString = lastModifiedTime.toString("yyyy.MM.dd hh:mm:ss");
                qint64 lastModifiedTimeToqint64 = lastModifiedTime.toSecsSinceEpoch();
                //            bool ok;
                //            uint LastModifiedTimeToStringToHex = LastModifiedTimeToString.toUInt(&ok, 16);


                //            QDate date = QDate(1935,3,30);
                //            QString date_string = date.toString("yyyyMMdd");
                //            QByteArray data=QByteArray(date_string.toLocal8Bit());
                //            QByteArray bcd=QByteArray::fromHex(data);

                //            qDebug()<<"date_string is:" << date_string<<bcd.toHex();
                //QString lastModifiedTimeToqint64ForCheck = QString::number(lastModifiedTimeToqint64, 10);
                QString lastModifiedTimeToqint64ForCheck = QDateTime::fromSecsSinceEpoch(lastModifiedTimeToqint64).toLocalTime().toString("yyyy.MM.dd hh:mm:ss");
                //QString lastModifiedTimeToqint64ForCheckOk = QString::number(lastModifiedTimeToqint64, 10);

                QString CheckQint64Time = QString::number(lastModifiedTimeToqint64);

                LineNum = LineNum + 1;
                if(LineNum % 50 == 0){
                    out << ")\" R\"(" << "\n";
                }

                //out << "\"name\":"<<dir << ";" << "\"LastModifiedTime\":" << lastModified.toString() << "\n";
                out << "{" << "\"name\": "<< "\"" << dir << "/" << "\"" << ";" << "\"CheckQint64Time\": " <<  "\"" << CheckQint64Time
                    << "\"" << ";" << "\"QMimeType\": " << "\"" << mime.name() << "\""<< ";" <<  "\"LastModifiedTime\": " << "\"" << lastModifiedTimeToqint64ForCheck << "\"" << "}," << "\n";
                //qDebug() << "\"name\":"<<dir;

            }
        }

    }

     //QTextStream out(&file);

    out << "])\";" << "\n";
    file.close();

    QFileInfo again_check_file(file);

    // check if file exists and if yes: Is it really a file and no directory?
    if (again_check_file.exists() && again_check_file.isFile()) {
        file.open(QIODevice::ReadWrite); // Or QIODevice::ReadWrite or QIODevice::WriteOnly
        QTextStream AgainOut(&file);
        qint64 fileSize = file.size();
        qDebug() << "fileSize is:" << fileSize << "bytes";
        file.seek(fileSize - 8);
        QString TestReadChar = file.read(1);
        AgainOut << "\n])\";" << "\n";
        qDebug() << "Read char or string is:" << TestReadChar;


    } else {
        ;
    }

    file.close();

    QMessageBox msgBox;
    msgBox.setText("backup file state have done!");
    msgBox.exec();


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

//choose directory
void MyWidget::on_pushButton_clicked()
{
    QDir directory = QFileDialog::getExistingDirectory(this, tr("select directory"));

    qDebug() << "directory's Path is " << directory.absolutePath();
    qDebug() << "directory is " << directory;

    if(!directory.path().contains("/")){
        return;
    }else{
        reply = QMessageBox::question(this, "IMPORTANT NOTICE 1", "You choose directory is: " + directory.absolutePath(),
                                      QMessageBox::Save | QMessageBox::Cancel);

        if (reply == QMessageBox::Save) {
            WantOperaDir = directory.absolutePath() + "/";
            WantOperaDirToQstring = WantOperaDir.path() + "/";
            CheckWantOperaDirChooseIf = 1;
            qDebug() << "Save was clicked, now you choice directory is: " << WantOperaDirToQstring;

            dirModel2 = new QFileSystemModel(); //Create new model
            dirModel2->setRootPath(WantOperaDirToQstring); //Set model path

            ui->treeView_2->setModel(dirModel2); //Add model to QTreeView

            QModelIndex idx2 = dirModel2->index(WantOperaDirToQstring); //Set the root item
            ui->treeView_2->setRootIndex(idx2);
        }
        if(reply == QMessageBox::Cancel)
        {
            CheckWantOperaDirChooseIf = 0;
        }

    }



}

// Display status of backup files and now file or directory different
void MyWidget::on_pushButton_2_clicked()
{


    model.setHorizontalHeaderLabels({"Name", "LastModifiedTime"});


//    const std::string json = R"([
//                             {"name": "/folder1/file1.txt";"size": "1KB 1"},
//                             {"name": "/folder1/subP";"size": "1KB 1"},
//                             {"name": "/folder1/subK/";"size": "1KB 1"},
//                             {"name": "/folder1/file2.txt";"size": "2023 July 25 19:53:09"},
//                             {"name": "/folder1/sub/file3.txt";"size": "1KB"},
//                             {"name": "/folder2/file4.txt";"size": "1KB"},
//                             {"name": "/folder2/file5.txt";"size": "1KB"}
//                             ])";




//    const std::string json = R"([
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qmake.stash";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/c.txt";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/www/1440D2C4BC469D57.idx";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/Release/a.txt";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/Release/b.txt";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/Debug";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/qax/";"LastModifiedTime": ""},
//{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/Debug/w.txt";"LastModifiedTime": ""}
//])";



    QFile file(BackupFileStateDirToQstring + "rememberFileState.txt");
    QTextStream stream(&file);
    QStringList list;
    int line = 0;
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray ar = file.readAll();
        QByteArray str;
        for(int i = 0; i < ar.size(); i++) {
            if(line != 0 && line != 1 && line != 2) {
                if(ar.at(i) == '\n') {
                    list << QString::fromUtf8(str.replace("\r", ""));
                    str.clear();
                }
                else{
                    str += ar.at(i);
                }
            }
            if(ar.at(i) == '\n')
                line++;
        }
    }

    // Now have error need modify, now I'm modify

    //const std::string json = list;


    //below temp comment

    //qDebug() << "*********------*********read list is" << list;
    //qDebug() << "*****iterate list:";
    for ( const auto& i : list )
    {
        //qDebug() << i;
    }




#if 0
    QList<QString> testlist;
    //QStringList<QString> testlist;
    testlist.append("January");
    testlist.append("February");
    testlist.append("December");
    qDebug() << "*****testlist is:" << testlist << Qt::endl;

    QList<QString>::iterator i;
    for (i = testlist.begin(); i != testlist.end(); ++i){
        qDebug() << "*****value of i is:" << *i << Qt::endl;
    }
#endif


//    const QStringList listPP { "A", "B", "C" };
//    qDebug() << "listPP is:";
//    for ( const auto& i : listPP )
//    {
//        qDebug() << i;
//    }


// need delete \ such that turn \" to "

//    const std::string json = R"([
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.exe\";\"CheckQint64Time\": \"1690431060\";\"LastModifiedTime\": \"2023.07.27 12:11:00\"},
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.ilk\";\"CheckQint64Time\": \"1690431060\";\"LastModifiedTime\": \"2023.07.27 12:11:00\"},
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.pdb\";\"CheckQint64Time\": \"1690431060\";\"LastModifiedTime\": \"2023.07.27 12:11:00\"},
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.vc.pdb\";\"CheckQint64Time\": \"1690431059\";\"LastModifiedTime\": \"2023.07.27 12:10:59\"},
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/main.obj\";\"CheckQint64Time\": \"1690420676\";\"LastModifiedTime\": \"2023.07.27 09:17:56\"},
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_mywidget.cpp\";\"CheckQint64Time\": \"1690420673\";\"LastModifiedTime\": \"2023.07.27 09:17:53\"},
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_mywidget.obj\";\"CheckQint64Time\": \"1690420676\";\"LastModifiedTime\": \"2023.07.27 09:17:56\"},
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_predefs.h\";\"CheckQint64Time\": \"1690176641\";\"LastModifiedTime\": \"2023.07.24 13:30:41\"},
//    {\"name\": \"C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/mywidget.obj\";\"CheckQint64Time\": \"1690431060\";\"LastModifiedTime\": \"2023.07.27 12:11:00\"}
//    ])\";



#if 1
    const std::string json = R"([
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qmake.stash/";"CheckQint64Time": "1690176641";"QMimeType": "text/plain";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/";"CheckQint64Time": "1690280515";"QMimeType": "inode/directory";"LastModifiedTime": "2023.07.25 18:21:55"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/";"CheckQint64Time": "1690176641";"QMimeType": "inode/directory";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/";"CheckQint64Time": "1690176641";"QMimeType": "inode/directory";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/";"CheckQint64Time": "1690452233";"QMimeType": "inode/directory";"LastModifiedTime": "2023.07.27 18:03:53"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/adxintrin.h.F8695614109264BF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/algorithm.85F84F593F617683.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/array.4A440D58C35C1B65.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/assert.h.1440D2C4BC469D57.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/atomic.46B98FDAFBC57939.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/bmiintrin.h.575071838DB7E543.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cctype.6CAC01960A46CBE8.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cerrno.D0366719F7F5D6B2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cfloat.D3E6A7BCFC6D7B8F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/chrono.0EF46438A07D6958.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/climits.D8FE350A98C8E969.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/clocale.6DAA72D95FD7152A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cmath.892CD3F82046EB21.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/concurrencysal.h.5DA0C09AED7DA192.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt.h.67FFEE19928F854D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_malloc.h.C0138CCDDEC903D5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_math.h.0390C374A34FAE6B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_memcpy_s.h.57108F1F96D1D502.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_memory.h.65CCD44C1265E45E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_search.h.B43E2344530D0FBD.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_share.h.DDB39811FDF689B6.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_stdio_config.h.58436A96317F9ED9.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_terminate.h.A7F76FB77BCBF78E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wconio.h.8BD81AD4B6009573.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wctype.h.4D29D397E6C1930F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wdirect.h.6812AA73E629936C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wio.h.E1801E05E6DE601B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wprocess.h.6BEFF415B32DF6AD.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wstdio.h.857D4DFFF9CE7A4E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wstdlib.h.70C64F6197B548E5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wstring.h.0DBF67EC18F91D22.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/corecrt_wtime.h.1CDF2D3F4B8BC90B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/crtdbg.h.B4D1688BBE438108.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/crtdefs.h.37482460E084AC88.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cstddef.18387D969F572B40.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cstdint.210D2F1E1255355E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cstdio.9E31F70803BFA76C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cstdlib.721BB85373461AF5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cstring.8985911536AFC237.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/ctime.1EFA885321907197.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/ctype.h.BC399C448EA6DADA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/cwchar.1B862937C4978721.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/eh.h.F7CF178131C9CC77.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/emmintrin.h.6E9074898208EE3A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
)" R"(
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/errno.h.FE9F83F635964CFD.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/exception.68221D83EEE0C979.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/filesystem.EEB58F510895B243.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/float.h.007015653F756B29.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/float.h.D55989CBB4E7EEA3.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/functional.F7983FBAA4462BCB.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/fxsrintrin.h.C52DDDDFB7A8B9DB.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/ia32intrin.h.3E30D2C597639933.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/immintrin.h.33FF6DAB2F686F5A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/initializer_list.EE3DCE14C35AE786.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/intrin.h.411A625DDB615A10.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/intrin0.h.19F5FEEAE1E7457C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/intrin0.inl.h.5D396B7ADE2D7A7B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/iomanip.1D639BBCDBA1F3D0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/ios.6E488EB20885070C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/iosfwd.AE9C5D6643157A02.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/isa_availability.h.8CE89F7382834217.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/istream.CB98F8285B9AC1A4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/iterator.4B52004CBF86A481.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/limits.3F90F82B2338C205.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/limits.h.593EB37839F86979.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/limits.h.AF08C55F08408B39.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/list.7AA79CD58A9A6AAC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/locale.647A011D4C4CF16D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/locale.h.1C8D49C5DA3FC138.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/main.cpp.A7AB6293CD377D1F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/malloc.h.D0EB2895A2726144.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/map.49ED74089A19706E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/math.h.2ED2F48A13D3ABEA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/memory.0E0E4619EB759AB4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/mmintrin.h.63C0A8200BC4D3A5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/mm_malloc.h.E4AB49790CC6DF03.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/mywidget.cpp.2889AAB0319329FA.idx/";"CheckQint64Time": "1690452233";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 18:03:53"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/mywidget.h.BED889163E189308.idx/";"CheckQint64Time": "1690431227";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 12:13:47"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/new.87325457E5B059EC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/numeric.42A3E831692436B7.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/optional.D2DD59C893468CE9.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/ostream.B4C957B4DBB0940D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/q20memory.h.99CD2B60065B1CDE.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/q20type_traits.h.19E72E0AB35A4B98.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qabstractbutton.h.913A6A585BEECC5D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qabstractfileiconprovider.h.FEDB5E17B10CF7B3.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qabstractitemdelegate.h.E9A8092DFCEA3C82.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QAbstractItemModel.742DBD48F020095D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qabstractitemmodel.h.A9E197D0533FC7EF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qabstractitemview.h.69ED3FC16C11A764.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qabstractscrollarea.h.DD106BF093A2092A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qabstractslider.h.18A0E4F0C7F02C3B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qabstractspinbox.h.A26C1D0ECD3FF99F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qaction.h.536DA3572F319258.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
)" R"(
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qalgorithms.h.548F82460ADE94AF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qanystringview.h.45F7FD9A96550E55.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QApplication.C30CFCF52BD60966.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qapplication.h.6648494309EC90A2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qarraydata.h.4BCEAF97283B3E89.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qarraydataops.h.4D40D9B995847FFA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qarraydatapointer.h.0F694992D960408B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qassert.h.F45698103D617E01.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qatomic.h.70EB060E536A9F1D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qatomic_cxx11.h.84A2B083DF566AC5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qbasicatomic.h.E67EB669C22E341A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qbindingstorage.h.711FC1D3D34D62CF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qbitmap.h.705090817B9DFFF4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qboxlayout.h.52AF6BB914DE650E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qbrush.h.809BFC8DE2A69262.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qbytearray.h.B7C1268CC59CC94D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qbytearrayalgorithms.h.C4F21F05AD4A720C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qbytearraylist.h.71FC4F21B87F9C28.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qbytearrayview.h.08819CC96C9FFC1E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcalendar.h.83ECE22A799D5D1F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcborcommon.h.2E694942A298798A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcborvalue.h.466F1AB135E4A9E2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qchar.h.76B68EC9DB30A3CE.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcolor.h.3123A77C49A4CA02.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcompare.h.D38D43DA59C09FC8.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcompare_impl.h.E0C9ED1140658087.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcompilerdetection.h.991EDC6AB39E2D17.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qconfig.h.827225FDA0499DD1.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qconstructormacros.h.4032C83BF433D327.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcontainerfwd.h.BB774F6EA8BA5716.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcontainerinfo.h.6868153325ECBDF4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcontainertools_impl.h.8334267A98702027.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcontiguouscache.h.B17B8705C7BA5F53.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcoreapplication.h.5F22580141C09FEF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcoreapplication_platform.h.D5487C58B996B2A9.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcoreevent.h.71B0BB6F44796E74.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qcursor.h.2A9BD4ADD51BC170.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qdarwinhelpers.h.808338C91E10DEA6.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qdatastream.h.60C194F05DDA133E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QDateTime.BE5699CE14B8998E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qdatetime.h.10A0433B5286D1DA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QDebug.AFB3A038D96BBC9F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qdebug.h.B342A9E1E726D108.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qdialog.h.CD5C6E9374A4DD15.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QDir.986CAA73B57D0D5E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qdir.h.D78A247822B35C0E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QDirIterator.C2707D516670ED63.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qdiriterator.h.A8ED31324BE8D7A5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qeventloop.h.420CAFC32E5771C2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qexceptionhandling.h.B19F1657E7A7BB2B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
)" R"(
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfile.h.1BDB16F225C1A190.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfiledevice.h.A1DFB7B2E6CD560C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QFileDialog.E96B6A44F7EEE1D5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfiledialog.h.E55B4BCA564A533C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QFileIconProvider.9BB458C4E261B268.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfileiconprovider.h.FBE6717A0A6D9EB4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QFileInfo.31D2B2B0D2C91CB0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfileinfo.h.57A368E2203E7220.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QFileSystemModel.FE62B92F9BF51355.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfilesystemmodel.h.8C1A76AB7001B82A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qflags.h.3FA3EF791036162E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfloat16.h.EB0AF361FE0AC93F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfont.h.4AFFA7C298271F1A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfontinfo.h.08F9BA9D85713A46.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfontmetrics.h.410523987A96ABFF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qforeach.h.6605906775CB7F77.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qframe.h.19C8604F58C5BB7A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qfunctionpointer.h.A0F701A5667138D7.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qgenericatomic.h.09008B98754A8ACC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qglobal.h.20BD3459F767FA49.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qglobalstatic.h.5A31962909690E90.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QGridLayout.E4F3A1295C441492.idx/";"CheckQint64Time": "1690431227";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 12:13:47"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qgridlayout.h.20BED56F485669FF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qguiapplication.h.3DD2C9A5DBA9F260.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qguiapplication_platform.h.D82BD6E46B59C357.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qhash.h.FB1F71EA5EDF8938.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qhashfunctions.h.DBB158BF6FBF457B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QHBoxLayout.B54878B25703D6EF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QHeaderView.5F173F2D6020F3BC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qheaderview.h.9D687AEA36A2B403.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qicon.h.8DA53B9D01FED295.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qimage.h.67597433C49CD802.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qinputmethod.h.77B22054D6EE2814.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qiodevice.h.A3C9B518FB2E1077.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qiodevicebase.h.0D1B1D8DA5CAA025.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qitemselectionmodel.h.D6BA511D9E08CE92.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qiterable.h.BB42B7747191E5B9.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qiterator.h.52BB425EC8A17FD7.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QJsonArray.7112725520889828.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qjsonarray.h.94F3500BCF742E4E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QJsonDocument.87659FA48FDE612C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qjsondocument.h.4DCEE28D68DC7A5B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QJsonObject.B3505D73ECFEEBD8.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qjsonobject.h.1743321A3ED6D0FC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QJsonParseError.87C26B0FCDBE708C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qjsonvalue.h.6079870DA0CA2B1F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qkeysequence.h.99165846931D9C7A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QLabel.4A5054D779002A1E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qlabel.h.FBB59325F14963A1.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qlayout.h.92E824E5A4835F2E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
)" R"(
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qlayoutitem.h.00F283E95FCED4CA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QLCDNumber.063C29137E05F68A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qlcdnumber.h.A91BEE2CB349AAD2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qline.h.13F8A6CF8F045EC2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qlist.h.CC1868D280B1FBA7.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qlocale.h.D8EAE50BFA48AE43.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qlogging.h.1E41B1D48BDD787F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmalloc.h.6A1583A2E36CC707.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmap.h.4E3141C9610927B8.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmargins.h.FB2A6B3E2E4F3CFC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmath.h.C6FD53386481747B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QMessageBox.A98826180B18751A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmessagebox.h.E676E67394329919.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmetacontainer.h.4D7094C05C4A50C1.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmetatype.h.CA643542C08EDE26.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QMimeDatabase.6F11F82D4DABC727.idx/";"CheckQint64Time": "1690452233";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 18:03:53"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmimedatabase.h.9AECDA9EFA659B18.idx/";"CheckQint64Time": "1690452233";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 18:03:53"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QMimeType.AA3FB86D74956AB1.idx/";"CheckQint64Time": "1690452233";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 18:03:53"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qmimetype.h.6423CEA806BA60B5.idx/";"CheckQint64Time": "1690452233";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 18:03:53"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qminmax.h.A7134EE4E42A7201.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qnamespace.h.80FCAE74E3696591.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qnativeinterface.h.8AE8D2B7F91FB785.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qnumeric.h.3AB5FF1690442750.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qobject.h.F6B8FA2A6FA48299.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qobjectdefs.h.1414CCF1B9B8D3DD.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qobjectdefs.h.78913DAB9F02C16B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qobjectdefs_impl.h.61C594075327ECF2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qobject_impl.h.6FB8F9B98409801A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qoverload.h.5FE97A8DDD88FD6D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpaintdevice.h.B656B6DC22755FA0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpair.h.D82E01804F84A3BC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpalette.h.81D00C9700EEF31A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpicture.h.09372BD3CB04C50B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpixelformat.h.E47D17E527DEF9C0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpixmap.h.291DEE16CF311E00.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpoint.h.4C82A4AD4B40C56A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpolygon.h.AF0C315F7CB24BC3.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qprocessordetection.h.34911D6793AB8F49.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QPushButton.917F7A0C877944DA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qpushbutton.h.3C33923D50BA9266.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qrect.h.1B310BAF79ED7879.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qrefcount.h.9C3F0A5B7CC8FE47.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qregion.h.A195B2DBF2869CC5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qregularexpression.h.63290A6D4636D04C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qrgb.h.30E956A94B0A5FBF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qrgba64.h.F14186D0E686EE98.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qrubberband.h.CCC82D7D1C818FDD.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qscopedpointer.h.6DB4217AEA45579B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qscopeguard.h.80A6E1012D97B603.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qset.h.F640F658D855B095.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
)" R"(
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qshareddata.h.6B3D691B4CF411EC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qshareddata_impl.h.10A7FA87E8C9F8E3.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qsharedpointer.h.A8E72003B77F4435.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qsharedpointer_impl.h.0C44D95493CEFC41.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qsize.h.A3C25A40B77789B2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qsizepolicy.h.A604067E8D354F4C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qslider.h.6778A65280F56038.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QSpacerItem.571B7C00A1D29B43.idx/";"CheckQint64Time": "1690431227";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 12:13:47"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QSplitter.A87E667221B7E825.idx/";"CheckQint64Time": "1690415574";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 07:52:54"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qsplitter.h.3BD88C8D6F64E895.idx/";"CheckQint64Time": "1690415574";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 07:52:54"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QStandardItem.79A37FF9DF43B6DA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QStandardItemModel.E881DEFF1593AC99.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstandarditemmodel.h.863409C5372363E6.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstring.h.7532E8510E800905.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstringalgorithms.h.EF3F56A29E4344CF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstringconverter_base.h.7BFEE5991FD2BCC4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstringfwd.h.B306206EFADADDD0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstringlist.h.7585C8192A0B8FA6.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstringliteral.h.2CA7616EF4BB02B1.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstringmatcher.h.C56F0193885FF36D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstringtokenizer.h.8D4FB22E77BEF580.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstringview.h.4C4E652B2CE2AFAE.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstyle.h.A203361D4EBC6D72.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qstyleoption.h.D220427DCD1B4683.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qswap.h.C4F1FFB966C54D92.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qsysinfo.h.E79561D3492AA412.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qsystemdetection.h.91E352DF2B11EE37.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtabbar.h.E717F0E21C817FCC.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtabwidget.h.3D2D7C82969E6469.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtaggedpointer.h.82C7E8AEC2B8FE9A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtclasshelpermacros.h.502C828F00D41FF8.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtconfigmacros.h.EF8B1203C857E098.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtcore-config.h.8308A25BF98840BF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtcoreexports.h.994CB1BE52EC9A58.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtdeprecationmarkers.h.F5B06341715BD197.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtenvironmentvariables.h.816734D3E857F0A4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtextdocument.h.A2161A8AAA312EE5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtextstream.h.15164900355BDF36.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtgui-config.h.ECF25FD2445C4C3F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtguiexports.h.20D3789A587648C3.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtguiglobal.h.F9AC63F8273459F7.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtmetamacros.h.BE51BD94956667E0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtnoop.h.D318438B1F47F2EA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtpreprocessorsupport.h.C4EB52555990EC39.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtransform.h.920B3E56C1867A55.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QTreeView.507B0A1E52B50BA9.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtreeview.h.3E0528ADF4764A43.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtresource.h.B21FF410190DD3B6.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qttranslation.h.789C43B753A476E7.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qttypetraits.h.4B46775A0BEDB61C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
)" R"(
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtversion.h.686F89BC6F28CD86.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtversionchecks.h.026F9AC2BEF0F6D2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtwidgets-config.h.B22324654F879C71.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtwidgetsexports.h.FC442653A0B3B556.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtwidgetsglobal.h.892B207AE2CAA785.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtypeinfo.h.DD300D2982B201EF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qtypes.h.34C1A54BAA2A97A5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qurl.h.F3B09855CAE52D5A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qutf8stringview.h.2A50E61F260C7CD5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/quuid.h.1C58A12FA2407A31.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qvalidator.h.2CFFE3058A1D3CE9.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QVariant.1BB61C07F983763E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qvariant.h.2E3A0B6311B05BEA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qvarlengtharray.h.77C1CEEDCCD7D7F3.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QVBoxLayout.FC7DC782ECFE299F.idx/";"CheckQint64Time": "1690431227";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 12:13:47"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qversiontagging.h.F88FD207DE87A8C5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/QWidget.21BA7436E839B1CD.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qwidget.h.B886763A5BA666BE.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qwindowdefs.h.532C063EBBBB4552.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qwindowdefs_win.h.D6BA4A783877628F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/qxptype_traits.h.4F8D61AB7C1C5326.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/ratio.C6FACC67546FFCA0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/sal.h.1C9CF74E7F6BAC9B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/setjmp.h.3BB22334FEE4D10F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/share.h.775B5EBE027B509D.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stat.h.5047F8B9082C84A2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stdarg.h.4BB05D4934CD3658.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stdbool.h.656DF20E022C20B3.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stddef.h.5027B43BC208C641.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stdexcept.EE424D8C4195B882.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stdint.h.7D1C380C9B46DB7A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stdint.h.C10B0D7B913FE173.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stdio.h.D33E05345EC1A10A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/stdlib.h.ED0696BD7A47DF9E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/streambuf.8D9B27EB97BC40B5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/string.514E0AB2F59C8D21.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/string.h.9DE4699AD584AFB2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/string_view.2A2A5C5F911B54A0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/system_error.36152983C2069315.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/time.h.F2ED5CAFA1133060.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/tuple.2B8A560E215B3CDB.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/typeinfo.D44221A938BCE44C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/types.h.20FF288202F761C1.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/type_traits.7190FE2AE541F94F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/ui_mywidget.h.FAC1C5CE9E83A287.idx/";"CheckQint64Time": "1690431227";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.27 12:13:47"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/unordered_map.6D701991804ECF76.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/use_ansi.h.1D30BC1BD4F699E2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/utility.9C47A7922FB842EF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vadefs.h.299B0006B53DBFCF.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vadefs.h.F6E26EB65D36CE5E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
)" R"(
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/variant.649C9ED58C473CD2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vcruntime.h.AAB31D7B7BCCD4F0.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vcruntime_exception.h.72BF0AACA1F19447.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vcruntime_new.h.38DFFEABFC7E7A7B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vcruntime_new_debug.h.37ED41FA82326C44.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vcruntime_string.h.BDAF1BA1E90E3BC2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vcruntime_typeinfo.h.470559F7955C4A90.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/vector.7BAF0B9D826000E9.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/version.E305A414D4AD6D69.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/wchar.h.2F8BF9720D625835.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/x86gprintrin.h.9ABBD493A7616DFD.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/x86intrin.h.0A86660698E282E4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xatomic.h.CA1EA98993210B4C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xbit_ops.h.75A4AFA19D1E2894.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xcall_once.h.2E5B720A47B8E4A8.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xerrc.h.3A5F809E8C0439E5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xfacet.7656D2FAF93B98C6.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xfilesystem_abi.h.1D7BB7F6E238BC44.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xhash.BB64DFAF202B08C2.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xiosbase.11BF7B96F6FB0F6E.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xkeycheck.h.446B0E4F6069422B.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xlocale.E30584607870E8A3.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xlocbuf.6FE3163A0835007F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xlocinfo.3E49836069E29381.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xlocmes.B2D0ACF13058C440.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xlocmon.37583FBF562D3734.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xlocnum.8814B4FBD229622C.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xloctime.631CDC99A444F2FB.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xmemory.04435719BFC927CA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xmmintrin.h.82EA2CC20D6A10E5.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xnode_handle.h.9674A0D90153EF17.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xpolymorphic_allocator.h.B60A0E245B5CADB4.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xsaveintrin.h.06D434FD8C34C69F.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xsmf_control.h.49295DED1F67F067.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xstddef.48B6B36131B62FFA.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xstring.B8FAFCA137A6A414.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xthreads.h.FF54C47FB4B7382A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xtimec.h.7EBD356A27955504.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xtr1common.E49B2C47A014CB5A.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xtree.80AD9DA8439D3086.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/xutility.102A0CD5A197B686.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/yvals.h.0315B3A9C4B27910.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/yvals_core.h.D79E2161B6D038AE.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/__msvc_chrono.hpp.C53D586FCE0358C7.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/__msvc_system_error_abi.hpp.CFB01E470000EDDE.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/__msvc_xlocinfo_types.hpp.1A22C9FFD90532E7.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache/clangd/index/__stddef_max_align_t.h.FEDF5B123A8C95DD.idx/";"CheckQint64Time": "1690176641";"QMimeType": "application/x-riff";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/compile_commands.json/";"CheckQint64Time": "1690452231";"QMimeType": "application/json";"LastModifiedTime": "2023.07.27 18:03:51"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/";"CheckQint64Time": "1690460778";"QMimeType": "inode/directory";"LastModifiedTime": "2023.07.27 20:26:18"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.exe/";"CheckQint64Time": "1690493121";"QMimeType": "application/x-ms-dos-executable";"LastModifiedTime": "2023.07.28 05:25:21"},
)" R"(
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.ilk/";"CheckQint64Time": "1690493121";"QMimeType": "application/octet-stream";"LastModifiedTime": "2023.07.28 05:25:21"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.pdb/";"CheckQint64Time": "1690493121";"QMimeType": "application/vnd.palm";"LastModifiedTime": "2023.07.28 05:25:21"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.vc.pdb/";"CheckQint64Time": "1690493120";"QMimeType": "application/vnd.palm";"LastModifiedTime": "2023.07.28 05:25:20"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/main.obj/";"CheckQint64Time": "1690462513";"QMimeType": "application/x-tgif";"LastModifiedTime": "2023.07.27 20:55:13"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_mywidget.cpp/";"CheckQint64Time": "1690462511";"QMimeType": "text/x-c++src";"LastModifiedTime": "2023.07.27 20:55:11"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_mywidget.obj/";"CheckQint64Time": "1690462513";"QMimeType": "application/x-tgif";"LastModifiedTime": "2023.07.27 20:55:13"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_predefs.h/";"CheckQint64Time": "1690176641";"QMimeType": "text/x-chdr";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/mywidget.obj/";"CheckQint64Time": "1690493120";"QMimeType": "application/x-tgif";"LastModifiedTime": "2023.07.28 05:25:20"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/Makefile/";"CheckQint64Time": "1690493214";"QMimeType": "text/x-makefile";"LastModifiedTime": "2023.07.28 05:26:54"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/Makefile.Debug/";"CheckQint64Time": "1690493214";"QMimeType": "text/x-makefile";"LastModifiedTime": "2023.07.28 05:26:54"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/Makefile.Release/";"CheckQint64Time": "1690493214";"QMimeType": "text/x-makefile";"LastModifiedTime": "2023.07.28 05:26:54"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/release/";"CheckQint64Time": "1690176759";"QMimeType": "inode/directory";"LastModifiedTime": "2023.07.24 13:32:39"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/rememberFileState.txt/";"CheckQint64Time": "1690493225";"QMimeType": "text/plain";"LastModifiedTime": "2023.07.28 05:27:05"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/testNewFile.txt/";"CheckQint64Time": "1690342223";"QMimeType": "text/plain";"LastModifiedTime": "2023.07.26 11:30:23"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/ui_mywidget.h/";"CheckQint64Time": "1690426472";"QMimeType": "text/x-chdr";"LastModifiedTime": "2023.07.27 10:54:32"}
])";

#endif


    QJsonParseError parse;
    // The string is not a valid json, the separator must be a comma
    // and not a semicolon, which is why it is being replaced
    QByteArray data = QByteArray::fromStdString(json).replace(";", ",");
    QJsonDocument const& jdoc =  QJsonDocument::fromJson(data, &parse);
    Q_ASSERT(parse.error == QJsonParseError::NoError);
    if(jdoc.isArray()){
        for(const QJsonValue &element : jdoc.array() ){
            QJsonObject obj = element.toObject();
            QString NeedToFindName = obj["name"].toString();
            QString LastModifiedTime = obj["LastModifiedTime"].toString();

            QByteArray NeedToFindNameByteArray = NeedToFindName.toLocal8Bit();
            //const char *c_str2 = NeedToFindNameByteArray.data();
            char* NeedToFindNameByteArrayToCharPointer = NeedToFindNameByteArray.data();

            QString QMimeTypeForCheck = obj["QMimeType"].toString();

            QByteArray QMimeTypeForCheckByteArray = NeedToFindName.toLocal8Bit();
            //const char *c_str2 = NeedToFindNameByteArray.data();
            char* QMimeTypeForCheckeByteArrayToCharPointer = NeedToFindNameByteArray.data();


            appendToModel(&model, NeedToFindName.split("/", Qt::SkipEmptyParts), LastModifiedTime);
        }
    }

//    viewLeft = new QTreeView(this);
//    viewLeft->setModel(&model);
//    viewLeft->move(5,200);
//    viewLeft->resize(300,200);
//    viewLeft->show();

    //treeView = new QTreeView(this);
    //treeView.setModel(&model);
    ui->treeView->setModel(&model);

//    treeView->move(5,200);
//    treeView->resize(300,200);
    //treeView.show();


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
    if(1 == CheckWantOperaDirChooseIf){
        if(0 == CheckSkipDirChooseIf){
            reply = QMessageBox::question(this, "IMPORTANT NOTICE 2", "Now ready to backup status of files that directory is: "
                                                                          + WantOperaDirToQstring + "\n\n" + "When backup, program may be appear doesn't response, it's normal, just only wait a moment, " +
                                                                          "then you will get tip of backup file state have done.",
                                          QMessageBox::Save | QMessageBox::Cancel);
            if (reply == QMessageBox::Save) {

                //需要实现文件状态的备份
                qDebug() << "Now ready to status of backup files that directory is: " << WantOperaDirToQstring;
                qDebug() << "*************** This function need to be do! ***************";

                qDebug() << "Backup file path is:" << WantOperaDirToQstring;
                MyWidget::BackupDirAndFileState(WantOperaDirToQstring);
            }

            if(reply == QMessageBox::Cancel)
            {
                ;
            }
        }else{
            reply = QMessageBox::question(this, "IMPORTANT NOTICE 2", "Now ready to backup status of files that directory is: "
            + WantOperaDirToQstring + "\n\n" + "You don't want to backup directory is:" + WantSkipBackupDirToQstring +"\n\n" +
            "When backup, program may be appear doesn't response, " +
            "it's normal, just only wait a moment, " +
            "then you will get tip of backup file state have done.",
                                          QMessageBox::Save | QMessageBox::Cancel);
            if (reply == QMessageBox::Save) {

                //需要实现文件状态的备份
                qDebug() << "Now ready to status of backup files that directory is: " << WantOperaDirToQstring;
                qDebug() << "*************** This function need to be do! ***************";

                qDebug() << "Backup file path is:" << WantOperaDirToQstring;
                MyWidget::BackupDirAndFileState(WantOperaDirToQstring);
            }

            if(reply == QMessageBox::Cancel)
            {
                ;
            }
        }
    }else{
        QMessageBox msgBoxTip;
        msgBoxTip.setText("You don't choose directory!");
        msgBoxTip.exec();
    }

}

void MyWidget::FindStringInBackFileLineByLine(char* NeedToFindString, char* ReturnValue, int mode)
{
    int index;
    int begin = 0;
    int m, k;
    int FindCheckFlag = 0;
    QFile file(BackupFileStateDirToQstring + "rememberFileState.txt");
    QFileInfo check_file(file);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox msgBoxTip;
            msgBoxTip.setText("Can't find backup file");
            msgBoxTip.exec();
        }


        QTextStream in(&file);

        while (!in.atEnd())
        {
            //QString line = in.readLine(); //specifying number = # of characters
            //lstLine.append( line.split(",") );
            char buf[1024] = {0};

            qint64 lineLength = file.readLine(buf, sizeof(buf));

            //temp comment
            //qDebug() << "buf is:" << buf;


            if (lineLength != -1){

                //temp comment
                //qDebug() << "readline by line:" << QString(buf);
                // the line is available in buf
                index = strindexP(buf, NeedToFindString);
                //temp comment
                //qDebug() << "strindexP rerunt index is:" << index;
                FindCheckFlag = index;
                if(index >= 0){
                    //strncmp(LastRecordTimeP,buf,60);

                    //LastRecordTimeToString = QString(LastRecordTimeP);
                    //qDebug() << "LastRecordTimeToString is:" << LastRecordTimeToString;

                    //temp comment
                    //qDebug() << "*******Find what I want to find:" << QString(buf);

                    size_t bufLength = strlen(buf);
                    //temp comment
                    //qDebug() << "buf is:" << buf;
                    if(0 == mode){

                        //temp comment
                        //qDebug() << "i is:" << index;
                        //qDebug() << "LastRecordTimePLength is:" << bufLength;
                        while(buf[begin] != ':'){
                            begin = begin + 1;
                        }
                        for(m = begin+1, k = 0; buf[m] != '\n'; m++, k++){
                            ReturnValue[k] = buf[m];
                        }
                        ReturnValue[k] = '\0';
                        //temp comment
                        //qDebug() << "ReturnValue is:" << QString(ReturnValue);

                        //other
                        //qDebug() << "LastRecordTime is:" << QString(LastRecordTime);
                        //return ReturnValue;

                        if(FindCheckFlag >=0){
                            break;
                        }
                    }else{
                        size_t nnm = 0;
                        for(; nnm < bufLength; nnm++){
                            ReturnValue[nnm] = buf[nnm];
                        }
                        //nnm = nnm + 1;
                        ReturnValue[nnm] = '\0';
                        //temp comment
                        //qDebug() << "ReturnValue is:" << ReturnValue;
                    }

                }


            }
        }
    }else{
        QMessageBox msgBoxTip;
        msgBoxTip.setText("You not haved backup file!");
        msgBoxTip.exec();
    }

    file.close();
}

//Display last time status of backup files date
void MyWidget::on_pushButton_4_clicked()
{
    char NeedToFindTime[] = "Last time backup file state time:";
    char NeedToFindBackFilePath[] = "backup file path:";


    QFile file(BackupFileStateDirToQstring + "rememberFileState.txt");
    QFileInfo check_file(file);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox msgBoxTip;
            msgBoxTip.setText("Can't find open backup file");
            msgBoxTip.exec();
        }else{
            char* ReceiveReturnTime = new char [1000];
            char* ReceiveReturnPath = new char [1000];
            MyWidget::FindStringInBackFileLineByLine(NeedToFindTime, ReceiveReturnTime, 0);
            MyWidget::FindStringInBackFileLineByLine(NeedToFindBackFilePath, ReceiveReturnPath, 0);

            qDebug() << "backup file path is:" << QString(ReceiveReturnPath);

            reply = QMessageBox::information(this, "IMPORTANT NOTICE 3", "Last time backup file path is:\n" + QString(ReceiveReturnPath),
                                          QMessageBox::Ok | QMessageBox::Cancel);
            if (reply == QMessageBox::Ok) {
                    ui->lcdNumber->setDigitCount(25);
                    ui->lcdNumber->display(QString(ReceiveReturnTime));
            }
            if(reply == QMessageBox::Cancel){
                ;
            }

            delete [] ReceiveReturnTime;
            delete [] ReceiveReturnPath;
        }
    }else{
        ui->lcdNumber->setDigitCount(25);
        ui->lcdNumber->display(QString("0"));
        QMessageBox msgBoxTip;
        msgBoxTip.setText("Can't find backup file");
        msgBoxTip.exec();

    }

}

//Choose dircetory that you want to skip, not backup
void MyWidget::on_pushButton_5_clicked()
{
    if(CheckWantOperaDirChooseIf != 1){
        QMessageBox msgBoxTip;
        msgBoxTip.setText("Please first select the directory you want to operate on!");
        msgBoxTip.exec();
        return;
    }
    QDir WantSkipBackupDir = QFileDialog::getExistingDirectory(this, tr("select directory"));

    qDebug() << "**A** WantOperaDirToQstring's Path is " << WantSkipBackupDir.absolutePath();
    qDebug() << "**B** WantSkipOperaDir is " << WantSkipBackupDir;


    if(!WantSkipBackupDir.path().contains("/")){
        return;
    }else{
        reply = QMessageBox::question(this, "IMPORTANT NOTICE 4", "You don't want to backup directory is: " + WantSkipBackupDir.absolutePath(),
                                      QMessageBox::Save | QMessageBox::Cancel);

        if (reply == QMessageBox::Save) {
            WantSkipBackupDir = WantSkipBackupDir.absolutePath() + "/";
            WantSkipBackupDirToQstring = WantSkipBackupDir.path() + "/";
            CheckSkipDirChooseIf = 1;
            qDebug() << "**C** WantOperaDirToQstring's Path is " << WantSkipBackupDir.path();
            qDebug() << "**D** You don't want to backup save was clicked, now you don't want to backup directory is: " << WantSkipBackupDirToQstring;
        }
        if(reply == QMessageBox::Cancel)
        {
            CheckSkipDirChooseIf = 0;
            return;
        }

    }

    if(!WantSkipBackupDir.absolutePath().contains(WantOperaDirToQstring, Qt::CaseSensitive)){
        QMessageBox msgBoxTip;
        msgBoxTip.setText("ERROR:\n\n"
                          "You want to Opera dir is:" + WantOperaDirToQstring + "\n\n" +
                          "You want to skip dir is:" + WantSkipBackupDir.absolutePath() + "\n\n" +
                          "The directories are invalid. May be they are same or the directories are inconsistent." + "\n\n" +
                          "Please select directory again.");
        msgBoxTip.exec();
        return;
    }

}

