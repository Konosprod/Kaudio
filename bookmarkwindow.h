#ifndef BOOKMARKWINDOW_H
#define BOOKMARKWINDOW_H

#include <QDialog>

namespace Ui {
class bookMarkWindow;
}

class bookMarkWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit bookMarkWindow(QWidget *parent = 0);
    ~bookMarkWindow();
    
private:
    Ui::bookMarkWindow *ui;
};

#endif // BOOKMARKWINDOW_H
