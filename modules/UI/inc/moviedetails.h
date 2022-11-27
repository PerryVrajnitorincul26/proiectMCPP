//
// Created by Codrut on 11/27/2022.
//

#ifndef MCPP_MOVIEDETAILS_H
#define MCPP_MOVIEDETAILS_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MovieDetails; }
QT_END_NAMESPACE

class MovieDetails : public QWidget {
Q_OBJECT

public:
    explicit MovieDetails(QWidget *parent = nullptr);

    double on_pushButton_clicked();

    ~MovieDetails() override;

private:
    Ui::MovieDetails *ui;
};


#endif //MCPP_MOVIEDETAILS_H
