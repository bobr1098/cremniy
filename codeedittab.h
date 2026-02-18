#ifndef CODEEDITTAB_H
#define CODEEDITTAB_H

#include <QTabWidget>

class CodeEditTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit CodeEditTab(QWidget *parent = nullptr);
};

#endif