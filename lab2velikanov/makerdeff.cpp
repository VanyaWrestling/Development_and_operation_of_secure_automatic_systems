#include "makerdeff.h"
#include "sicretmodal.h"
#include "aes.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QtWidgets/QApplication>
#include <QtGui/QClipboard>
#include <QDesktopServices>
#include <QJsonArray>
#include <QSaveFile>

makerDeff::makerDeff(QObject *QMLObject) : viewer(QMLObject)
{
    sicretsmodal = new sicretsModal();
}

bool makerDeff::parserFunc(QString pin, QString SearchStr){
    QFile file(":/asserts/pass.txt");
    if( file.open( QIODevice::ReadOnly ) )
    {
        QByteArray bytes = file.readAll();
        file.close();
        qDebug()<<bytes<<"Tyt bytes";

        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
        QString key(pin);
        QString iv(pin);
        QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
        QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
        QByteArray decodeText = encryption.decode(bytes, hashKey, hashIV);
        QByteArray decodedString = encryption.removePadding(decodeText);
        bytes = decodedString;
        qDebug() << bytes << "вывод";

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
            qDebug() << jsonError.errorString();
            return false;
        }
        else if(document.isObject())
        {
            QJsonObject main = document.object();
            QJsonValue first = main.value("records");
            QJsonArray last = first.toArray();

            if (sicretsmodal->rowCount() > 0) {
                sicretsmodal->clear();
            }
            for(int i = 0; i < last.count(); i++){
                QJsonObject list = last.at(i).toObject();
//                qDebug() << last;
                QString img = list.value("img").toString();
                QString urlka = list.value("url").toString();
//                qDebug() << url;
                QString login = list.value("login").toString();
                QString password = list.value("password").toString();
                if (urlka.contains(SearchStr))
                    sicretsmodal->addItem(sicret(img, urlka, login, password));
            }
        }
    }
    return true;
}

void makerDeff::copyToBufBarter(int index, QString param, QString pin){
    QString data = sicretsmodal->get(index).take(param).toString();
    QString data1 = sicretsmodal->get(index).take("strani4ka").toString();


    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString key(pin);
    QString iv(pin);
    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
//    QByteArray encodeText = encryption.encode(data.toLocal8Bit(), hashKey, hashIV);
    QByteArray decodeText = encryption.decode(data.toLocal8Bit(), hashKey, hashIV);
    QString decodedString = QString(encryption.removePadding(decodeText));

    QApplication::clipboard()->setText(decodedString);

//    QFile file1(":/asserts/kok1.txt");
//    file1.open(QIODevice::ReadOnly);
//    QByteArray bytes = file1.readAll();
//    file1.close();

//    QByteArray encodeText = encryption.encode(bytes, hashKey, hashIV);
//    QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);
//    QString decodedString = QString(encryption.removePadding(decodeText));
//    QFile file("D:\\project\\testkok.txt");
//    file.open(QIODevice::WriteOnly);
//    file.write(encodeText);
//    file.close();
}

void makerDeff::openUrl(){
   // QDesktopServices::openUrl(QUrl("https://google.com/"));
}
