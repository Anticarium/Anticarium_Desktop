#ifndef MAINWINDOWMANAGER_H
#define MAINWINDOWMANAGER_H

#include <QObject>
#include <shared_types/Control.h>
#include <shared_types/SensorData.h>
#include <shared_types/TerrariumData.h>

class MainWindowManager : public QObject {
    Q_OBJECT
  public:
    MainWindowManager(QObject* parent = nullptr);
    // updates displayed values
    void sendControlData(const shared_types::Control& control);
    const shared_types::Control& getData() const;

  signals:
    void updateEvent(const shared_types::Control& control);
};

#endif // MAINWINDOWMANAGER_H
