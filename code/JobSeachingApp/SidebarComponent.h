#ifndef SIDEBARCOMPONENT_H
#define SIDEBARCOMPONENT_H

#include <QWidget>

class SidebarComponent : public QWidget
{
    Q_OBJECT

public:
    explicit SidebarComponent(QWidget *parent = nullptr);
    virtual ~SidebarComponent();

    // Virtual method to set up the sidebar
    virtual void setupSidebar() = 0;

signals:
    void navigationRequested(const QString &pageName);
};

#endif // SIDEBARCOMPONENT_H
