#pragma once

#include <QObject>
#include <anticarium_desktop/Jttp.h>
#include <shared_types/SavedRegimes.h>

class DisplayRegimesManager : public QObject {
    Q_OBJECT
  public:
    enum {
        DELETION_START = 100 // If id number is even or bigger than 100, delete cocrresponding regime
    };

    DisplayRegimesManager(QObject* parent = nullptr);

    // Requests SavedRegimes from server
    void initialize();

    // Sends an id of element to delete
    void deleteRegime(int id);

    shared_types::Regime getRegimeAt(int index);
  signals:
    void displayDataEvent(const shared_types::SavedRegimes& newSavedRegimes);
    void requestDataEvent(JTTP::REQUEST_DATA requestData);
    void sendDataEvent(const shared_types::RegimeId& regimeId);

  public slots:
    // Stores incoming SavedRegimes data
    void onDataReceived(const shared_types::SavedRegimes& savedRegimes);

  private:
    shared_types::SavedRegimes savedRegimes;
};
