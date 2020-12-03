#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QFileDialog>
#include <QDebug>
#include <QLocale>
#include <QTableWidgetItem>
#include <QDesktopServices>
#include <QInputDialog>

#include "FileTree.hpp"
Q_DECLARE_METATYPE(FileTree*);


void drawTree(QTreeWidgetItem *head, FileTree *dir) {
    QTreeWidgetItem *item = new QTreeWidgetItem(head);
    item->setText(0, QString::fromStdString(dir->getName()));
    item->setText(1, QLocale().formattedDataSize(dir->getFileSize()));
    item->setText(2, QString::fromStdString(dir->getType()));
    item->setText(3, QString::fromStdString(dir->getMtime()));
    item->setData(4, Qt::UserRole, QVariant::fromValue(dir));

    item->setIcon(0, QFileIconProvider().
                  icon(QFileInfo(QString::fromStdString(dir->getPath()))));

    if (dir->getIsVirtual()) {
        item->setText(1, "None");
    }

    for (auto &a: dir->getForest()) {
        drawTree(item, a);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnWidth(0, 300);
    ui->treeWidget->setColumnWidth(2, 150);

    auto path = "/home/keyclicker/Documents/Labs/labs/Term3";
    ft = FileTree::Virtual("root");


    ft->addDir(path);

    topLevelItem = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(topLevelItem);

    topLevelItem->setText(0, QString::fromStdString(ft->getName()));
    topLevelItem->setData(4, Qt::UserRole, QVariant::fromValue(ft));
    drawTree(topLevelItem, ft->getForest().back());

    topLevelItem->setExpanded(true);
}

MainWindow::~MainWindow()
{
    delete ft;
    delete ui;
}


void MainWindow::on_buttonOpen_clicked(){
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.exec();

    QTreeWidgetItem *si;
    FileTree *ft;

    if (!ui->treeWidget->selectedItems().isEmpty() &&
            ui->treeWidget->selectedItems().back()->
            data(4, Qt::UserRole).value<FileTree*>()->getIsVirtual()) {

        si = ui->treeWidget->selectedItems().back();
        ft = si->data(4, Qt::UserRole).value<FileTree*>();
    }
    else {
        si = topLevelItem;
        ft = si->data(4, Qt::UserRole).value<FileTree*>();
    }

    drawTree(si, ft->addDir(dialog.directory().path().toStdString()));
    si->setExpanded(true);
}

void MainWindow::on_buttonClose_clicked()
{
    for (auto &a: ui->treeWidget->selectedItems()) {
        if (a != topLevelItem)
            delete a;
    }
}

void MainWindow::on_treeWidget_itemSelectionChanged()
{
    const auto fti = ui->treeWidget->selectedItems().back()->data(4, Qt::UserRole).value<FileTree*>();

    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(2);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->resizeSection(0, 125);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Property"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Value"));


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto setField = [this](auto row, auto field, auto value) {
        auto fwi = new QTableWidgetItem(field);
        auto vwi = new QTableWidgetItem(value);
        fwi->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);
        vwi->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);

        ui->tableWidget->setItem(row, 0, fwi);
        ui->tableWidget->setItem(row, 1, vwi);
    };

    setField(0, "Name", QString::fromStdString(fti->getName()));
    setField(1, "Item type", QString::fromStdString(fti->getType()));
    setField(2, "Folder path", QString::fromStdString(fti->getPath()));
    setField(3, "Date modified", QString::fromStdString(fti->getMtime()));
    setField(4, "Size", QLocale().formattedDataSize(fti->getFileSize()));

    if (fti->getIsVirtual()) {
        setField(4, "Size", "None");
    }

    for (auto a: fti->getMetadata()) {
        auto row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        auto fwi = new QTableWidgetItem(QString::fromStdString(a.first));
        auto vwi = new QTableWidgetItem(QString::fromStdString(a.second));
        fwi->setFlags(fwi->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        vwi->setFlags(vwi->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable);

        ui->tableWidget->setItem(row, 0, fwi);
        ui->tableWidget->setItem(row, 1, vwi);
    }


    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void MainWindow::on_pushAddField_clicked()
{
    auto row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    auto fwi = new QTableWidgetItem();
    auto vwi = new QTableWidgetItem();
    fwi->setFlags(fwi->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    vwi->setFlags(vwi->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    ui->tableWidget->setItem(row, 0, fwi);
    ui->tableWidget->setItem(row, 1, vwi);
}

void MainWindow::on_pushDeleteField_clicked()
{
    if (!ui->tableWidget->selectedItems().empty())
        ui->tableWidget->removeRow(ui->tableWidget->selectedItems().front()->row());
}

void MainWindow::on_pushApply_clicked()
{
    const auto fti = ui->treeWidget->selectedItems().back()->data(4, Qt::UserRole).value<FileTree*>();
    auto row = ui->tableWidget->rowCount();

    fti->clearFields();
    for (int i = 5; i < row; ++i) {
        if (!ui->tableWidget->item(i, 0)->text().isEmpty()) {
            fti->insertField(ui->tableWidget->item(i, 0)->text().toStdString(),
                             ui->tableWidget->item(i, 1)->text().toStdString());
        }
    }
}

void MainWindow::on_buttonManager_clicked()
{
    const auto fti = ui->treeWidget->selectedItems().back()->data(4, Qt::UserRole).value<FileTree*>();
    QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(fti->getPath())));
}

void MainWindow::on_buttonCreate_clicked()
{
    QTreeWidgetItem *si;
    FileTree *ft;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Creating virtual directory"),
                                         tr("Virtual directory name:"), QLineEdit::Normal,
                                         "Default Name", &ok);
    if (ok) {
        if (!ui->treeWidget->selectedItems().isEmpty() &&
                ui->treeWidget->selectedItems().back()->
                data(4, Qt::UserRole).value<FileTree*>()->getIsVirtual()) {

            si = ui->treeWidget->selectedItems().back();
            ft = si->data(4, Qt::UserRole).value<FileTree*>();
        }
        else {
            si = topLevelItem;
            ft = si->data(4, Qt::UserRole).value<FileTree*>();
        }

        drawTree(si, ft->addVirtualDir(text.toStdString()));
        si->setExpanded(true);
    }
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    auto ft = item->data(4, Qt::UserRole).value<FileTree*>();
    if (ft->getIsVirtual()) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Creating virtual directory"),
                                             tr("Virtual directory name:"), QLineEdit::Normal,
                                             item->text(0), &ok);
        if (ok) {
            ft->setName(text.toStdString());
            item->setText(0, text);
        }
        item->setExpanded(!item->isExpanded());
    }
}
