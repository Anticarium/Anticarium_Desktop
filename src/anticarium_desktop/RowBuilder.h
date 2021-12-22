#pragma once

#include <QObject>
#include <anticarium_desktop/config/ImageRow.hpp>

// Purely static class
class RowBuilder : public QObject {
    Q_OBJECT
  public:
    RowBuilder(QObject* parent = nullptr);

  signals:
    void rowReadyEvent(const ImageRow&);

  public slots:

    // Builds one image row
    void build(const QByteArray& row, int width);

  private:
    bool isRowOk(const ImageRow& row);
};
