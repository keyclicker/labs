#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "FileTree.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonOpen_clicked();

    void on_buttonClose_clicked();

    void on_treeWidget_itemSelectionChanged();

    void on_pushAddField_clicked();

    void on_pushDeleteField_clicked();

    void on_pushApply_clicked();

    void on_buttonManager_clicked();

    void on_buttonCreate_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    FileTree *ft;
    QTreeWidgetItem *topLevelItem;

};
#endif // MAINWINDOW_HPP
