//
// Created by Iusaq on 11/26/2022.
//

#ifndef MCPP_MOVIESTABLEMODEL_H
#define MCPP_MOVIESTABLEMODEL_H

#include <QAbstractTableModel>

namespace Ui {
    class MoviesTableModel;
}
class MoviesTableModel: public QAbstractTableModel {
    Q_OBJECT

public:
    MoviesTableModel(QObject *parent = 0);

    void populateData(const QList<QString> &movieTitle,const QList<QString> &movieGenres);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<QString> m_movie_title;
    QList<QString> m_movie_genres;

};


#endif //MCPP_MOVIESTABLEMODEL_H
