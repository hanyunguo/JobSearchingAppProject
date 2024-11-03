#include "Page.h"
#include <QResizeEvent>

Page::Page(QWidget *parent)
    : QWidget(parent)
{
    // Constructor implementation (if needed)
}

// Provide a definition for the pure virtual destructor
Page::~Page()
{
    // Destructor implementation (even if empty)
}

void Page::resizeEvent(QResizeEvent *event)
{
    QSize newSize = event->size();

    // Example: Make the sidebar 25% of the width and main content 75%
    int sidebarWidth = newSize.width() * 0.4;
    int contentWidth = newSize.width() - sidebarWidth;
    int height = newSize.height();
    if(sidebar) {
        sidebar->setGeometry(0, 0, sidebarWidth, height);
    }//mainContent->setGeometry(0, 0, newSize.width(), height);
    // Call base class implementation if necessary
    QWidget::resizeEvent(event);
}
