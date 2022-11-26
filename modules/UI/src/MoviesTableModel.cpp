//
// Created by Iusaq on 11/26/2022.
//
#include "MoviesTableModel.h"

MoviesTableModel::MoviesTableModel(QObject *parent) : QAbstractTableModel(parent) {

}

void MoviesTableModel::populateData(const QList<QString> &movieTitle,const QList<QString> &movieGenres)
{
    m_movie_title.clear();
    m_movie_title = movieTitle;
    m_movie_genres.clear();
    m_movie_genres = movieGenres;
    return;
}

int MoviesTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_movie_title.length();
}

int MoviesTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant MoviesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return m_movie_title[index.row()];
    } else if (index.column() == 1) {
        return m_movie_genres[index.row()];
    }
    return QVariant();
}

QVariant MoviesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Title");
        } else if (section == 1) {
            return QString("Genres");
        }
    }
    return QVariant();
}

