
#ifndef SIMULATIONUNIT_H
#define SIMULATIONUNIT_H

#include <QObject>
#include <QLibrary>
#include <QMetaEnum>


typedef int (*SIMBA2_OpenProjectFile)(char* filename);
typedef int (*SIMBA2_CheckProjectState)(int *state);
typedef int (*SIMBA2_CloseProjectFile)();

typedef int (*SIMBA2_ConnectAll)(int hwindex);
typedef int (*SIMBA2_ConnectAllEx)(int hwindex, bool wait) ;
typedef int (*SIMBA2_IsConnected)(int hwindex, int *active);
typedef int (*SIMBA2_DisconnectAll)(int hwindex);


typedef int (*SIMBA2_DownloadAll)(int hwindex);
typedef int (*SIMBA2_GetDownloadStatus)(int hwindex, int *percent);


typedef int (*SIMBA2_ReadIO)(char *name, char *value);
typedef int (*SIMBA2_ReadIO_Bin)(char *name, long *value);
typedef int (*SIMBA2_ReadIO_Double)(char *name, double *value);
typedef int (*SIMBA2_ReadIO_Unit)(char *name, char *value);


typedef int (*SIMBA2_WriteIO)(char *name, char *value);
typedef int (*SIMBA2_WriteIO_Bin)(char *name, long value);
typedef int (*SIMBA2_WriteIO_Double)(char *name, double value);
typedef int (*SIMBA2_WriteIO_Unit)(char *name, char *value);

typedef int (*SIMBA2_SaveProcessIOFile)(char *PathName);
typedef int (*SIMBA2_ReadStringConfiguration)(char *configurationstring, int maxlen, int first);

typedef int (*SIMBA2_GetRecentProjectPath)(int index, char *path);


typedef int (*SIMBA2_ReadRecordDataExt)(int hwindex, int dev, int slot, int sub, int index, char* data, int *maxlen);



class SimulationUnit : public QObject
{
    Q_OBJECT
public:
    explicit SimulationUnit(QObject *parent = nullptr);  
    ~SimulationUnit();

private:
    QLibrary* lib;
    QMetaEnum metaEnum;

    QStringList hardwareData;


private:

    void loadFunctions();
    void test();

    void readHardware();


public:
    char * qstrToChar(QString);
    void loadLibrary(QString);
    void runSimProject(QString path, bool download);


    void readRecordData(int hwindex, int dev, int slot, int sub, int index);
    QString readIO(QString);
    void writeIO(QString, QString);

public:
    SIMBA2_OpenProjectFile          SIMBA_OpenProjectFile   ;
    SIMBA2_CheckProjectState        SIMBA_CheckProjectState ;
    SIMBA2_CloseProjectFile         SIMBA_CloseProjectFile  ;

    SIMBA2_ConnectAll	            SIMBA_ConnectAll	      ;
    SIMBA2_ConnectAllEx	            SIMBA_ConnectAllEx	  ;
    SIMBA2_IsConnected	            SIMBA_IsConnected	      ;
    SIMBA2_DisconnectAll            SIMBA_DisconnectAll     ;

    SIMBA2_DownloadAll              SIMBA_DownloadAll       ;
    SIMBA2_GetDownloadStatus        SIMBA_GetDownloadStatus ;

    SIMBA2_ReadIO		            SIMBA_ReadIO		      ;
    SIMBA2_ReadIO_Bin	            SIMBA_ReadIO_Bin	      ;
    SIMBA2_ReadIO_Double            SIMBA_ReadIO_Double     ;
    SIMBA2_ReadIO_Unit	            SIMBA_ReadIO_Unit	      ;

    SIMBA2_WriteIO                  SIMBA_WriteIO           ;
    SIMBA2_WriteIO_Bin              SIMBA_WriteIO_Bin       ;
    SIMBA2_WriteIO_Double           SIMBA_WriteIO_Double    ;
    SIMBA2_WriteIO_Unit             SIMBA_WriteIO_Unit      ;

    SIMBA2_SaveProcessIOFile        SIMBA_SaveProcessIOFile;
    SIMBA2_ReadStringConfiguration  SIMBA_ReadStringConfiguration;

    SIMBA2_GetRecentProjectPath     SIMBA_GetRecentProjectPath;

    SIMBA2_ReadRecordDataExt        SIMBA_ReadRecordDataExt;

    enum SIMBA2_RETURN_CODES{
       SIMBA_QUIT_POS               =  0, // O.K.
       SIMBA_QUIT_NEG               = -1, // Negative acknowledgment, unspecified error
       SIMBA_PARAMETER_INVALID      = -2, // Wrong call parameter (syntax or value not available)
       SIMBA_NOT_SUPPORTED          = -3, // The function is not supported by the current delivery status
       SIMBA_WRONG_SIMBATYPE        = -4, // Function is not supported by the SIMULATIONUnit
       SIMBA_SYS_DRIVER_CLOSED      = -5, // Hardware driver was already closed
       SIMBA_THREAD_NOT_STARTED     = -6, // Task thread cannot be launched (WINDOWS problem)
       SIMBA_CHANNEL_LOCKED         = -7, // No access as reserved by another process.
       SIMBA_MULTI_ACCESS_ERROR     = -8, // Simultaneous access of different applications has caused a WINDOWS error
       SIMBA_MAINPROG_NOT_RUNNING   = -9, // SIMULATIONUnit was not started
       SIMBA_BUSY                   = -10,// SIMULATIONUnit is utilized to full capacity, job is taking too long
       SIMBA_HARDWARE_NO_ACCESS     = -11,// No access to hardware, hardware index is not present in project
       SIMBA_FUNCTION_TIMEOUT       = -12,// Timeout
       SIMBA_QUIT_NOT_CONNECTED     = -20,// Module not connected
       SIMBA_WRONG_FIRMWARE         = -23,// Wrong firmware version used in the module
       SIMBA_QUIT_FULL_BUFF         = -29,// Request buffer is full
       SIMBA_REQUEST_TIME_OUT       = -30,// SIMULATIONUnit does not respond
       SIMBA_DRIVER_ERROR           = -40,// SIMULATIONUnit driver not available or not working
       SIMBA_MEM_ERROR              = -41,// Driver cannot allocate memory for I/O image
       SIMBA_PROJECT_FAIL           = -48,// SIMULATIONUnit cannot open project or project not available
       SIMBA_PROJECT_CLOSED         = -49,// No open project
    };
    Q_ENUM(SIMBA2_RETURN_CODES);



};

#endif // SIMULATIONUNIT_H
