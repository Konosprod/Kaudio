#include "removeFromPlayListWindow.h"

RemovePlWindow::RemovePlWindow(QWidget* parent) : QDialog(parent)
{
    entry = new QSpinBox(this);
    entry->setMinimum(1);
    QLabel *label = new QLabel("Enter the index of the music");
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

