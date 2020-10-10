#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                                               << "Пункт назначения"
                                               << "Номер рейса"
                                               << "ФИО"
                                               << "Дата");
    connect(ui->deleteRow, SIGNAL(clicked()), this, SLOT(handleDeleteRow()));
    connect(ui->addRow, SIGNAL(clicked()), this, SLOT(handleAddRow()));
    connect(ui->search, SIGNAL(clicked()), this, SLOT(handleSearch()));
    connect(ui->removeSearch, SIGNAL(clicked()), this, SLOT(handleRemoveSearch()));
}

void MainWindow::handleDeleteRow() {
    int num = ui->rowNumber->value();
    QMessageBox msgBox;
    if (num < 1 || num > ui->tableWidget->rowCount()) {
        msgBox.setText(QString("Неверный номер строки!"));
    } else {
        ui->tableWidget->removeRow(num - 1);
        msgBox.setText(QString("Вы удалили строку #") + QString::number(num));
    }
    msgBox.exec();
}

void MainWindow::handleAddRow() {
    int rowNum = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowNum);
    QTableWidgetItem *item0 = new QTableWidgetItem(ui->destination->text());
    ui->tableWidget->setItem(rowNum, 0, item0);
    QTableWidgetItem *item1 = new QTableWidgetItem(ui->flightNumber->text());
    ui->tableWidget->setItem(rowNum, 1, item1);
    QTableWidgetItem *item2 = new QTableWidgetItem(ui->name->text());
    ui->tableWidget->setItem(rowNum, 2, item2);
    QTableWidgetItem *item3 = new QTableWidgetItem(ui->date->text());
    ui->tableWidget->setItem(rowNum, 3, item3);
    ui->destination->setText("");
    ui->flightNumber->setText("");
    ui->name->setText("");

}

void MainWindow::handleSearch() {
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        if (ui->tableWidget->item(i, 1)->text() != ui->searchNumber->text() ||
                ui->tableWidget->item(i, 3)->text() != ui->searchDate->text()) {
            ui->tableWidget->hideRow(i);
        } else if (ui->tableWidget->isRowHidden(i)) {
            ui->tableWidget->showRow(i);
        }
    }
}

void MainWindow::handleRemoveSearch() {
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        if (ui->tableWidget->isRowHidden(i)) {
            ui->tableWidget->showRow(i);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

