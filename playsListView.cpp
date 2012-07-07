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

    connect(vue, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(setIndex(QModelIndex)));

}

void playListView::setPlayList(QStringList& playlist)
{
    list = playlist;
    modele->setStringList(list);
    vue->setModel(modele);
}

void playListView::setIndex(QModelIndex index)
{
    emit selectedChanged(index.row());
}
