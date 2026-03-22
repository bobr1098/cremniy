#ifndef HEXVIEWTAB_H
#define HEXVIEWTAB_H

#include "core/ToolTab.h"
#include <QWidget>
#include <qfileinfo.h>
#include <qstackedwidget.h>

class HexViewTab : public ToolTab
{
    Q_OBJECT

private:

    QStackedWidget* pageView;

public:
    explicit HexViewTab(QWidget *parent = nullptr);

    QString toolName() const override { return "HEX"; };
    QIcon toolIcon() const override { return QIcon(":/icons/hex.png"); };

public slots:

    // From Parrent Class: ToolTab
    void setFile(QString filepath) override;
    void setTabData() override;
    void saveTabData() override;

    void pageModifyDataSlot();

};

#endif // HEXVIEWTAB_H
