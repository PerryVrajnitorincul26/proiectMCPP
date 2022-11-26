#include "moviestable.h"
#include "ui_moviestable.h"
#include "MovieDatabase.h"
#include "MoviesTableView.h"
#include <QString>

MoviesTable::MoviesTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoviesTable)
{
    ui->setupUi(this);
}

MoviesTable::~MoviesTable()
{
    delete ui;
}

void MoviesTable::on_pushButton_clicked()
{

    QList<QString> moviesTitles;
    QList<QString> moviesGenres;

    QTableView *view = new QTableView;
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto &dbRef = MovieDatabase::instance();
    auto searchResult = dbRef.searchMovieTitles("at");

    for(auto &item: *searchResult){
        QString id = QString::number(item.m_movie_id);
        QString title = QString::fromStdString(item.m_title);
        QString genres = QString::fromStdString(item.m_genres);
        moviesTitles.append(title);
        moviesGenres.append(genres);
    }

    MoviesTableView *model = new MoviesTableView(this);
    model->populateData(moviesTitles, moviesGenres);

    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();
}



