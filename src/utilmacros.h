#ifndef UTILMACROS_H
#define UTILMACROS_H
#include <QApplication>
#include <QDesktopWidget>


#ifdef WIDGET_CENTER
#define WIDGET_CENTRALIZE(widget) \
    QDesktopWidget *desktop = QApplication::desktop(); \
    widget->move((desktop->width()-widget->width())/2,(desktop->height()-widget->height())/2);
#else
#define WIDGET_CENTRALIZE(widget)
#endif

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#define SET_HEADER_CLICKABLE(table_ptr,h,flag) \
    if (#h == "horizontal") {table_ptr->horizontalHeader()->setClickable(flag);} \
    else { table_ptr->verticalHeader()->setClickable(flag);}
#else
#define SET_HEADER_CLICKABLE(table_ptr,h,flag) \
    if (#h == "horizontal"){table_ptr->horizontalHeader()->setSectionsClickable(flag);} \
    else {table_ptr->verticalHeader()->setSectionsClickable(flag);}
#endif


#endif // UTILMACROS_H
