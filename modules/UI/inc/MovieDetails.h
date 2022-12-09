//
// Created by Codrut on 11/27/2022.
//

#ifndef MCPP_MOVIEDETAILS_H
#define MCPP_MOVIEDETAILS_H

#include <QWidget>
#include <MovieDatabase.h>
#include <db_headers.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MovieDetails; }
QT_END_NAMESPACE

class MovieDetails : public QWidget {
Q_OBJECT

    std::unique_ptr<user_rating_row> reviewObj;

public:
    explicit MovieDetails(QWidget *parent = nullptr);

    explicit MovieDetails(int mid, int cid, QWidget *parent = nullptr);

    double on_GiveRating_clicked();

    ~MovieDetails() override;

private:
    Ui::MovieDetails *ui;

public slots:
    void loadImage();
};


#endif //MCPP_MOVIEDETAILS_H
