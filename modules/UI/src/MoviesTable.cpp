#include "MoviesTable.h"
#include "ui_MoviesTable.h"


MoviesTable::MoviesTable(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::MoviesTable) {
    ui->setupUi(this);
}

MoviesTable::~MoviesTable() {
    delete ui;
}

//NU VA ATINGETI DE FUNCTIA ASTA CA VA SPARG
void MoviesTable::on_pushButton_clicked() {
    std::string titleToSearch = ui->titleInput->text().toStdString();
    std::string genreToSearch = ui->genreInput->text().toStdString();
    QList<QString> moviesTitles;
    QList<QString> moviesGenres;
    QList<int> moviesId;

    auto &dbRef = MovieDatabase::instance();
    auto searchResult = dbRef.searchMovieTitles(titleToSearch);

    if (!searchResult.empty()) {
        for (auto &item: searchResult) {
            int id = item->m_movie_id;
            QString title = QString::fromStdString(item->m_title);
            QString genres = QString::fromStdString(item->m_genres);
            moviesTitles.append(title);
            moviesGenres.append(genres);
            moviesId.append(id);
        }
        ///Note that delete on nullptr does nothing. This is not undefined behaviour.
        delete model;
        model = new MoviesTableModel(this);
        model->populateData(moviesTitles, moviesGenres, moviesId);

        ui->tableView->setModel(model);

        ui->tableView->horizontalHeader()->setVisible(true);
        ui->tableView->show();
        std::string message("We found ");
        message.append(std::to_string(searchResult.size()));
        message.append(" results");

        ui->msgLabel->setText(QString::fromStdString(message));
    } else {
        ui->msgLabel->setText("No results have been found!");
    }
}

void MoviesTable::on_tableView_clicked(const QModelIndex &pos) {
    int movieId = model->data(pos, -1).toInt();
    auto tempDialog = new QDialog();
    auto myDialog = new MovieDetails(movieId,this->user_id);
    auto myLayout = new QHBoxLayout();
    tempDialog->setLayout(myLayout);
    myLayout->addWidget(myDialog);
    tempDialog->exec();
}

MoviesTable::MoviesTable(int uid, QWidget *parent) : MoviesTable(parent) {
    this->user_id = uid;
}




void MoviesTable::on_pushButton_back_clicked() {
    emit homeClicked();
}

void MoviesTable::on_pushButton_details_clicked() {
    _showmovie= new ShowMovie(this);
_showmovie->show();
}





