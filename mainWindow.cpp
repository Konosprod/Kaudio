#include "mainWindow.h"
#include "openRadioWindow.h"
#include "playListView.h"
#include "playPauseButton.h"
#include "removeFromPlayListWindow.h"
#include "exportplaylistwindow.h"
#include "bookmarkwindow.h"
#include "lyricswindow.h"
#include "addlyricswindow.h"
#include <iostream>
#include <string>

/**
    lyrics         => New Window ?
 **/

Window::Window(int argc, char *argv[]) : QMainWindow()
{
    current = -1;
    stop = new QPushButton("Stop", this);
    open = new QPushButton("Open", this);
    next = new QPushButton("->", this);
    prev = new QPushButton("<-");
    showButton = new QPushButton("Show", this);
    time = new QLCDNumber;
    totalTime = new QLCDNumber;
    slider = new Phonon::SeekSlider(this);
    volumeSlider = new Phonon::VolumeSlider(this);
    output = new Phonon::AudioOutput(Phonon::VideoCategory, this);
    sound = new Phonon::MediaObject(this);
    sticon = new QSystemTrayIcon(QIcon(":ressources/icon"), this);
    plView = new playListView;
    repeatButton = new QPushButton("Repeat", this);
    playPauseButton = new PlayPauseButton();
    /*videoWidget = new Phonon::VideoWidget(this);
    Phonon::createPath(sound, videoWidget);*/
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);

    setUpGUI();
    setUpMenu();
    setUpLayouts();

    setUpConnexions();

    if(argc == 2)
    {
        current = -1;
        QString name(argv[1]);

        if((name.indexOf(".pls") == -1) && (name.indexOf(".m3u") == -1))
        {
            sound->setCurrentSource(name);
            this->playFile();
        }
        else
        {
            if(name.lastIndexOf(".pls") != -1)
            {
                addpls(name);
            }

            if(name.lastIndexOf(".m3u") != -1)
            {
                addm3u(name);
            }
        }
    }
    else if(argc >= 3)
    {
        for(int i = 1; i < argc; i++)
        {
            QString name(argv[i]);
            playList.append(name);
        }

        current = 0;
        sound->setCurrentSource(playList.at(current));
        this->playFile();
    }

}

void Window::setUpConnexions()
{
    connect(sound, SIGNAL(tick(qint64)), this, SLOT(setTimeMusic(qint64)));
    connect(open, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(stop, SIGNAL(clicked()), this, SLOT(stopFile()));
    connect(next, SIGNAL(clicked()), this, SLOT(nextFile()));
    connect(prev, SIGNAL(clicked()), this, SLOT(prevFile()));
    connect(sound, SIGNAL(finished()), this, SLOT(updateNextFile()));
    connect(sticon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    connect(showButton, SIGNAL(clicked()), this, SLOT(showPlayList()));
    connect(playPauseButton, SIGNAL(toggled(bool)), this, SLOT(playPause(bool)));
    connect(plView, SIGNAL(selectedChanged(int)), this, SLOT(setCurrentMusic(int)));
    connect(sound, SIGNAL(currentSourceChanged(Phonon::MediaSource)), this, SLOT(setStatusBarMessage()));
}

void Window::setCurrentMusic(int newCurrent)
{
    stopFile();
    current = newCurrent;
    sound->setCurrentSource(playList.at(current));
    playFile();
}

void shuffle(QStringList& list)
{
    int nbIter = qrand()%list.count() * list.size();

    for(int i = 0; i < nbIter; i++)
    {
        int begin = qrand() % list.count();
        int end = qrand() % list.count();
        while(begin == end)
        {
            end = qrand() % list.count();
        }
        list.swap(begin, end);
    }
}

void Window::randomPlayDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select a directory", "",
                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
            );

    if(dir.isEmpty())
    {
        return;
    }
    else
    {
        if(!playList.isEmpty())
        {
            playList.clear();
        }
        scanMusiqueDir(dir);
        if(playList.isEmpty())
        {
            return;
        }
        shuffle(playList);
        current = 0;
        sound->setCurrentSource(playList.at(current));
        if(plView->isVisible())
        {
            plView->setPlayList(playList);
        }
        this->playFile();
    }
}

void Window::updateNextFile()
{
    if(repeatButton->isChecked())
    {

        sound->stop();
        if(!playList.isEmpty())
        {
            sound->setCurrentSource(playList.at(current));
        }
        else
        {
            sound->setCurrentSource(sound->currentSource());
        }
        playFile();
    }
    else
    {
        nextFile();
    }
}

void Window::setStatusBarMessage()
{
    QString namemusic;
    QString number;
    if(!playList.isEmpty())
    {
        namemusic = playList.at(current).mid(playList.at(current).lastIndexOf('/'));
        namemusic.remove(0, 1);
        number.sprintf("%d/%d", current+1, playList.size());
        statusBar->showMessage("Current: " + namemusic + "  " + number, 0);

        if(this->isHidden())
        {
            sticon->showMessage("Current:",  namemusic + "  " + number, QSystemTrayIcon::Information, 3000);
        }
    }
}

void Window::setUpLayouts()
{
    QWidget* ecran = new QWidget();
    QVBoxLayout *vbox = new QVBoxLayout;
    QVBoxLayout *vbox1 = new QVBoxLayout;
    QVBoxLayout *vbox2 = new QVBoxLayout;
    QVBoxLayout *vbox3 = new QVBoxLayout;
    QVBoxLayout *vbox4 = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;
    QHBoxLayout *hbox1 = new QHBoxLayout;

    vbox4->addWidget(volumeSlider);
    vbox4->addWidget(repeatButton);
    vbox3->addWidget(stop);
    vbox3->addWidget(showButton);
    vbox1->addWidget(open);
    vbox1->addWidget(prev);
    vbox2->addWidget(playPauseButton);
    vbox2->addWidget(next);
    hbox1->addWidget(slider);
    hbox1->addWidget(time);
    hbox1->addWidget(totalTime);
    hbox->addLayout(vbox1);
    hbox->addLayout(vbox2);
    hbox->addLayout(vbox3);
    hbox->addLayout(vbox4);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox);
    vbox->addWidget(plView);
    /*vbox->addWidget(videoWidget);*/
    ecran->setLayout(vbox);
    this->setCentralWidget(ecran);
}

void Window::setUpGUI()
{
    time->display("00:00");
    totalTime->display("00:00");
    sound->setTickInterval(1000);
    slider->setMediaObject(sound);
    volumeSlider->setAudioOutput(output);
    stop->setEnabled(false);
    prev->setEnabled(false);
    next->setEnabled(false);
    playPauseButton->setEnabled(false);
    showButton->setEnabled(false);
    plView->hide();
    slider->setGeometry(0, 0, 200, 10);
    Phonon::createPath(sound, output);
    repeatButton->setCheckable(true);
}

void Window::addLyrics()
{
    addLyricsWindow* lwin = new addLyricsWindow(this, playList.at(current));
    lwin->exec();
}

void Window::readLyrics()
{
    lyricsWindow* lwin = new lyricsWindow(this, playList.at(current));
    lwin->exec();
}

void Window::scanMusiqueDir(QString dirName)
{
    QDir dir(dirName);
    QStringList files = dir.entryList(QStringList() << "*.mp3" << "*.wav" << "*.flac", QDir::Files, QDir::Name);

    for (int i = 0; i < files.count(); ++i)
    {
        playList << dir.absolutePath() + QDir::separator() + files.value(i);
    }

    QStringList directories = dir.entryList(QStringList(), QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);

    for (int i = 0; i < directories.count(); ++i)
    {
        scanMusiqueDir(dir.absolutePath() + QDir::separator() + directories.at(i));
    }
}

void Window::playPause(bool checked)
{
    if(checked)
    {
        this->playFile();
    }
    else
    {
        this->pauseFile();
    }
}

void Window::showPlayList()
{
    if(!plView->isVisible())
    {
        plView->setPlayList(playList);
        plView->show();
    }
    else
    {
        plView->hide();
        this->adjustSize();
    }
}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        sticon->hide();
        show();
        break;
    default:
        ;
    }
}

void Window::mini()
{
    sticon->show();//affichage du tray
    hide();//"cachage" de la fenetre =)

}

void Window::openRadio()
{
    RadioWindow* radioWin = new RadioWindow(this);

    if(radioWin->exec() == QDialog::Accepted)
    {
        sound->setCurrentSource(radioWin->text());
        playRadio();
    }

}

void Window::randomizePlayList()
{
    if(playList.isEmpty())
    {
        return;
    }
    stopFile();

    shuffle(playList);

    current = 0;
    sound->setCurrentSource(playList.at(current));
    if(plView->isVisible())
    {
        plView->setPlayList(playList);
    }
    this->playFile();
}

void Window::openDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select a directory", "",
                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
            );

    if(dir.isEmpty())
    {
        return;
    }
    else
    {
        if(!playList.isEmpty())
        {
            playList.clear();
        }
        scanMusiqueDir(dir);
        if(playList.isEmpty())
        {
            return;
        }
        current = 0;
        sound->setCurrentSource(playList.at(current));
        if(plView->isVisible())
        {
            plView->setPlayList(playList);
        }
        this->playFile();
    }
}

void Window::savePlayList()
{
    QString filename = QFileDialog::getSaveFileName(this, "Select a filename", "", ".m3u | .pls");

    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        QFile out(filename);

        if(out.open(QFile::WriteOnly | QFile::Text))
        {
            for(int i = 0; i < playList.size(); i++)
            {
                QTextStream blah(&out);
                blah << playList.at(i) << "\n";
            }
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier:\n" + filename);
        }
    }
}

void Window::removeFromPlayList()
{
    if(playList.isEmpty())
    {
        return;
    }
    else
    {
        RemovePlWindow* rmWin = new RemovePlWindow(this);

        if(rmWin->exec() == QDialog::Accepted)
        {
            QString index(rmWin->text());
            playList.removeAt(index.toInt()-1);
            plView->setPlayList(playList);
        }
    }
}

void Window::addToPlayList()
{
    if(playList.isEmpty())
    {
        return;
    }
    else
    {
        QStringList filenames = QFileDialog::getOpenFileNames(this, "Select files");

        if(filenames.isEmpty())
        {
            return;
        }
        else
        {
            playList+=filenames;
            plView->setPlayList(playList);
        }
    }
}

void Window::editBookMark()
{
    bookMarkWindow* bmw = new bookMarkWindow(this);

    bmw->exec();
}

bool Window::clearDirectory(const QString& dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = clearDirectory(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }

        result = dir.rmdir(dirName);
    }

    return result;
}

void Window::copyFiles(QString dir)
{
    QString namemusic;
    QProgressDialog progress("Copying files...", "Abort Copy", 0, playList.count(), this);
    progress.setWindowModality(Qt::WindowModal);

    for (int i = 0; i < playList.count(); i++)
     {
         progress.setValue(i);

         if (progress.wasCanceled())
         {
             break;
         }

         QFile file(playList.at(i));
         namemusic = playList.at(i).mid(playList.at(i).lastIndexOf('/'));
         namemusic.remove(0, 1);
         file.copy(dir + "/" + namemusic);
     }
     progress.close();
}

void Window::copyPlaylist(QString dir)
{
    exportPlaylistWindow* window = new exportPlaylistWindow(this);

    if(window->exec() == QDialog::Accepted)
    {
        if(window->checked())
        {
            clearDirectory(dir);
            QDir blah(dir);

            if(!blah.exists())
            {
                blah.mkpath(dir);
            }
        }

        copyFiles(dir);
    }
}

void Window::exportPlaylist()
{
    if(playList.isEmpty())
    {
        QMessageBox::critical(this, "Error", "You must open a playlist first !");
        return;
    }
    else
    {
        QString dir = QFileDialog::getExistingDirectory(this, "Select your media");

        if(dir.isEmpty())
        {
            return;
        }
        else
        {

            copyPlaylist(dir);
        }
    }
}

void Window::setUpMenu()
{
    menubar = new QMenuBar(this);
    menuFile = new QMenu("&File", menubar);
    menuPlayList = new QMenu("&PlayList", menubar);
    /*menuBookMark = new QMenu("&BookMark", menubar);*/
    menuOpenRadio = new QAction(QIcon(":/ressources/iOpenRadio"), "Open Radio", this);
    menuOpenRadio->setShortcut(QKeySequence("Ctrl+W"));
    menuOpenFile = new QAction(QIcon(":/ressources/iOpen"), "Open File", this);
    menuOpenFile->setShortcut(QKeySequence("Ctrl+O"));
    menuMini = new QAction("Mini", this);
    menuMini->setShortcut(QKeySequence("Ctrl+M"));
    menuShuffleDir = new QAction("Shuffle Directory", this);
    menuShufflePlaylist = new QAction("Randomize Playlist", this);
    menuShufflePlaylist->setShortcut(QKeySequence("Ctrl+R"));
    menuOpenDir = new QAction("Open Directory", this);
    menuOpenDir->setShortcut(QKeySequence("Ctrl+D"));
    menuSavePlayList = new QAction("Save PlayList", this);
    menuSavePlayList->setShortcut(QKeySequence("Ctrl+S"));
    menuAddToPlayList = new QAction("Add to PlayList", this);
    menuAddToPlayList->setShortcut(QKeySequence("Ctrl+A"));
    menuRemoveFromPlayList = new QAction("Remove from PlayList", this);
    menuExportPlayList = new QAction("Export PlayList", this);
    menuExportPlayList->setShortcut(QKeySequence("Ctrl+E"));
    menuSong = new QMenu("&Song", menubar);
    menuReadLyrics = new QAction("Read Lyrics", this);
    menuReadLyrics->setShortcut(QKeySequence("Ctrl+L"));
    menuCreateLyrics = new QAction("Create Lyrics", this);
    /*menuEditBookMark = new QAction("Edit BookMark", this);*/

    menuOpenRadio->setIconVisibleInMenu(true);
    menuOpenFile->setIconVisibleInMenu(true);

    menuFile->addAction(menuOpenFile);
    menuFile->addAction(menuOpenDir);
    menuFile->addAction(menuOpenRadio);
    menuFile->addAction(menuShuffleDir);
    menuFile->addSeparator();
    menuFile->addAction(menuMini);

    menuPlayList->addAction(menuShufflePlaylist);
    menuPlayList->addAction(menuSavePlayList);
    menuPlayList->addAction(menuAddToPlayList);
    menuPlayList->addAction(menuRemoveFromPlayList);
    menuPlayList->addAction(menuExportPlayList);

    menuSong->addAction(menuReadLyrics);
    menuSong->addAction(menuCreateLyrics);

    /*menuBookMark->addAction(menuEditBookMark)*/;

    menubar->addMenu(menuFile);
    menubar->addMenu(menuPlayList);
    /*menubar->addMenu(menuBookMark);*/
    menubar->addMenu(menuSong);

    QShortcut * nextMusique = new QShortcut(QKeySequence("Ctrl+N"), this);
    QShortcut* prevMusique = new QShortcut(QKeySequence("Ctrl+P"), this);

    connect(nextMusique, SIGNAL(activated()), this, SLOT(nextFile()));
    connect(prevMusique, SIGNAL(activated()), this, SLOT(prevFile()));
    connect(menuMini, SIGNAL(triggered()), this, SLOT(mini()));
    connect(menuOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(menuOpenRadio, SIGNAL(triggered()), this, SLOT(openRadio()));
    connect(menuShuffleDir, SIGNAL(triggered()), this, SLOT(randomPlayDir()));
    connect(menuShufflePlaylist, SIGNAL(triggered()), this, SLOT(randomizePlayList()));
    connect(menuOpenDir, SIGNAL(triggered()), this, SLOT(openDir()));
    connect(menuSavePlayList, SIGNAL(triggered()), this, SLOT(savePlayList()));
    connect(menuAddToPlayList, SIGNAL(triggered()), this, SLOT(addToPlayList()));
    connect(menuRemoveFromPlayList, SIGNAL(triggered()), this, SLOT(removeFromPlayList()));
    connect(menuExportPlayList, SIGNAL(triggered()), this, SLOT(exportPlaylist()));
    connect(menuReadLyrics, SIGNAL(triggered()), this, SLOT(readLyrics()));
    connect(menuCreateLyrics, SIGNAL(triggered()), this, SLOT(addLyrics()));
    /*connect(menuEditBookMark, SIGNAL(triggered()), this, SLOT(editBookMark()));*/

    this->setMenuBar(menubar);

}

void Window::prevFile()
{
     repeatButton->setChecked(false);
    if((current)-1 > 0)
    {
        current--;
    }
    else
    {
        current = 0;
    }

    sound->setCurrentSource(playList.at(current));
    playFile();
}

void Window::nextFile()
{
    stopFile();
    repeatButton->setChecked(false);
    if(playList.isEmpty())
    {
        return;
    }

    if((current) < playList.count())
    {
        current++;
    }
    if(current == playList.count())
    {
        current = 0;
    }
    if(current > playList.count())
    {
        current = 0;
    }
    sound->setCurrentSource(playList.at(current));
    playFile();
}

void Window::playRadio()
{
    sound->play();
    playPauseButton->setEnabled(true);
    stop->setEnabled(true);
    next->setEnabled(false);
    prev->setEnabled(false);
    repeatButton->setEnabled(false);
}

void Window::playFile()
{
    sound->play();
    playPauseButton->setEnabled(true);
    playPauseButton->setChecked(true);
    stop->setEnabled(true);

    if(current < 0)
    {
        prev->setEnabled(false);
        next->setEnabled(false);
        showButton->setEnabled(false);
    }
    if(current == 0)
    {
        prev->setEnabled(false);
        next->setEnabled(true);
        showButton->setEnabled(true);
    }

    if(current > 0)
    {
        next->setEnabled(true);
        prev->setEnabled(true);
        showButton->setEnabled(true);
    }
    setStatusBarMessage();

}

void Window::pauseFile()
{
    sound->pause();
    playPauseButton->setEnabled(true);
    playPauseButton->setChecked(false);
    stop->setEnabled(true);
}

void Window::stopFile()
{
    sound->stop();
    repeatButton->setChecked(false);
    playPauseButton->setEnabled(true);
    playPauseButton->setChecked(false);
    stop->setEnabled(false);
    showButton->setEnabled(false);
    time->display("00:00");
    totalTime->display("00:00");
    statusBar->clearMessage();
}

void Window::setTimeMusic(qint64 timeMusique)
{
    QTime displayTime(0, (timeMusique / 60000) % 60, (timeMusique / 1000) % 60);
    QTime ttime(0, (sound->totalTime() / 60000) % 60, (sound->totalTime() / 1000) % 60);

    totalTime->display(ttime.toString("mm:ss"));
    time->display(displayTime.toString("mm:ss"));
}

void Window::addm3u(QString name)
{
    QString chaine;
    QFile file(name);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            chaine += line + '\n';
        }
        file.close();

        playList = chaine.split('\n');
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier : " + name);
    }

    playList.removeLast();
    current = 0;
    sound->setCurrentSource(playList.at(current));
    this->playFile();
}

void Window::addpls(QString name)
{
    QString chaine;
    QFile file(name);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            chaine += line;
        }
        file.close();

        QRegExp reg("(File)\\d+(=)");
        QRegExp rex("(Title)\\d+(=)");
        int i;
        int fin;
        i = chaine.indexOf(reg);
        while(i != -1)
        {
            fin = chaine.indexOf(rex, i);
            if(fin != -1)
            {
                QString tmp;
                QStringList blah;
                tmp = chaine.mid(i, fin-i);
                blah = tmp.split("=");
                playList.append(blah.at(1));
            }

            i = chaine.indexOf(reg, fin);
        }

    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier : " + name);
    }

    current = 0;
    sound->setCurrentSource(playList.at(current));
    this->playFile();
}

void Window::openFile()
{

    playList.clear();
    current = -1;
    QString name = QFileDialog::getOpenFileName(this, "Selectionner un fichier", QString());

    if(!name.isEmpty())
    {
        if((name.indexOf(".pls") == -1) && (name.indexOf(".m3u") == -1))
        {
            playList.append(name);
            current = 0;
            sound->setCurrentSource(playList.at(current));
            this->playFile();
        }
        else
        {
            if(name.lastIndexOf(".pls") != -1)
            {
                addpls(name);
            }

            if(name.lastIndexOf(".m3u") != -1)
            {
                addm3u(name);
            }
        }
    }
    else
    {
        return;
    }
}
