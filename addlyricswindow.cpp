#include "addlyricswindow.h"
#include "ui_addlyricswindow.h"

addLyricsWindow::addLyricsWindow(QWidget *parent, QString songName) :
    QDialog(parent),
    ui(new Ui::addLyricsWindow)
{
    ui->setupUi(this);
    a_songName = songName;
    connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveLyrics()));

}

void addLyricsWindow::cancel()
{
    this->destroy();
}

void addLyricsWindow::saveLyrics()
{
    QString filename(a_songName.remove(a_songName.lastIndexOf("."), a_songName.length()-a_songName.lastIndexOf(".")));

    QFile file(filename + ".lyrics");

    if(file.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&file);

        out << ui->textEdit->document()->toPlainText();
    }

    cancel();
}

addLyricsWindow::~addLyricsWindow()
{
    delete ui;
}
