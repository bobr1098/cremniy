#include "tooltabwidget.h"
#include "QHexView/model/buffer/qmemorybuffer.h"
#include "QHexView/qhexview.h"
#include "filetab.h"
#include <QCodeEditor.hpp>
#include <QFile>
#include <QSyntaxStyle.hpp>

#include <QCodeEditor.hpp>
#include <QCECompleter.hpp>
#include <QSyntaxStyle.hpp>
#include <QCXXHighlighter.hpp>
#include <QJSONHighlighter.hpp>
#include <qboxlayout.h>
#include <qfileinfo.h>

ToolTab::ToolTab(FileTab *fwparent, QString path) :
    m_codeEditor(nullptr),
    m_completers(),
    m_highlighters(),
    m_styles()
    {


    m_completers["c"] = new QCECompleter(":/languages/python.xml");
    m_completers["cpp"] = new QCECompleter(":/languages/python.xml");
    m_completers["asm"] = new QCECompleter(":/languages/python.xml");

    m_highlighters["c"] = new QCXXHighlighter;
    m_highlighters["cpp"] = new QCXXHighlighter;
    m_highlighters["asm"] = new QCXXHighlighter;

    m_styles["default"] = QSyntaxStyle::defaultStyle();

        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) return;
        QByteArray data = file.readAll(); // читаем все байты
        file.close();
        auto text = QString::fromUtf8(data); // преобразуем в QString

        QFileInfo fileInfo(path);
        QString ext = fileInfo.suffix();

        QWidget *emptyWidget2 = new QWidget();

        QHexDocument* document = QHexDocument::fromMemory<QMemoryBuffer>(data, nullptr);

        QWidget *hextabwidget = new QWidget(this);
        hextabwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QHexView* hexview = new QHexView(hextabwidget);
        hexview->setDocument(document);
        auto layout = new QVBoxLayout(hextabwidget);
        layout->addWidget(hexview);
        hextabwidget->setLayout(layout);

        qDebug() << document->read(0, document->length());

        QIcon codeIcon(":/icons/code.png");
        QIcon hexIcon(":/icons/hex.png");
        QIcon disasmIcon(":/icons/dasm.png");

        m_codeEditor = new QCodeEditor(this);

        m_syncfiledata = new SyncFileData(m_codeEditor, hexview);
        m_syncfiledata->setBuffer(data);
        m_syncfiledata->syncBuffer();

        connect(document, &QHexDocument::dataChanged, this, [=](){ m_syncfiledata->setBuffer(document->read(0, document->length())); });

        // CodeEditor
        m_codeEditor->setSyntaxStyle(m_styles["default"]);
        m_codeEditor->setCompleter  (m_completers[ext]);
        m_codeEditor->setHighlighter(m_highlighters[ext]);

        this->addTab(m_codeEditor, codeIcon, "Code");
        this->addTab(hextabwidget, hexIcon, "Hex");
        this->addTab(emptyWidget2, disasmIcon, "Disassembler");

        connect(this, &QTabWidget::currentChanged, this, [=](int index){
            qDebug() << "curr tab change:" << index;
            m_syncfiledata->syncBuffer();
        });

}

QCodeEditor* ToolTab::get_codeEditor(){
    return m_codeEditor;
}

void ToolTab::loadStyle(QString path, QString name)
{
    QFile fl(path);

    if (!fl.open(QIODevice::ReadOnly))
    {
        return;
    }

    auto style = new QSyntaxStyle(this);

    if (!style->load(fl.readAll()))
    {
        delete style;
        return;
    }

    m_styles[name] = style;
}
