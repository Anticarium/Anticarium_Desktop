#pragma once

#include <QGraphicsScene>
#include <anticarium_desktop/UDPReader.h>
#include <anticarium_desktop/config/ImageRow.hpp>

class VideoManager : public QObject {
    Q_OBJECT
  public:
    VideoManager(QObject* parent = nullptr);

    void run();

    QGraphicsScene* getVideoScene() const;

  private slots:
    // Incoming udp data
    void onIncomingData(const QByteArray& data);

    void updateImageRow(const ImageRow& row);


  private:
    void initializeScene();

    UDPReader* udpReader       = nullptr;
    QGraphicsScene* videoScene = nullptr;
};
