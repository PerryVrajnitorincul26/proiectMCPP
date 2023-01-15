#include "ShowMovie.h"
#include "ui_ShowMovie.h"
#include "QPixmap"
#include "MovieDetails.h"

//CONSTRUCTORS
ShowMovie::ShowMovie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowMovie)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Bulibas/Documents/GitHub/proiectMCPP/modules/UI/moviedatabase.jpg");
    ui->label_Image->setPixmap(pix.scaled(200,200,Qt::KeepAspectRatio));
    ui->label_movieTitle->setText("Title");
    ui->label_Genre->setText("All genre");
    ui->label_rating->setText("Rating from 1 to 5");
}
//GETTERS

//SETTERS

//BUTTONS


//DESTRUCTOR
ShowMovie::~ShowMovie()
{
    delete ui;
}