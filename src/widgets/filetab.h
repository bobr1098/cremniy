#ifndef FILETAB_H
#define FILETAB_H

#include "filestabwidget.h"
#include <QWidget>

class FileTab : public QWidget
{
    Q_OBJECT
public:
    QString filePath;
    FilesTabWidget* parrentTabWidget;
    explicit FileTab(FilesTabWidget *fwparent, QString path);
    void saveFile();



public slots:
    void fileModifyEvent(bool modified);
};

#endif // FILETAB_H
