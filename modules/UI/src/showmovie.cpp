#include "showmovie.h"
#include "ui_showmovie.h"
#include "QPixmap"
#include "moviedetails.h"
ShowMovie::ShowMovie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowMovie)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Bulibas/Documents/GitHub/proiectMCPP/modules/UI/moviedatabase.jpg");
    ui->label_Image->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));
    ui->label_movieTitle->setText("Title");
    ui->label_Genre->setText("All genre");
    ui->label_rating->setText("Rating from 1 to 5");
}

ShowMovie::~ShowMovie()
{
    delete ui;
}

void ShowMovie::on_pushButton_close_clicked() {
    close();

}
