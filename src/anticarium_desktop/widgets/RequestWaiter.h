#pragma once
#include <QProgressBar>

class RequestWaiter : public QProgressBar {
    Q_OBJECT
  public:
    RequestWaiter(QWidget* parent = nullptr);

  public slots:
    void onDataRequested();
    void onAnswerReceived();

  private slots:
    void tick();

  private:
    const int tickInterval = 400;

    int requestCounter = 0;

    const int maxValue = 3;
    const int minValue = 0;
    int currentValue   = minValue;

    QTimer* timer = nullptr;
};
