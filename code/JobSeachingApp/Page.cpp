#include "Page.h"
#include <QResizeEvent>

Page::Page(QWidget *parent)
    : QWidget(parent)
{
    // Constructor implementation (if needed)
    setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px;");
    this->setMinimumSize(600, 600);
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
    }
    QWidget::resizeEvent(event);
}
