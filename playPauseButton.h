#ifndef PLAYPAUSEBUTTON_H
#define PLAYPAUSEBUTTON_H

#include <QtGui>

class PlayPauseButton: public QPushButton
{
    Q_OBJECT

public:
    PlayPauseButton();

public slots:
    void setPlayPause(bool checked);

protected:

};

#endif // PLAYPAUSEBUTTON_H
