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
#if MyWidget_appendToModel_DEBUG
        qDebug() << "********************************************************************print list is:" << list;
#endif
        QList BeforeGoCheckDirOrFile = list;
        QList listCopy = list;
        QString JudgeDirOrFile;
        for ( const auto& CheckValue : BeforeGoCheckDirOrFile )
        {
#if MyWidget_appendToModel_DEBUG
            qDebug() << "CheckValue is:" << CheckValue;
#endif
            JudgeDirOrFile.append(CheckValue);
            JudgeDirOrFile.append('/');

        }
        JudgeDirOrFile.removeLast();
#if MyWidget_appendToModel_DEBUG
        qDebug() << "Look JudgeDirOrFile is:" << JudgeDirOrFile;
#endif
        QByteArray JudgeDirOrFileByteArray = JudgeDirOrFile.toLocal8Bit();

        char JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks[1000] = {0};
        char lookDirIncludeIf[1000] = {0};
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

#if MyWidget_appendToModel_DEBUG
        qDebug() << "JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks is:" << JudgeDirOrFileByteArrayToCharPointerAddOneQuotationMarks;
        qDebug() << "ReceiveNeedToFindNameByteArrayToCharPointer is " << ReceiveNeedToFindNameByteArrayToCharPointer;
#endif

        if(0 == strlen(ReceiveNeedToFindNameByteArrayToCharPointer)){
            QMessageBox msgBox;
            msgBox.setText("ReceiveNeedToFindNameByteArrayToCharPointer is NULL!");
            msgBox.exec();
        }

        if((MyWidget::strindexP(ReceiveNeedToFindNameByteArrayToCharPointer, QMimeTypePPP) >= 0)){
            if((MyWidget::strindexP(ReceiveNeedToFindNameByteArrayToCharPointer, directoryPPP) >= 0)){
                NowCheckIsDir = 1;
            }
        }

        if(1 == NowCheckIsDir){
#if MyWidget_appendToModel_DEBUG
            qDebug() << "ReceiveNeedToFindNameByteArrayToCharPointer is " << ReceiveNeedToFindNameByteArrayToCharPointer << " that is directory." ;
#endif
        }else{
#if MyWidget_appendToModel_DEBUG
            qDebug() << "ReceiveNeedToFindNameByteArrayToCharPointer is " << ReceiveNeedToFindNameByteArrayToCharPointer << " that is file." ;
#endif
        }


//        if(std::next(it) == list.end() && NowCheckIsDir != 1){
//            qDebug() << "---File----In std::next(it) == list.end() list is:" << list;
//            item->setIcon(provider.icon(QFileIconProvider::File));
//            parentItem->appendRow({item, new QStandardItem(LastModifiedTime)});
//        }
//        else if(NowCheckIsDir == 1){
//            qDebug() << "****Folder****In std::next(it) != list.end() list is:" << list;
//            item->setIcon(provider.icon(QFileIconProvider::Folder));
//            parentItem->appendRow(item);
//        }

        if(NowCheckIsDir == 1){
#if MyWidget_appendToModel_DEBUG
            qDebug() << "****Folder****In std::next(it) != list.end() list is:" << list;
#endif
            item->setIcon(provider.icon(QFileIconProvider::Folder));
            parentItem->appendRow(item);
        }
        else if(std::next(it) == list.end()){
#if MyWidget_appendToModel_DEBUG
            qDebug() << "---File----In std::next(it) == list.end() list is:" << list;
#endif
            item->setIcon(provider.icon(QFileIconProvider::File));
            item->setBackground(Qt::red);
            parentItem->appendRow({item, new QStandardItem(LastModifiedTime)});
        }else{
#if MyWidget_appendToModel_DEBUG
            qDebug() << "****Folder****In std::next(it) != list.end() list is:" << list;
#endif
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
#if MyWidget_BackupDirAndFileState_DEBUG
    qDebug() << "Date is:"+formattedTime;
#endif
    LastRecordTimeToString = formattedTime;

    QDir BackupFileStateDir = BackupFileStateDir.currentPath();
    QString  BackupFileStateDirToQstring= BackupFileStateDir.path() + "/";

#if MyWidget_BackupDirAndFileState_DEBUG
    qDebug() << "APPCurrentPath is:" << BackupFileStateDir;
    qDebug() << "APPCurrentPathToString is:" << BackupFileStateDirToQstring;
#endif

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
//    out << "This file is generated by Qt, please don't modify\n";
//    out << "backup file path:" << WantOperaDirToQstring + "\n";
//    out << "Last time backup file state time:" << formattedTime << "\n";
//    out << "R\"([" << "\n";

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
#if MyWidget_BackupDirAndFileState_DEBUG
                qDebug() << "In (1 == CheckSkipDirChooseIf) check_file is:"<< check_file << " mime is: " << mime;
#endif
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

//                /* test.json */
//                {
//                    {
//                        "name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qmake.stash",
//                        "CheckQint64Time": "1690176641",
//                        "QMimeType": "text/plain",
//                        "LastModifiedTime": "2023.07.25 18:21:55"
//                    },
//                    {
//                        "name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd",
//                        "CheckQint64Time": "1690280515",
//                        "QMimeType": "inode/directory",
//                        "LastModifiedTime": "2023.07.25 18:21:55"
//                    }
//                        "name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/.qtc_clangd/.cache",
//                        "CheckQint64Time": "1690176641",
//                        "QMimeType": "inode/directory",
//                        "LastModifiedTime": "2023.07.25 18:21:55"
//                }

                //good
//                //out << "\"name\":"<<dir << ";" << "\"LastModifiedTime\":" << lastModified.toString() << "\n";
//                out << "{" << "\"name\": "<< "\"" << dir << "\"" << ";" << "\"CheckQint64Time\": " <<  "\"" << CheckQint64Time
//                << "\"" << ";" << "\"QMimeType\": " << "\"" << mime.name() << "\""<< ";" <<  "\"LastModifiedTime\": " << "\"" << lastModifiedTimeToqint64ForCheck << "\"" << "}," << "\n";
//                //qDebug() << "\"name\":"<<dir;

                //out << "\"name\":"<<dir << ";" << "\"LastModifiedTime\":" << lastModified.toString() << "\n";
                out << "{" << "\"name\": "<< "\"" << dir << "\"" << ";" << "\"CheckQint64Time\": " <<  "\"" << CheckQint64Time
                    << "\"" << ";" << "\"QMimeType\": " << "\"" << mime.name() << "\""<< ";" <<  "\"LastModifiedTime\": " << "\"" << lastModifiedTimeToqint64ForCheck << "\"" << "}," << "\n";
                //qDebug() << "\"name\":"<<dir;



            }
        }else{
            if(!dir.endsWith("/.", Qt::CaseSensitive) && !dir.endsWith("/..", Qt::CaseSensitive)){


                QFile file(dir);
                QFileInfo check_file(file);

                QMimeDatabase db;
                QMimeType mime = db.mimeTypeForFile(check_file, QMimeDatabase::MatchDefault);

#if MyWidget_BackupDirAndFileState_DEBUG
                qDebug() << "In (1 != CheckSkipDirChooseIf) check_file is:"<< check_file << " mime is: " << mime;
#endif
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
                out << "{" << "\"name\": "<< "\"" << dir << "\"" << ";" << "\"CheckQint64Time\": " <<  "\"" << CheckQint64Time
                    << "\"" << ";" << "\"QMimeType\": " << "\"" << mime.name() << "\""<< ";" <<  "\"LastModifiedTime\": " << "\"" << lastModifiedTimeToqint64ForCheck << "\"" << "}," << "\n";
                //qDebug() << "\"name\":"<<dir;


            }
        }

    }

     //QTextStream out(&file);

    //out << "])\";" << "\n";
    file.close();

    QFileInfo again_check_file(file);

    // check if file exists and if yes: Is it really a file and no directory?
    if (again_check_file.exists() && again_check_file.isFile()) {
        file.open(QIODevice::ReadWrite); // Or QIODevice::ReadWrite or QIODevice::WriteOnly
        QTextStream AgainOut(&file);
        qint64 fileSize = file.size();

#if MyWidget_BackupDirAndFileState_DEBUG
        qDebug() << "fileSize is:" << fileSize << "bytes";
#endif

        file.seek(fileSize - 8);
        QString TestReadChar = file.read(1);
        AgainOut << "\n])\";" << "\n";
#if MyWidget_BackupDirAndFileState_DEBUG
        qDebug() << "Read char or string is:" << TestReadChar;
#endif

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
#if MyWidget_on_pushButton_clicked_DEBUG
            qDebug() << "Save was clicked, now you choice directory is: " << WantOperaDirToQstring;
#endif
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




    const std::string json = R"([
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.exe";"CheckQint64Time": "1690512815";"QMimeType": "application/x-ms-dos-executable";"LastModifiedTime": "2023.07.28 10:53:35"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.ilk";"CheckQint64Time": "1690512815";"QMimeType": "application/octet-stream";"LastModifiedTime": "2023.07.28 10:53:35"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.pdb";"CheckQint64Time": "1690512815";"QMimeType": "application/vnd.palm";"LastModifiedTime": "2023.07.28 10:53:35"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/CheckDirectoryAndFileChange.vc.pdb";"CheckQint64Time": "1690512815";"QMimeType": "application/vnd.palm";"LastModifiedTime": "2023.07.28 10:53:35"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/main.obj";"CheckQint64Time": "1690462513";"QMimeType": "application/x-tgif";"LastModifiedTime": "2023.07.27 20:55:13"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_mywidget.cpp";"CheckQint64Time": "1690462511";"QMimeType": "text/x-c++src";"LastModifiedTime": "2023.07.27 20:55:11"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_mywidget.obj";"CheckQint64Time": "1690462513";"QMimeType": "application/x-tgif";"LastModifiedTime": "2023.07.27 20:55:13"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/moc_predefs.h";"CheckQint64Time": "1690176641";"QMimeType": "text/x-chdr";"LastModifiedTime": "2023.07.24 13:30:41"},
{"name": "C:/my-win10-document/code/CheckDirectoryAndFileChange/build-CheckDirectoryAndFileChange-Desktop_Qt_6_5_1_MSVC2019_64bit-Debug/debug/mywidget.obj";"CheckQint64Time": "1690512815";"QMimeType": "application/x-tgif";"LastModifiedTime": "2023.07.28 10:53:35"}
])";



    QFile file(BackupFileStateDirToQstring + "rememberFileState.txt");
    QTextStream stream(&file);
    QStringList list;
    int line = 0;
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray ar = file.readAll();
        QByteArray str;
        for(int i = 0; i < ar.size(); i++) {
            if(line != 0 && line != 1 && line != 2 && line !=3) {
                if(ar.at(i) == '\n') {
                    list << QString::fromUtf8(str.replace("\"", ""));
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



    qDebug() << "*********------*********read list is" << list;
    qDebug() << "*****iterate list:";
    QString TestJson;
    for ( const auto& i : list )
    {
        qDebug() << i;
        TestJson.replace("\"","");
        TestJson.append(i);
    }
    qDebug() << "TestJson is:" << TestJson;
    //QString TestJsonDeleteFenao = TestJson.replace("\"","");
#if MyWidget_on_pushButton_2_clicked_DEBUG
    //qDebug() << "Delete yinhao after TestJson is:" << TestJsonDeleteFenao;
#endif


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



#if 0

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

#if MyWidget_FindStringInBackFileLineByLine_DEBUG
            qDebug() << "buf is:" << buf;
#endif

            if (lineLength != -1){

#if MyWidget_FindStringInBackFileLineByLine_DEBUG
                qDebug() << "readline by line:" << QString(buf);
#endif
                // the line is available in buf
                index = strindexP(buf, NeedToFindString);
#if MyWidget_FindStringInBackFileLineByLine_DEBUG
                //qDebug() << "strindexP rerunt index is:" << index;
#endif
                FindCheckFlag = index;
                if(index >= 0){
                    //strncmp(LastRecordTimeP,buf,60);

                    //LastRecordTimeToString = QString(LastRecordTimeP);
                    //qDebug() << "LastRecordTimeToString is:" << LastRecordTimeToString;

#if MyWidget_FindStringInBackFileLineByLine_DEBUG
                    qDebug() << "*******Find what I want to find:" << QString(buf);
#endif
                    size_t bufLength = strlen(buf);
#if MyWidget_FindStringInBackFileLineByLine_DEBUG
                    qDebug() << "buf is:" << buf;
#endif
                    if(0 == mode){

#if MyWidget_FindStringInBackFileLineByLine_DEBUG
                        qDebug() << "i is:" << index;
                        qDebug() << "LastRecordTimePLength is:" << bufLength;
#endif
                        while(buf[begin] != ':'){
                            begin = begin + 1;
                        }
                        for(m = begin+1, k = 0; buf[m] != '\n'; m++, k++){
                            ReturnValue[k] = buf[m];
                        }
                        ReturnValue[k] = '\0';
#if MyWidget_FindStringInBackFileLineByLine_DEBUG
                        qDebug() << "ReturnValue is:" << QString(ReturnValue);
#endif
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
#if MyWidget_FindStringInBackFileLineByLine_DEBUG
                        qDebug() << "ReturnValue is:" << ReturnValue;
#endif
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

#if MyWidget_on_pushButton_5_clicked_DEBUG
    qDebug() << "**A** WantOperaDirToQstring's Path is " << WantSkipBackupDir.absolutePath();
    qDebug() << "**B** WantSkipOperaDir is " << WantSkipBackupDir;
#endif

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

