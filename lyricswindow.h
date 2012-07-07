#ifndef LYRICSWINDOW_H
#define LYRICSWINDOW_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class lyricsWindow;
}

class lyricsWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit lyricsWindow(QWidget *parent = 0, QString songName = "blah");
    ~lyricsWindow();

protected:
    void fillText(QString songName);
    
private:
    Ui::lyricsWindow *ui;
};

#endif // LYRICSWINDOW_H
