#include "lyricswindow.h"
#include "ui_lyricswindow.h"

lyricsWindow::lyricsWindow(QWidget *parent, QString songName) :
    QDialog(parent),
    ui(new Ui::lyricsWindow)
{
    ui->setupUi(this);
    QFileInfo info(songName);
    ui->groupBox->setTitle(info.baseName() + ":");
    fillText(songName);

}

lyricsWindow::~lyricsWindow()
{
    delete ui;
}


void lyricsWindow::fillText(QString songName)
{

    QString filename(songName.remove(songName.lastIndexOf("."), songName.length()-songName.lastIndexOf(".")));

    QFile file(filename + ".lyrics");

    if(file.exists())
    {
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->textEdit->setText(file.readAll());
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "You must create the lyrics before !");
        this->destroy();
    }
}
