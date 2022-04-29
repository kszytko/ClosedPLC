#ifndef TESTMACRO1_H
#define TESTMACRO1_H

#include "IMacro.h"

class TestMacro1 : public IMacro
{
public:
    TestMacro1(QList<Variable> _inputs, QList<Variable> _outputs) : IMacro(_inputs, _outputs){
        input1 = _inputs[0];
        input2 = _inputs[1];

        output1 = _outputs[0];
    }

    // IMacro interface
public:
    void process(){
        output1.value = input1.value * input2.value;
    };


private:
    Variable input1, input2;
    Variable output1;
};

#endif // TESTMACRO1_H
