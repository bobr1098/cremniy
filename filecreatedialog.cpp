#include "filecreatedialog.h"

#include "QIODevice"
#include "QFile"

FileCreateDialog::FileCreateDialog(QWidget *parent, QString path): QDialog(parent) {

    this->dir_path = path;
    setWindowTitle("Create file");
    setFixedSize(300, 100); // маленькое окно

    QVBoxLayout *layout = new QVBoxLayout(this);

    // текстовое поле
    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Enter file name...");
    layout->addWidget(lineEdit);

    // кнопка
    QPushButton *button = new QPushButton("Create", this);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, &FileCreateDialog::onCreateClicked);
}

void FileCreateDialog::onCreateClicked() {
    QString fileName = lineEdit->text();
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter file name!");
        return;
    }

    // тут можно создать файл
    QString fullPath = QString("%1/%2").arg(dir_path).arg(fileName);
    QFile file(fullPath);
    if(file.open(QIODevice::WriteOnly)) {
        file.close();
        accept(); // закрыть диалог
    } else {
        QMessageBox::critical(this, "Error", "Failed to create file!");
    }
}