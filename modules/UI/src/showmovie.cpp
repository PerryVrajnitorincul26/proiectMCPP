#include "showmovie.h"
#include "ui_showmovie.h"
#include "QPixmap"
#include "moviedetails.h"
ShowMovie::ShowMovie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowMovie)
{
    ui->setupUi(this);

}

ShowMovie::~ShowMovie()
{
    delete ui;
}

void ShowMovie::on_pushButton_close_clicked() {
    close();

}
