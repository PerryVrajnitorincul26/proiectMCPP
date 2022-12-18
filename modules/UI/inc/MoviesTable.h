#ifndef MOVIESTABLE_H
#define MOVIESTABLE_H

#include <QDialog>
#include <MovieDatabase.h>
#include <db_headers.h>
#include "MovieDatabase.h"
#include "MoviesTableModel.h"
#include "MovieDetails.h"
#include <QString>
#include <QDebug>
#include "ShowMovie.h"

namespace Ui {
    class MoviesTable;
}

class MoviesTable : public QDialog {
Q_OBJECT
    MoviesTableModel *model= nullptr;
    int user_id = 0;
public:
    explicit MoviesTable(QWidget *parent = nullptr);
    explicit MoviesTable(int uid, QWidget *parent = nullptr);

    ~MoviesTable();

private slots:

    void on_pushButton_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_details_clicked();
    void on_tableView_clicked(const QModelIndex &pos);

private:
    Ui::MoviesTable *ui;
    ShowMovie *_showmovie;

signals:
    void homeClicked();
};

#endif // MOVIESTABLE_H