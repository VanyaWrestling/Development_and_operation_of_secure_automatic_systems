#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "makerdeff.h"
#include "sicretmodal.h"
#include <QQmlContext>
#include <QCryptographicHash>
#include <Windows.h>
#include <iostream>
#include <intrin.h>
#include <QProcess>

typedef unsigned long long QWORD;
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);




//    // Проверка хэша
    QWORD moduleBase = (QWORD)GetModuleHandle(NULL);
    QWORD text_segment_start = moduleBase + 0x1000;


    PIMAGE_DOS_HEADER pIDH = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase);
    PIMAGE_NT_HEADERS pINH = reinterpret_cast<PIMAGE_NT_HEADERS>(moduleBase + pIDH->e_lfanew);
    QWORD size_of_text = pINH->OptionalHeader.SizeOfCode;

    QByteArray text_segment_contents = QByteArray((char*)text_segment_start, size_of_text);
    QByteArray current_hash = QCryptographicHash::hash(text_segment_contents, QCryptographicHash::Sha256);
    QByteArray current_hash_base64 = current_hash.toBase64();

    const QByteArray hash0_base64 = QByteArray("ywTg/Un99daqgFCmelJI02Npp6AZ0gbs+jAzZjLRIgc=");


    qDebug() << "text_segment_start= " << Qt::hex << text_segment_start;
    qDebug() << "size_of_text= " << size_of_text;
    qDebug() << "text_segment_contents= " << Qt::hex << text_segment_contents.first(100);
    qDebug() << "current_hash_base64= " << current_hash_base64;


    bool checkresult = (current_hash_base64==hash0_base64);
    qDebug() << "checkresult= " << checkresult;
    if(!checkresult) {
//        int result = QMessageBox::critical(nullptr, "Внимание!", "Приложение модифицированно!");
        qDebug() << "Внимание! Приложение модифицированно!";
        return -1;
    }

    //Блок защиты от отладки самоотладкой
//    QProcess *satelliteProcess = new QProcess();
//    int pid = QGuiApplication::applicationPid();
//    qDebug() << "pid = " << pid;
//    QStringList arguments = {QString::number(pid)};
//    qDebug() << "arguments = " << arguments;
//    satelliteProcess->start("DebugProtector.exe", arguments);
//    bool protectorStarted = satelliteProcess->waitForStarted(1000);
//    qDebug() << "protectorStarted = " << protectorStarted;

//    //Блок простейшего отладчика
    bool debuggerFound = IsDebuggerPresent();
    if(debuggerFound) {
        qDebug() << "Debugger found";
        std::cout << "Debugger found";
        return -1;
    }
    //

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlContext *context = engine.rootContext();
    QObject* rootObject = engine.rootObjects().isEmpty() ? NULL : engine.rootObjects().first();

    makerDeff makerDeff(rootObject);
    context->setContextProperty("makerDeff", &makerDeff);
    context->setContextProperty("sicretsmodal", makerDeff.sicretsmodal);

    return app.exec();
}
