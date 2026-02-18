#include "mainwindow.h"
#include "filetreeview.h"
#include "filecreatedialog.h"
#include "./ui_mainwindow.h"

#include "QFileSystemModel"

#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter->setSizes({200, 1000});
    ui->splitter->setCollapsible(0, false);
    ui->splitter->setCollapsible(1, false);
    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);

    ui->treeView->setMinimumWidth(180);
    ui->treeView->setTextElideMode(Qt::ElideNone);
    ui->treeView->setIndentation(12);

    QFileSystemModel *model = new QFileSystemModel(this);

    // путь, который нужно показать
    QString path = "/home/igmunv/proj/test";

    model->setRootPath(path);

    model->setReadOnly(false);
    ui->treeView->setModel(model);

    // ограничиваем отображение только этой директории
    ui->treeView->setRootIndex(model->index(path));

    ui->treeView->setColumnHidden(1, true);
    ui->treeView->setColumnHidden(2, true);
    ui->treeView->setColumnHidden(3, true);
    ui->treeView->header()->hide();
    ui->treeView->setAnimated(true);


    ui->treeView->setEditTriggers(QAbstractItemView::EditKeyPressed);

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QTreeView::customContextMenuRequested,
            this, &MainWindow::onTreeContextMenu);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    auto *model = static_cast<QFileSystemModel*>(ui->treeView->model());
    if (model->isDir(index)) return;

    QMessageBox msgBox;     // диалоговое окно
    msgBox.setText("File Clicked!"); // устанавливаем текст
    msgBox.exec();  // отображаем диалоговое окно
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

}

void MainWindow::onTreeContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos); // индекс под курсором

    QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
    if (!model)
        return;

    QMenu menu(this);



    if (index.isValid()){

        QString path = model->filePath(index);
        bool isDir = model->isDir(index);  // <-- проверяем, директория ли

        if (isDir){
            menu.addAction("Open", [this, path]() {
                QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
                if (!model)
                    return;

                QModelIndex index = model->index(path);
                if (!index.isValid())
                    return;

                // Разворачиваем саму директорию
                ui->treeView->expand(index);

                // Прокручиваем и выделяем
                //ui->treeView->scrollTo(index);
                //ui->treeView->setCurrentIndex(index);
                //ui->treeView->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

            });

            menu.addAction("Rename", [this, path]() {
                QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
                if (!model)
                    return;

                QModelIndex index = model->index(path);
                if (!index.isValid())
                    return;

                // Включаем редактирование индекса
                ui->treeView->edit(index);
            });
            menu.addAction("Delete", [index]() {

            });
            menu.addSeparator();
            menu.addAction("Create File", [path,this]() {
                FileCreateDialog fcd(this,path);
                fcd.exec();

            });
            menu.addAction("Create Folder", [index]() {

            });
        }
        else{
            menu.addAction("Open", [this, path]() {

            });
            menu.addAction("Rename", [this, path]() {
                QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
                if (!model)
                    return;

                QModelIndex index = model->index(path);
                if (!index.isValid())
                    return;

                // Включаем редактирование индекса
                ui->treeView->edit(index);
            });
            menu.addAction("Delete", [index]() {

            });
        }

        // Показать меню в глобальных координатах

    }

    else{
        QString path = model->rootPath();
        menu.addAction("Create File", [path,this]() {
            FileCreateDialog fcd(this,path);
            fcd.exec();

        });
        menu.addAction("Create Folder", [index]() {

        });
    }
    menu.exec(ui->treeView->viewport()->mapToGlobal(pos));
}

