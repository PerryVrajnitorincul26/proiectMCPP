#ifndef SHOWMOVIE_H
#define SHOWMOVIE_H

#include <QWidget>

namespace Ui {
class ShowMovie;
}

class ShowMovie : public QWidget
{
    Q_OBJECT

public:
    explicit ShowMovie(QWidget *parent = nullptr);
    ~ShowMovie();

private:
    Ui::ShowMovie *ui;
};

#endif // SHOWMOVIE_H
