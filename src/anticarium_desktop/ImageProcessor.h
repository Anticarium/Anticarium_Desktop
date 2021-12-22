#pragma once

#include <QPair>
#include <QThread>
#include <anticarium_desktop/RowBuilder.h>

// Purely static class
class ImageProcessor : public QObject {
    Q_OBJECT
  public:
    ImageProcessor(QObject* parent = nullptr);
    virtual ~ImageProcessor();
    void start();

  signals:
    void rowReadyEvent(const ImageRow&);

  public slots:
    void onImageRow(const QByteArray& data);

  private:
    int maxThreads = 0;
    int getNextThreadID();
    std::vector<QPair<QThread*, RowBuilder*>> buildersThreadsPairsList;
};
