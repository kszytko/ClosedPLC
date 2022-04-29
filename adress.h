#ifndef ADRESS_H
#define ADRESS_H

#include <QString>

enum class  REG_TYPE{
    BOOL = 1,
    BYTE = 8,
    WORD = 16,
    DWORD = 32
};

enum class DIR_TYPE{
    INPUT,
    OUTPUT,
    INPUT_OUTPUT
};

struct Adress{
    QString fullAdress;
    REG_TYPE adrrType;
    DIR_TYPE regType;

    int parsedAdress;


    Adress(QString _fullAdress) : fullAdress(_fullAdress){
        //parser for adrType
        //parser for dirType
    }

    Adress(){
    }


};


#endif // ADRESS_H
