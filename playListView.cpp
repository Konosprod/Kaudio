#include "playListView.h"

playListView::playListView() : QWidget()
{
    QVBoxLayout *layout = new QVBoxLayout;
    modele = new QStringListModel(list);
    vue = new QListView ;
    vue->setModel(modele);
    vue->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(vue);
    setLayout(layout);
}

void playListView::setPlayList(QStringList& playlist)
{
    list = playlist;
    modele->setStringList(list);
    vue->setModel(modele);
}
