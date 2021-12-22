#include <anticarium_desktop/ImageProcessor.h>
#include <anticarium_desktop/config/ApplicationSettings.h>

ImageProcessor::ImageProcessor(QObject* parent) : QObject(parent) {
    auto settings = ApplicationSettings::instance();
    maxThreads    = settings->getImageProcessingThreads();

    // Create thread and processing pairs
    for (int i = 0; i < maxThreads; i++) {
        QThread* thread     = new QThread(this);
        RowBuilder* builder = new RowBuilder();

        builder->moveToThread(thread);

        QPair<QThread*, RowBuilder*> pair;
        pair.first  = thread;
        pair.second = builder;

        buildersThreadsPairsList.push_back(pair);

        connect(builder, &RowBuilder::rowReadyEvent, this, &ImageProcessor::rowReadyEvent);
    }
}

ImageProcessor::~ImageProcessor() {
    for (auto i : buildersThreadsPairsList) {
        i.first->quit();
        i.first->wait();
    }
}

void ImageProcessor::start() {
    for (auto i : buildersThreadsPairsList) {
        i.first->start();
    }
}

void ImageProcessor::onImageRow(const QByteArray& data) {
    auto settings  = ApplicationSettings::instance();
    int imageWidth = settings->getImageWidth();

    int threadId = getNextThreadID();
    auto builder = buildersThreadsPairsList[threadId].second;

    QMetaObject::invokeMethod(builder, "build", Qt::QueuedConnection, Q_ARG(QByteArray, data), Q_ARG(int, imageWidth));
}

int ImageProcessor::getNextThreadID() {
    static int nextThread = -1;

    nextThread++;
    if (nextThread == maxThreads) {
        nextThread = 0;
    }

    return nextThread;
}
