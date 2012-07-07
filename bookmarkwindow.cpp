#include "bookmarkwindow.h"
#include "ui_bookmarkwindow.h"

bookMarkWindow::bookMarkWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookMarkWindow)
{
    ui->setupUi(this);
}

bookMarkWindow::~bookMarkWindow()
{
    delete ui;
}
