#include "simulationunit.h"

#include <QDebug>
#include <QString>
#include <QThread>



void SimulationUnit::loadLibrary(QString path)
{
    lib = new QLibrary(path);

    if (!lib->load())
    {
        qDebug()<<"Library not loaded. Try again.";
        lib->unload();
        lib->deleteLater();
    }
    else
    {
        loadFunctions();
    }
}

SimulationUnit::SimulationUnit(QObject *parent)
    : QObject{parent}
{
    metaEnum = QMetaEnum::fromType<SIMBA2_RETURN_CODES>();


        //writeIO("S000I0.0");
        //writeIO("S000I0.2");
        //writeIO("S000I0.3");
        //writeIO("S000I0.4");

        //writeIO("S000Q0.0");
        //writeIO("S000Q0.2");
        //writeIO("S000Q0.3");
        //writeIO("S000Q0.4");


        //readIO("S000I0.0");
        //readIO("S000I0.2");
        //readIO("S000I0.3");
        //readIO("S000I0.4");

        //readIO("S000Q0.0");
        //readIO("S000Q0.2");
        //readIO("S000Q0.3");
        //readIO("S000Q0.4");

}

SimulationUnit::~SimulationUnit()
{
    SIMBA_DisconnectAll(-1);
    SIMBA_CloseProjectFile();
}

void SimulationUnit::loadFunctions()
{
    SIMBA_OpenProjectFile       = (SIMBA2_OpenProjectFile  ) lib->resolve("SIMBA2_OpenProjectFile");
    SIMBA_CheckProjectState     = (SIMBA2_CheckProjectState) lib->resolve("SIMBA2_CheckProjectState");
    SIMBA_CloseProjectFile      = (SIMBA2_CloseProjectFile ) lib->resolve("SIMBA2_CloseProjectFile");

    SIMBA_ConnectAll            = (SIMBA2_ConnectAll	     ) lib->resolve("SIMBA2_ConnectAll");
    SIMBA_ConnectAllEx          = (SIMBA2_ConnectAllEx	 ) lib->resolve("SIMBA2_ConnectAllEx");
    SIMBA_IsConnected           = (SIMBA2_IsConnected	     ) lib->resolve("SIMBA2_IsConnected");
    SIMBA_DisconnectAll         = (SIMBA2_DisconnectAll    ) lib->resolve("SIMBA2_DisconnectAll");

    SIMBA_DownloadAll           = (SIMBA2_DownloadAll	     ) lib->resolve("SIMBA2_DownloadAll");
    SIMBA_GetDownloadStatus     = (SIMBA2_GetDownloadStatus) lib->resolve("SIMBA2_GetDownloadStatus");

    SIMBA_ReadIO                = (SIMBA2_ReadIO		     ) lib->resolve("SIMBA2_ReadIO_Unit");
    SIMBA_ReadIO_Bin            = (SIMBA2_ReadIO_Bin	     ) lib->resolve("SIMBA2_ReadIO_Double");
    SIMBA_ReadIO_Double         = (SIMBA2_ReadIO_Double    ) lib->resolve("SIMBA2_ReadIO_Bin");
    SIMBA_ReadIO_Unit           = (SIMBA2_ReadIO_Unit	     ) lib->resolve("SIMBA2_ReadIO");

    SIMBA_WriteIO               = (SIMBA2_WriteIO          ) lib->resolve("SIMBA2_WriteIO");
    SIMBA_WriteIO_Bin           = (SIMBA2_WriteIO_Bin      ) lib->resolve("SIMBA2_WriteIO_Bin");
    SIMBA_WriteIO_Double        = (SIMBA2_WriteIO_Double   ) lib->resolve("SIMBA2_WriteIO_Double");
    SIMBA_WriteIO_Unit          = (SIMBA2_WriteIO_Unit     ) lib->resolve("SIMBA2_WriteIO_Unit");

    SIMBA_SaveProcessIOFile       = (SIMBA2_SaveProcessIOFile       )lib->resolve("SIMBA2_SaveProcessIOFile");
    SIMBA_ReadStringConfiguration = (SIMBA2_ReadStringConfiguration )lib->resolve("SIMBA2_ReadStringConfiguration");
    SIMBA_GetRecentProjectPath    = (SIMBA2_GetRecentProjectPath    )lib->resolve("SIMBA2_GetRecentProjectPath");

    SIMBA_ReadRecordDataExt = (SIMBA2_ReadRecordDataExt)lib->resolve("SIMBA2_ReadRecordDataExt");

    if(!SIMBA_OpenProjectFile  ){qDebug()<<"OpenProjectFile  " << " not loaded.";}
    if(!SIMBA_CheckProjectState){qDebug()<<"CheckProjectState" << " not loaded.";}
    if(!SIMBA_CloseProjectFile ){qDebug()<<"CloseProjectFile " << " not loaded.";}

    if(!SIMBA_ConnectAll	     ){qDebug()<<"ConnectAll	   " << " not loaded.";}
    if(!SIMBA_ConnectAllEx	 ){qDebug()<<"ConnectAllEx	   " << " not loaded.";}
    if(!SIMBA_IsConnected	     ){qDebug()<<"IsConnected	   " << " not loaded.";}
    if(!SIMBA_DisconnectAll    ){qDebug()<<"DisconnectAll    " << " not loaded.";}

    if(!SIMBA_DownloadAll	     ){qDebug()<<"DownloadAll	   " << " not loaded.";}
    if(!SIMBA_GetDownloadStatus){qDebug()<<"GetDownloadStatus" << " not loaded.";}

    if(!SIMBA_ReadIO		     ){qDebug()<<"ReadIO		   " << " not loaded.";}
    if(!SIMBA_ReadIO_Bin	     ){qDebug()<<"ReadIO_Bin	   " << " not loaded.";}
    if(!SIMBA_ReadIO_Double    ){qDebug()<<"ReadIO_Double    " << " not loaded.";}
    if(!SIMBA_ReadIO_Unit	     ){qDebug()<<"ReadIO_Unit	   " << " not loaded.";}

    if(!SIMBA_WriteIO		     ){qDebug()<<"WriteIO		   " << " not loaded.";}
    if(!SIMBA_WriteIO_Bin	     ){qDebug()<<"WriteIO_Bin	   " << " not loaded.";}
    if(!SIMBA_WriteIO_Double   ){qDebug()<<"WriteIO_Double   " << " not loaded.";}
    if(!SIMBA_WriteIO_Unit	 ){qDebug()<<"WriteIO_Unit	   " << " not loaded.";}

    if(!SIMBA_SaveProcessIOFile	    ){qDebug()<<"SaveProcessIOFile	    " << " not loaded.";}
    if(!SIMBA_ReadStringConfiguration ){qDebug()<<"ReadStringConfiguration" << " not loaded.";}
    if(!SIMBA_GetRecentProjectPath	){qDebug()<<"GetRecentProjectPath   " << " not loaded.";}

    if(!SIMBA_ReadRecordDataExt){qDebug()<<"SIMBA_ReadRecordDataExt   " << " not loaded.";}
}


char * SimulationUnit::qstrToChar(QString path)
{
    QByteArray byteArray = path.toLocal8Bit();
    return byteArray.data();
}

void SimulationUnit::runSimProject(QString path, bool download)
{
    if(!lib->isLoaded()){
        qDebug()<<"Lib not loaded";
        return;
    }

    int errorCode;
    int state;

    char *charPath = qstrToChar(path);

    qDebug() << "OpenProjectFile: " << path;
    errorCode = SIMBA_OpenProjectFile(charPath);
    qDebug() << "OpenProjectFile: " << metaEnum.valueToKey(errorCode);


    qDebug() << "CheckProjectState: " << "Start";
    state = 0;
    while(state != 3){
        errorCode = SIMBA_CheckProjectState(&state);
        QThread::sleep(1);
    }
    qDebug() << "CheckProjectState: " << metaEnum.valueToKey(errorCode);


    qDebug() << "ConnectAll";
    errorCode =  SIMBA_ConnectAll(-1);
    qDebug() << "ConnectAll: " << metaEnum.valueToKey(errorCode);

    if(download){
        qDebug() << "DownloadAll";
        errorCode =  SIMBA_DownloadAll(-1);
        qDebug() << "DownloadAll: " << metaEnum.valueToKey(errorCode);

        qDebug() << "GetDownloadStatus: " << "Start";
        state = 0;
        while(state < 100){
            errorCode = SIMBA_GetDownloadStatus(-1, &state);
            QThread::sleep(1);
        }
        qDebug() << "GetDownloadStatus: " << metaEnum.valueToKey(errorCode);
    }
}


void SimulationUnit::readHardware()
{
    int dataSize = 64;
    int firstRead = 1;
    char *data = new char[64]();
    int readDataSize;

    qDebug() << "SIMBA_ReadStringConfiguration";
    while((readDataSize = SIMBA_ReadStringConfiguration(data, dataSize, firstRead)) >= 0){
        firstRead = 0;
        hardwareData.append(data);
    }
    qDebug() << "SIMBA_ReadStringConfiguration" << hardwareData.size();
}

void SimulationUnit::readRecordData(int hwindex, int dev, int slot, int sub, int index)
{
    int errorCode;

    qDebug() << "SIMBA_ReadRecordDataExt";
    char data[128];
    int *maxleng = new int(128);

    errorCode = SIMBA_ReadRecordDataExt(hwindex,dev,slot,sub,index,data,maxleng);
    qDebug() << "SIMBA_ReadRecordDataExt: " << metaEnum.valueToKey(errorCode);
    qDebug() << data;
}

QString SimulationUnit::readIO(QString name)
{

    char value[64];

    SIMBA_ReadIO(qstrToChar(name), value);
    //SIMBA_ReadIO_Bin(char *name, long *value);
    //SIMBA_ReadIO_Double(char *name, double *value);
    //SIMBA_ReadIO_Unit(char *name, char *value);

    qDebug() << value;
    return QString(value);
}

void SimulationUnit::writeIO(QString name, QString value)
{


    SIMBA_WriteIO(qstrToChar(name), qstrToChar(value));
    //typedef int (*SIMBA2_ReadIO_Bin)(char *name, long *value);
    //typedef int (*SIMBA2_ReadIO_Double)(char *name, double *value);
    //typedef int (*SIMBA2_ReadIO_Unit)(char *name, char *value);
}

void SimulationUnit::test()
{

    int val;




    //char *paths = new char[64]();
    //qDebug() << "PATHS";
    //val =SIMBA_GetRecentProjectPath(64, paths);
    //qDebug() << "ReadStringConfiguration: " << metaEnum.valueToKey(val);
    //qDebug() << paths;




}
