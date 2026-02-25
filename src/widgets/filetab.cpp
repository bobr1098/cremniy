#include "filetab.h"
#include "tooltabwidget.h"
#include <qdir.h>
#include <qevent.h>

FileTab::FileTab(FilesTabWidget *fwparent, QString path)
    : QWidget{fwparent}
{
    filePath = path;
    parrentTabWidget = fwparent;
}


void FileTab::saveFile(){
    ToolTab* tooltabInner = this->findChild<ToolTab*>("toolTabWidget");
    if (!tooltabInner) return;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;
    tooltabInner->m_syncfiledata->syncBuffer();
    QByteArray* data = tooltabInner->m_syncfiledata->getBuffer();
    file.write(*data);
    file.close();
    parrentTabWidget->setTabText(parrentTabWidget->currentIndex(), QFileInfo(filePath).fileName());
}

void FileTab::fileModifyEvent(bool modified){
    ToolTab* tooltabInner = this->findChild<ToolTab*>("toolTabWidget");
    parrentTabWidget->setTabText(parrentTabWidget->currentIndex(), QFileInfo(filePath).fileName()+"*");
}