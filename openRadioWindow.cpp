#include "openRadioWindow.h"

RadioWindow::RadioWindow(QWidget* parent) : QDialog(parent)
{
    entry = new QLineEdit;
    QLabel *label = new QLabel("Enter the radio's URL");
    QPushButton *ok = new QPushButton("Ok");
    QPushButton *annul = new QPushButton("Cancel");
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;

    vbox->addWidget(label);
    vbox->addWidget(entry);
    hbox->addWidget(ok);
    hbox->addWidget(annul);
    vbox->addLayout(hbox);
    setLayout(vbox);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(annul, SIGNAL(clicked()), this, SLOT(close()));
}
