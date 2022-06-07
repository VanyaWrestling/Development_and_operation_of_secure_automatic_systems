#ifndef MAKERDEFF_H
#define MAKERDEFF_H

#include <QObject>
#include "sicretmodal.h"

class makerDeff: public QObject
{
    Q_OBJECT
public:
    explicit makerDeff(QObject *parent = nullptr);
    sicretsModal *sicretsmodal;

public slots:
    bool parserFunc(QString pin, QString SearchStr);
    void copyToBufBarter(int index, QString param, QString pin);
    void openUrl();

protected:
    QObject *viewer;
};

#endif // MAKERDEFF_H
