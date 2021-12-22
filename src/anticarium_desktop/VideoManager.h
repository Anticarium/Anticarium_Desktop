#pragma once

#include <QThread>
#include <anticarium_desktop/ImageProcessor.h>
#include <anticarium_desktop/UDPReader.h>
#include <anticarium_desktop/config/ImageRow.hpp>

class VideoManager : public QObject {
    Q_OBJECT
  public:
    VideoManager(QObject* parent = nullptr);
    virtual ~VideoManager();
    void run();

  signals:
    void imageRowReadyEvent(const ImageRow& row);

  private:
    UDPReader* udpReader           = nullptr;
    ImageProcessor* imageProcessor = nullptr;

    QThread* udpReaderThread = nullptr;
};
