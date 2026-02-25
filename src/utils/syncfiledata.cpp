#include "syncfiledata.h"

SyncFileData::SyncFileData(QCodeEditor* codeeditor, QHexView* hexview) {
    m_codeeditor = codeeditor;
    m_hexview = hexview;
}


void SyncFileData::setBuffer(QByteArray buffer){
    m_buffer = buffer;
    is_mod = true;
}

void SyncFileData::syncBuffer(){
    QTextCursor cursor = m_codeeditor->textCursor();
    if (is_mod) {
        m_codeeditor->setPlainText(QString::fromUtf8(m_buffer));

        QTextCursor newCursor = m_codeeditor->textCursor();
        newCursor.setPosition(cursor.position());
        m_codeeditor->setTextCursor(newCursor);

        is_mod = false;
    }
}

QByteArray* SyncFileData::getBuffer(){
    return &m_buffer;
}

bool SyncFileData::getModified(){
    return is_mod;
}