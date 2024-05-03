#ifndef USBWORKER_H
#define USBWORKER_H

#include <QObject>
#include <string>
#include <QFileInfoList>
#include <QDir>
#include <QList>
#include <QThread>


class UsbWorker: public QObject
{
    Q_OBJECT
public:
    UsbWorker();

public slots:
    /// Возвращает с помощью слотов статус флешки
    void slot_wait();

private slots:
    /// Вспомогательный слот для slot_wait
    void work_wait();
signals:
    /// Сигнал означающий, что флешка найдена
    void signal_flashDriveFound(bool);

    /// Сигнал означающий, что данные готовы к чтению
    void signal_dataIsReady();
private:
    /// Возвращает true, если была найдена флешка.
    bool isTheFlashDrivePluggedIn();

    /// Возвращает true, если команда cmd выполнится без ошибок.
    bool runCmd(const std::string &cmd);

    /// Возвращает список папок и pdf-файлов на флешке в указаной директории
    /// (Если флешка не воткнута, то возвращает пустой список)
    QStringList getTheFileStructureOfTheDir(const QString& path);

    /// Обрабатывает текст с консоли для findThePathToTheMountedFlashDrive
    QString processCmdOutput(const QString& cmd_line);

    /// Обрабатывает текст с консоли для findThePathToTheMountedFlashDrive
    QString processCmdOutput1(const QString& cmd_line);

    /// Возвращает путь к флешке или пустую строку
    QStringList findThePathToTheMountedFlashDrive();

private:
    QThread *thread;
    bool flag;
};

#endif // USBWORKER_H
