#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QBitArray>
#include <QFile>
#include <QTextStream>

#define NDEBUG

void setBit(QImage &img, int index, bool val) {
    int pixelIndex = index / 3;

    int x = pixelIndex % img.width();
    int y = pixelIndex / img.width();

#ifndef NDEBUG
    if (y >= img.height())
        throw std::out_of_range("выходит за пределы картинки");
#endif

    //img.pixel returns #AARRGGBB
    switch (index % 3) {
    case 0:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x010000) | (val << 16));
    case 1:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x000100) | (val << 8));
    case 2:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x000001) | val);
    }
}

bool getBit(const QImage &img, int index) {
    int pixelIndex = index / 3;

    int x = pixelIndex % img.width();
    int y = pixelIndex / img.width();

#ifndef NDEBUG
    if (y >= img.height())
        throw std::out_of_range("индекс бита выходит за пределы картинки");
#endif

    //img.pixel returns #AARRGGBB
    switch (index % 3) {
    case 0:
        return (img.pixel(x, y) >> 16) & 1;
    case 1:
        return (img.pixel(x, y) >> 8) & 1;
    case 2:
        return img.pixel(x, y) & 1;
    }

    Q_UNREACHABLE();
}

QByteArray readBytes(const QImage& img, size_t begin, size_t length) {
    QByteArray byteArray;
    char buf = 0;

    size_t end = (begin + length) * 8;

#ifndef NDEBUG
    if (static_cast<size_t>(img.width() * img.height() * 3) <= end)
        throw std::out_of_range("попытка прочитать биты вне картинки");
#endif

    for (size_t i = begin * 8; i < end; ++i) {
        buf = (buf << 1) | getBit(img, i);

        if (i % 8 == 7) {
            byteArray.push_back(buf);
            buf = 0;
        }
    }

    return byteArray;
}

void writeBytes(QImage& img, size_t begin, QByteArray& byteArray) {
    size_t end = (begin + byteArray.size()) * 8;

#ifndef NDEBUG
    if (static_cast<size_t>(img.width() * img.height() * 3) <= end)
        throw std::out_of_range("попытка записать биты вне картинки");
#endif

    for (size_t i = begin * 8; i < end; ++i) {
        setBit(img, i, (byteArray[i / 8] >> (7 - i % 8)) & 1);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadImgButton, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(ui->saveImgButton, &QPushButton::clicked, this, &MainWindow::saveImage);

    connect(ui->encodeMsgButton, &QPushButton::clicked, this, &MainWindow::encodeText);
    connect(ui->decodeMsgButton, &QPushButton::clicked, this, &MainWindow::decodeText);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::messageChanged);

    ui->outputLabel->setWordWrap(true);

    imageCapacity = -1; // по-умолчанию размер картинки невалидный
    usedBytes = 0;

    imageLoaded = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    imageLoaded = false;

    QString filepath = QFileDialog::getOpenFileName(this, tr("Открыть картинку"), "", tr("Допустимые форматы (*.png)"));

    if (!img.load(filepath, "PNG")) {
        showMessage(tr("Изображение не загружено"));
        return;
    }
    img.convertTo(QImage::Format_ARGB32);

    // каждый пиксель может хранить информацию в 3х каналах RGB
    // часть размера картинки уйдёт на запись маркера и размера сообщения
    imageCapacity = img.width() * img.height() * 3 - marker.size() - messageInfoLength;

    showMessage(tr("Изображение успешно загружено"));
    imageLoaded = true;
}

void MainWindow::saveImage()
{
    if (!imageLoaded) {
        showMessage(tr("Изображение не загружено в программу!"));
        return;
    }

    QString filepath = QFileDialog::getSaveFileName(this, tr("Сохранить картинку"), "", tr("Допустимые форматы (*.png)"));

    if (img.save(filepath, "PNG")) {
        showMessage(tr("Изображение успешно сохранено в %1").arg(filepath));
    } else {
        showMessage(tr("Изображение не сохранено"));
    }
}

void MainWindow::encodeText()
{
    if (!imageLoaded) {
        showMessage(tr("Изображение не загружена в программу!"));
        return;
    }

    usedBytes = ui->plainTextEdit->toPlainText().toUtf8().size();

    if (imageCapacity < usedBytes) {
        showMessage(tr("Ошибка. Не достаточно места!"));
        return;
    }

    QByteArray byteArray;
    byteArray.push_back(marker);
    for (int i = messageInfoLength - 1; i >= 0; --i) {
        byteArray.push_back((usedBytes >> i*8) & 0xff);
    }
    byteArray.push_back(ui->plainTextEdit->toPlainText().toUtf8());

    writeBytes(img, 0, byteArray);

    showMessage(tr("Сообщение добавлено в картинку!"));
}

void MainWindow::decodeText()
{
    if (!imageLoaded) {
        showMessage(tr("Изображение не загружена в программу!"));
        return;
    }

    int headerSize = marker.size() + messageInfoLength;
    QByteArray byteArray;

    byteArray = readBytes(img, 0, headerSize);

    for (size_t i = 0; i < marker.size(); ++i) {
        if (marker[i] != byteArray[i]) {
            showMessage(tr("Сообщение не обнаружено"));
            return;
        }
    }

    size_t messageSize = 0;
    for (size_t i = marker.size(); i < marker.size() + messageInfoLength; ++i) {
        messageSize = (messageSize << 8) + static_cast<unsigned char>(byteArray[i]);
    }

    if (messageSize > imageCapacity) {
        // showMessage(tr("Сообщение не обнаружено"));
        showMessage(tr("Ошибка. Размер сообщения в заголовке превышает размер изображения"));
        return;
    }

    byteArray = readBytes(img, headerSize, messageSize);

    QString text = QString::fromUtf8(byteArray);

    ui->plainTextEdit->setPlainText(text);

    showMessage(tr("Присутствует сообщение длиной %1 байт").arg(messageSize));
}

void MainWindow::messageChanged()
{
    if (imageCapacity < 0) return;
    usedBytes = ui->plainTextEdit->toPlainText().toUtf8().size();

    if (imageCapacity < usedBytes) {
        showMessage(tr("Размер сообщения превышен на: %1 байт").arg(usedBytes - imageCapacity));
    } else {
        showMessage(tr("Ещё можно ввести: %1 байт").arg(imageCapacity - usedBytes));
    }
}

void MainWindow::showMessage(QString msg)
{
    ui->outputLabel->setText(msg);
}

