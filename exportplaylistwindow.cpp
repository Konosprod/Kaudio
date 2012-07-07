#include "exportplaylistwindow.h"
#include "ui_exportplaylistwindow.h"

exportPlaylistWindow::exportPlaylistWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportPlaylistWindow)
{
    ui->setupUi(this);
}

exportPlaylistWindow::~exportPlaylistWindow()
{
    delete ui;
}

bool exportPlaylistWindow::checked()
{
    return ui->RemoveOrNot->isChecked();
}
