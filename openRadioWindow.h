#ifndef OPENRADIOWINDOW_H
#define OPENRADIOWINDOW_H

#include <QtGui>

class RadioWindow : public QDialog
{
    Q_OBJECT

public:
    RadioWindow(QWidget* parent);
    QString text() const { return entry->text(); }

protected:
    QLineEdit *entry;

};

#endif // OPENRADIOWINDOW_H
