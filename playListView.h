#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QtGui>

class playListView : public QWidget
{
    Q_OBJECT

public:
    playListView();
    void setPlayList(QStringList& playlist);

public slots:
    void setIndex(QModelIndex index);

signals:
    void selectedChanged(int newIndex);

protected:
    QListView *vue;
    QStringListModel *modele;
    QStringList list;

};

#endif // PLAYLISTVIEW_H
