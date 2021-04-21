#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <array>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void loadImage();
    void saveImage();
    void encodeText();
    void decodeText();
    void messageChanged();

private:
    void showMessage(QString msg);

    Ui::MainWindow *ui;
    QImage img;
    bool imageLoaded;
    size_t imageCapacity;
    size_t usedBytes;

    const std::array<char, 3> marker {
        static_cast<char>(0b11100010),
        static_cast<char>(0b10011101),
        static_cast<char>(0b10100100)
    };
    // количество байт, отводимых под размер спрятанного сообщения
    const size_t messageInfoLength = 4;
};
#endif // MAINWINDOW_HPP
