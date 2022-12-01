#ifndef MOVIESTABLE_H
#define MOVIESTABLE_H

#include <QDialog>
#include <MovieDatabase.h>
#include <db_headers.h>

namespace Ui {
class MoviesTable;
}

class MoviesTable : public QDialog
{
    Q_OBJECT

public:
    explicit MoviesTable(QWidget *parent = nullptr);
    ~MoviesTable();

private slots:

    void on_pushButton_clicked();

private:
    Ui::MoviesTable *ui;
};

#endif // MOVIESTABLE_H
