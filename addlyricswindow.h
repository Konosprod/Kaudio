#ifndef ADDLYRICSWINDOW_H
#define ADDLYRICSWINDOW_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class addLyricsWindow;
}

class addLyricsWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit addLyricsWindow(QWidget *parent = 0, QString songName = "blah");
    ~addLyricsWindow();
public slots:
    void saveLyrics();
    void cancel();
    
private:
    Ui::addLyricsWindow *ui;
    QString a_songName;
};

#endif // ADDLYRICSWINDOW_H
