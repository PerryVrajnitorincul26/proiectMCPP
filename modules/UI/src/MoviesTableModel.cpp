//
// Created by Iusaq on 11/26/2022.
//
#include "MoviesTableModel.h"

//CONSTRUCTORS
MoviesTableModel::MoviesTableModel(QObject *parent) : QAbstractTableModel(parent) {

}

//GETTERS

//SETTERS

//OTHER METHODS
void MoviesTableModel::populateData(const QList<QString> &movieTitle, const QList<QString> &movieGenres,
                                    const QList<int> movieID) {
    m_movie_title.clear();
    m_movie_title = movieTitle;
    m_movie_genres.clear();
    m_movie_genres = movieGenres;
    m_movie_id.clear();
    m_movie_id = movieID;
}

int MoviesTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_movie_title.length();
}

int MoviesTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant MoviesTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (role == -1) {
        return m_movie_id[index.row()];
    }
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return m_movie_title[index.row()];
    } else if (index.column() == 1) {
        return m_movie_genres[index.row()];
    }
    return QVariant();
}

QVariant MoviesTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Title");
        } else if (section == 1) {
            return QString("Genres");
        }
    }
    return QVariant();
}

//BUTTONS

//SIGNALS

