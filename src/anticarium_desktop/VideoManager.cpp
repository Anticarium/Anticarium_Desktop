#include <anticarium_desktop/RowBuilder.h>
#include <anticarium_desktop/VideoManager.h>
#include <anticarium_desktop/config/ApplicationSettings.h>

VideoManager::VideoManager(QObject* parent) : QObject(parent) {
    udpReader      = new UDPReader();
    imageProcessor = new ImageProcessor(this);

    udpReaderThread = new QThread(this);

    connect(udpReader, &UDPReader::dataReadEvent, imageProcessor, &ImageProcessor::onImageRow);
    connect(udpReaderThread, &QThread::started, udpReader, &UDPReader::run);
    connect(imageProcessor, &ImageProcessor::rowReadyEvent, this, &VideoManager::imageRowReadyEvent);
}

VideoManager::~VideoManager() {
    udpReaderThread->quit();
    udpReaderThread->wait();
}

void VideoManager::run() {
    udpReaderThread->start();
    imageProcessor->start();
}
