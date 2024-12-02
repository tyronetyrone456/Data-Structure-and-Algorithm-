#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    updateStackDisplay();
    updateQueueDisplay();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonPush_clicked() {
    QString book = ui->bookInput->text();
    if (!book.isEmpty()) {
        bookStack.push(book);
        ui->bookInput->clear();
        updateStackDisplay();
        ui->statusLabel->setText("Book added to returned stack.");
    }
}

void MainWindow::on_pushButtonPop_clicked() {
    if (!bookStack.isEmpty()) {
        bookStack.pop();
        updateStackDisplay();
        ui->statusLabel->setText("Latest returned book removed.");
    } else {
        ui->statusLabel->setText("No books in stack to remove.");
    }
}

void MainWindow::on_pushButtonPeekStack_clicked() {
    if (!bookStack.isEmpty()) {
        ui->statusLabel->setText("Latest returned book: " + bookStack.top());
    } else {
        ui->statusLabel->setText("No books in stack.");
    }
}

void MainWindow::on_pushButtonEnqueue_clicked() {
    QString reservation = ui->reservationInput->text();
    if (!reservation.isEmpty()) {
        reservationQueue.enqueue(reservation);
        ui->reservationInput->clear();
        updateQueueDisplay();
        ui->statusLabel->setText("Book reserved.");
    }
}

void MainWindow::on_pushButtonDequeue_clicked() {
    if (!reservationQueue.isEmpty()) {
        QString servedReservation = reservationQueue.dequeue();
        updateQueueDisplay();
        ui->statusLabel->setText("Served reservation: " + servedReservation);
    } else {
        ui->statusLabel->setText("No reservations to serve.");
    }
}

void MainWindow::on_pushButtonPeekQueue_clicked() {
    if (!reservationQueue.isEmpty()) {
        ui->statusLabel->setText("Next reservation: " + reservationQueue.head());
    } else {
        ui->statusLabel->setText("No reservations in queue.");
    }
}

void MainWindow::updateStackDisplay() {
    ui->stackListWidget->clear();
    for (const QString &book : bookStack) {
        ui->stackListWidget->addItem(book);
    }
}

void MainWindow::updateQueueDisplay() {
    ui->queueListWidget->clear();
    for (const QString &reservation : reservationQueue) {
        ui->queueListWidget->addItem(reservation);
    }
}
