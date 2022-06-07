#include "sicretmodal.h"
#include <QMap>
#include <QDebug>


sicret::sicret(const QString &getImg, const QString &getURL,
const QString &getLogin, const QString &getPassword)
    :   m_img(getImg),
        m_url(getURL),
        m_login(getLogin),
        m_password(getPassword)
{
 //
}

sicretsModal::sicretsModal(QObject *parent) : QAbstractListModel(parent)
{
    //пусто
}

QString sicret::getImg() const{ // функция для получения имени друга
    return m_img;
}

QString sicret::getURL() const{ // функция для получения фамилии друга
    return m_url;
}

QString sicret::getLogin() const{ // функция для получения фото друга
    return m_login;
}

QString sicret::getPassword() const{ // функция для получения id друга
    return m_password;
}

void sicretsModal::addItem(const sicret & newItem){
    // не изменяется
  // благодаря beginInsertRows() и endInsertRows() QML реагирует на изменения модели
    //ЧАСТЬ сигнальной системы уведомлений qml об изменениях модели и переде  в qml на какую позицию и сколько элементов вставляется
    beginInsertRows(QModelIndex(), //по умолчанию
                    rowCount(), //номер строки вставки
                    rowCount());// номер строки концу вставляемого участка
    m_items << newItem;// вставка нового элемента данных
    // сообзает listview о том что изменение модели закончено и можно обновить
    endInsertRows();
}

int sicretsModal::rowCount(const QModelIndex &parent) const
{
    // не изменяется
   // метод используется ListView в QML для определения числа элементов
    Q_UNUSED(parent); // макрос который скрыввает сообзение qt о тоом что параметр не использется
    return m_items.count(); //возвращает кол во элементов в списке
}

QVariant sicretsModal::data(const QModelIndex & index,
                                int role) const
{
     // метод используется в QML для получения значения одного поля под обозначением role одного элемента модели index
    //проверка на поппадание в список
    if (index.row() < 0 || (index.row() >= m_items.count()))
        return QVariant();//обертка

  //получение ссылки на обьект с нужным индексом
    const sicret&itemToReturn = m_items[index.row()];
    //получение значения нужного поля выбранного обьекта
    if (role == userImg)
    return itemToReturn.getImg(); //при любом return этой функции значение преобразуется в QVariant
    else if (role == UserURL)
    return itemToReturn.getURL();
    else if (role == userLogin)
    return itemToReturn.getLogin();
    else if (role == userPassword)
    return itemToReturn.getPassword();

    return QVariant();
}

QHash<int, QByteArray> sicretsModal::roleNames() const
{
    // метод используется в QML для сопоставления полей данных со строковыми названиями
     // TODO сопоставить полям данных строковые имена
    //метод отвечает за конвертацию за заполнение словаря "стрококвое_имя":роль
    QHash<int, QByteArray> roles;//обьяляется хэш таблица

    roles[userImg] = "img"; // строка будет в таком виде выхываться в qml
    roles[UserURL] = "urlka";
    roles[userLogin] = "login";//
    roles[userPassword] = "password";//
    return roles;
}

QVariantMap sicretsModal::get(int idx) const
{
    // не изменяется
    // метод используется ListView в QML для получения значений полей idx-го элемента модели
    //формирует выгрузку всех полей элемента списка под номером idx
    //QVariantMap {"роль":"значение"}
    QVariantMap map; //словарь
    foreach(int k, roleNames().keys())
    {
        map[roleNames().value(k)] = data(index(idx, 0), k);//выгружаются данные  слвать
    }
    return map;//
}

void sicretsModal::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);//аналагичнов в additem
    m_items.clear();//сообственно удаление элементов списка
    endRemoveRows();
}






