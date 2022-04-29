#ifndef IMACRO_H
#define IMACRO_H

#include "variable.h"
#include <QList>


class IMacro{
public:
    IMacro(QList<Variable> _inputs, QList<Variable> _outputs) : inputs(_inputs), outputs(_outputs){};

public:
    virtual void process() = 0;

public:
    QList<Variable> inputs;
    QList<Variable> outputs;

};




#endif // IMACRO_H
