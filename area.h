#ifndef AREA_H
#define AREA_H

#pragma once

#include "adress.h"
#include <QString>
#include <QMap>


class Area
{
public:
    Area();

    QString name;
    int size;

    QMap<QString, Adress> range;



};

#endif // AREA_H


//POPULATE
/*
 * %I1000.5 = 10IR001_Name;
 * word 10IR001_Name2 = %QW1000;
 *
 *
 *
 *
 *
 *
 */
