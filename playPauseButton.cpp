#include "playPauseButton.h"

PlayPauseButton::PlayPauseButton() : QPushButton()
{
    this->setText("Play");
    this->setCheckable(true);

    connect(this, SIGNAL(toggled(bool)), this, SLOT(setPlayPause(bool)));
}

void PlayPauseButton::setPlayPause(bool checked)
{
    if(checked)
    {
        this->setText("Pause");
    }
    else
    {
        this->setText("Play");
    }
}
