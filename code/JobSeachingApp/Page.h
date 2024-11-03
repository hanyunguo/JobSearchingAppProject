#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <SidebarComponent.h>

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = nullptr);
    virtual ~Page();

    // Pure virtual function to set up the page UI
    virtual void setupPage() = 0;
protected:
    SidebarComponent *sidebar;
    QWidget *mainContent;
    void resizeEvent(QResizeEvent *event) override;
signals:
    // Signal emitted when a page change is requested
    void changePageRequested(const QString &pageName);
};

#endif // PAGE_H
