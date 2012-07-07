#ifndef REMOVEFROMPLAYLISTWINDOW_H
#define REMOVEFROMPLAYLISTWINDOW_H

#include <QtGui>

class RemovePlWindow : public QDialog
{
    Q_OBJECT

public:
    RemovePlWindow(QWidget* parent);
    QString text() const { return entry->text(); }

protected:
    QSpinBox *entry;

};

#endif // REMOVEFROMPLAYLISTWINDOW_H
