#include "mainWindow.h"

/**

TODO:
  - Favoris
  - Lecture aléatoire de playlist
  - Double-clique playlist
  - Vidéo
**/

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
   Q_INIT_RESOURCE(rc);
   app.setApplicationName("Kaudio");
   Window win(argc, argv);
   win.setWindowTitle("Kaudio");
   win.setWindowIcon(QIcon(":/ressources/icon"));
   win.show();
   return app.exec();
}
