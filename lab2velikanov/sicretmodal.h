#ifndef SICRETMODAL_H
#define SICRETMODAL_H
#include <QVariant>
#include <QObject>
#include <QList>
#include <QModelIndex>
#include <QAbstractListModel>
#include <QUrl>

class sicret
{
public:
    sicret(const QString &p_Img,
           const QString &p_Url,
           const QString &p_Login,
           const QString &p_Password);

    QString getImg() const;
    QString getURL() const;
    QString getLogin() const;
    QString getPassword() const;

private:
    QString m_img;
    QString m_url;
    QString m_login;
    QString m_password;
};


class sicretsModal : public QAbstractListModel{
    //  класс QAbstractListModel обеспечивает
    // 1 по мимо хранения элементов модели в Qlist также
    // 2 Трансляцию строковых запросов QML в адреса (свойств и методов) С++
    // 3 Интерактивность и обновление QML-связанных view в qml посредстровам спец сигнальной системы
    Q_OBJECT
public:
    //должно быть столько индетефикаторов сколько свойсвта модели обьекта
    //нельзя начинать с 0 только с UserRole 256
    //
    enum enmRoles {
        userImg = Qt::UserRole + 1,
        UserURL,//258
        userLogin,//259
        userPassword//260
    };
    sicretsModal(QObject *parent = nullptr);

    void addItem(const sicret & newItem);// добавление айтема

    int rowCount(const QModelIndex & parent = QModelIndex()) const; // необходим чтобы автоматом определляли кол во жлементов и строили разметку

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;//необходим для получения данных обьекта index соотв заданному с помощью role свойству элемента
    QVariantMap get(int idx) const;//для выгрузки i-элемента списка целиком со всеми свойствами

    void clear();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<sicret> m_items;

};
#endif // SICRETMODAL_H
