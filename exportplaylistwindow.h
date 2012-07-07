#ifndef EXPORTPLAYLISTWINDOW_H
#define EXPORTPLAYLISTWINDOW_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class exportPlaylistWindow;
}

class exportPlaylistWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::exportPlaylistWindow *ui;

public:
    explicit exportPlaylistWindow(QWidget *parent = 0);
    ~exportPlaylistWindow();
    bool checked ();

};

#endif // EXPORTPLAYLISTWINDOW_H
