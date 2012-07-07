#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QSystemTrayIcon>
#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>
#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/VideoWidget>
#include "playListView.h"
#include "playPauseButton.h"

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(int argc, char* argv[]);
    void fillPlayListArea();
    void setUpMenu();
    void setUpGUI();
    void setUpLayouts();
    void setUpConnexions();
    void addm3u(QString name);
    void addpls(QString name);
    void scanMusiqueDir(QString dir);
    void copyPlaylist(QString dir);
    bool clearDirectory(const QString &dirName);
    void copyFiles(QString dir);

public slots:
    void removeFromPlayList();
    void addToPlayList();
    void playPause(bool checked);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void mini();
    void showPlayList();
    void openRadio();
    void openFile();
    void playFile();
    void stopFile();
    void pauseFile();
    void nextFile();
    void prevFile();
    void playRadio();
    void setTimeMusic(qint64 timeMusique);
    void updateNextFile();
    void randomPlayDir();
    void randomizePlayList();
    void setCurrentMusic(int newCurrent);
    void setStatusBarMessage();
    void openDir();
    void savePlayList();
    void editBookMark();
    void exportPlaylist();
    void readLyrics();
    void addLyrics();

protected:
    /** Fonctionnement de base **/
    int current;
    Phonon::SeekSlider* slider;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::AudioOutput *output;
    Phonon::MediaObject *sound;
    /*Phonon::VideoWidget *videoWidget;*/
    QStringList playList;
    QLCDNumber *time;
    QLCDNumber *totalTime;
    QPushButton *open;
    QPushButton *stop;
    QPushButton *next;
    QPushButton *prev;
    QPushButton *showButton;
    QPushButton *repeatButton;
    playListView* plView;
    PlayPauseButton* playPauseButton;
    QStatusBar* statusBar;

    /** Menus **/
    QMenuBar *menubar;

    /** Menu Fichier **/
    QMenu* menuFile;
    QAction* menuOpenRadio;
    QAction* menuShuffleDir;
    QAction* menuOpenDir;
    QAction* menuOpenFile;
    QAction* menuMini;
    QMenu* menuPlayList;
    QAction* menuShufflePlaylist;
    QAction* menuSavePlayList;
    QAction* menuAddToPlayList;
    QAction* menuRemoveFromPlayList;
    QAction* menuExportPlayList;
    QMenu* menuSong;
    QAction* menuCreateLyrics;
    QAction* menuReadLyrics;
    QMenu* menuBookMark;
    QAction* menuEditBookMark;
    QSystemTrayIcon *sticon;
    QShortcut* sc;


};

#endif // MAINWINDOW_H
