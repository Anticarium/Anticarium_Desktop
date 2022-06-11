#include <QTimer>
#include <anticarium_desktop/widgets/RequestWaiter.h>

RequestWaiter::RequestWaiter(QWidget* parent) : QProgressBar(parent) {
    timer = new QTimer(this);
    timer->setInterval(tickInterval);
    setRange(minValue, maxValue);
    setTextVisible(false);

    connect(timer, &QTimer::timeout, this, &RequestWaiter::tick);
}

void RequestWaiter::onDataRequested() {
    requestCounter++;
    if (requestCounter > 0) {
        timer->start();
        currentValue = minValue;
        tick();
        show();
    }
}

void RequestWaiter::onAnswerReceived() {
    requestCounter--;
    if (requestCounter <= 0) {
        // in case of some error
        requestCounter = 0;

        timer->stop();
        hide();
    }
}

void RequestWaiter::tick() {
    currentValue++;
    if (currentValue > maxValue) {
        currentValue = minValue;
    }
    setValue(currentValue);
}
