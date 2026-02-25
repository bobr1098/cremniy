#ifndef SYNCFILEDATA_H
#define SYNCFILEDATA_H

#include "QCodeEditor.hpp"
#include "QHexView/qhexview.h"

class SyncFileData
{

public:
    SyncFileData(QCodeEditor* codeeditor, QHexView* hexview);

    void setCodeEditor(QCodeEditor codeeditor);
    void setHexView(QHexView hexview);

    void setBuffer(QByteArray buffer);
    void syncBuffer();
    QByteArray* getBuffer();

    bool getModified();

private:

    QCodeEditor* m_codeeditor;
    QHexView* m_hexview;

    QByteArray m_buffer;

    bool is_mod = false;

};



#endif // SYNCFILEDATA_H
