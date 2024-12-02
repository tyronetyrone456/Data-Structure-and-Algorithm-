#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonPush_clicked();
    void on_pushButtonPop_clicked();
    void on_pushButtonPeekStack_clicked();
    void on_pushButtonEnqueue_clicked();
    void on_pushButtonDequeue_clicked();
    void on_pushButtonPeekQueue_clicked();

private:
    Ui::MainWindow *ui;
    QStack<QString> bookStack;         // Stack to store returned books
    QQueue<QString> reservationQueue;  // Queue to manage book reservations

    void updateStackDisplay();
    void updateQueueDisplay();
};

#endif // MAINWINDOW_H
