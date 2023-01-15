#include "MoviesTable.h"
#include "ui_MoviesTable.h"

//CONSTRUCTORS
MoviesTable::MoviesTable(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::MoviesTable) {
    ui->setupUi(this);
}

MoviesTable::~MoviesTable() {
    delete ui;
}

MoviesTable::MoviesTable(int uid, QWidget *parent) : MoviesTable(parent) {
    this->userId = uid;
}

//GETTERS

//SETTERS

//OTHER METHODS

//BUTTONS - slots
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

        int parentWidth = ui->tableView->parentWidget()->width();
        int numColumns = ui->tableView->model()->columnCount();
        int columnWidth = parentWidth / numColumns;

        for (int i = 0; i < numColumns; ++i) {
            ui->tableView->setColumnWidth(i, columnWidth);
        }

        ui->tableView->horizontalHeader()->setVisible(true);
        ui->tableView->setShowGrid(false);
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

    QDialog *moviePageDialog = new QDialog();
    moviePageDialog->setMaximumSize(QSize(900, 600));

    MovieDetails *movieDetails = new MovieDetails(movieId, this->userId);

    QHBoxLayout * giveRatingLayout = new QHBoxLayout(movieDetails);

    moviePageDialog->setLayout(giveRatingLayout);
    giveRatingLayout->addWidget(movieDetails);
    moviePageDialog->exec();

    delete movieDetails;
    moviePageDialog->deleteLater();
}

void MoviesTable::on_pushButton_details_clicked() {
    if (_showMovie == nullptr) {
        _showMovie = new ShowMovie(this);
        _showMovie->show();
    } else {
        _showMovie->close();
        _showMovie = nullptr;
    }
}

void MoviesTable::on_homeButton_clicked() {
    emit homeClicked();
}







