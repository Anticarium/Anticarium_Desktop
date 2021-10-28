#pragma once

#include <QObject>
#include <anticarium_desktop/Jttp.h>
#include <shared_types/SavedRegimes.h>

class DisplayRegimesManager : public QObject {
    Q_OBJECT
  public:
    DisplayRegimesManager(QObject* parent = nullptr);

    // Requests SavedRegimes from server
    void initialize();

  signals:
    void displayDataEvent(const shared_types::SavedRegimes& newSavedRegimes);
    void requestDataEvent(JTTP::REQUEST_DATA requestData);
};
