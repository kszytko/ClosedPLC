#ifndef VARIABLE_H
#define VARIABLE_H

#include <QString>
#include "adress.h"

enum class VAR_TYPE{
    BOOL,
    BYTE,
    CHAR,
    INT,
    FLOAT
};

class Variable{
public:
    Variable(){}
    Variable(QString _name, Adress* _adress, VAR_TYPE _varType): name(_name), adress(_adress), varType(_varType){};

public:
    QString name;
    Adress* adress;
    VAR_TYPE varType;

    int value;
};

#endif // VARIABLE_H
