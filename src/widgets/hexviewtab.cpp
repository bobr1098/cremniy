#include "hexviewtab.h"
#include "verticaltabstyle.h"
#include <qapplication.h>
#include <qboxlayout.h>
#include <qstackedwidget.h>
#include <qtabwidget.h>
#include <QListWidget>
#include <QTableWidget>

HexViewTab::HexViewTab(QWidget *parent, QString path)
    : QWidget{parent}
{
    // main layout
    auto mainHexTabLayout = new QHBoxLayout(this);
    mainHexTabLayout->setSpacing(0);
    mainHexTabLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainHexTabLayout);

    // types tab widget
    QListWidget* tabsList = new QListWidget();
    tabsList->setObjectName("hexTabsList");
    tabsList->setFocusPolicy(Qt::NoFocus);
    QStackedWidget* tabView = new QStackedWidget();
    mainHexTabLayout->addWidget(tabView);
    mainHexTabLayout->addWidget(tabsList);

    // Tabs List
    tabsList->addItem("Raw");
    tabsList->addItem("ELF");
    tabsList->addItem("PE");
    tabsList->addItem("MBR");

    // RAW page
    auto pageRaw = new QWidget();
    auto pageRawLayout = new QVBoxLayout(pageRaw);
    pageRawLayout->setContentsMargins(0,0,0,0);
    m_hexViewWidget = new QHexView();
    pageRawLayout->addWidget(m_hexViewWidget);
    pageRaw->setLayout(pageRawLayout);
    tabView->addWidget(pageRaw);

    // ELF page
    auto pageELF = new QWidget();
    auto pageELFLayout = new QVBoxLayout(pageELF);
    pageELF->setLayout(pageELFLayout);
    tabView->addWidget(pageELF);

    // PE page
    auto pagePE = new QWidget();
    auto pagePELayout = new QVBoxLayout(pagePE);
    pagePE->setLayout(pagePELayout);
    tabView->addWidget(pagePE);

    // MBR page
    auto pageMBR = new QWidget();
    auto pageMBRLayout = new QVBoxLayout(pageMBR);
    pageMBR->setLayout(pageMBRLayout);
    tabView->addWidget(pageMBR);

    tabsList->setCurrentRow(0);
    // Connects

    connect(tabsList, &QListWidget::currentRowChanged,
                     tabView, &QStackedWidget::setCurrentIndex);

    connect(m_hexViewWidget->hexDocument(),
            &QHexDocument::dataChanged,
            this,
            [this](const QByteArray&, quint64, QHexChangeReason){
                emit modifyData(true);
            });
}
