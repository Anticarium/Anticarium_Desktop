#pragma once

#include <anticarium_desktop/UDPReader.h>
#include <anticarium_desktop/config/ImageRow.hpp>

class VideoManager : public QObject {
    Q_OBJECT
  public:
    VideoManager(QObject* parent = nullptr);

    void run();

  signals:
    void imageRowReadyEvent(const ImageRow& row);

  private slots:
    // Incoming udp data
    void onIncomingData(const QByteArray& data);

  private:
    UDPReader* udpReader = nullptr;
};
