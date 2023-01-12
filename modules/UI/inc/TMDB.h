//
// Created by Iusaq on 12/8/2022.
//

#ifndef MCPP_TMDB_H
#define MCPP_TMDB_H


#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonValue>

class TMDB : public QObject {
Q_OBJECT

    const QString m_baseUrl = "https://api.themoviedb.org/3/movie/";

    QString m_movieId;

    const QString m_apiKey = "?api_key=7f62067bb2dd1e52cee2dca20be9759a"; //this is a private api key v3 for the imdb account special77777

    const QString m_tmdbImagesUrl = "https://image.tmdb.org/t/p/w500"; //here we are supposed to append the posterpath of the movie requested

    QString *tmdb_id = nullptr;

    QNetworkAccessManager *m_naManager; //"naManager" stands for network access manager

    //Movie Data JSON format
    //adult - boolean
    bool m_adult = true; //In Qt, boolean values are represented using the bool type from the C++ standard library. The bool type can have one of two values: true or false.
    //budget - floating number
    double m_budget = 0;
    //overview - string
    QString m_overview = "This is supposed to be a description";
    //popularity - floating number
    double m_popularity = 0;
    //poster_path - string
    QString m_posterPath = "/thePosterPathOfTheMovie";
    //release_date - dateformat yyyy-mm-dd
    QDate m_releaseDate; //documentation here: https://doc.qt.io/qt-6/qdate.html#QDate-6
    //revenue - floating number
    double m_revenue = 0;
    //runtime - number (minutes)
    double m_runtime = 0;

public :
    //Movie's poster
    QPixmap *pixmap = nullptr;

    void setMovie();

    explicit TMDB(const long long int &movieId); //here will be executed the connection with the APIs

    ~TMDB() override;

    [[maybe_unused]] void setPosterPath(const QString &mPosterPath);

    [[maybe_unused]] const QString &getApiKey() const;

    [[maybe_unused]] QNetworkAccessManager *getNaManager() const;

    [[maybe_unused]] bool isAdult() const;

    [[maybe_unused]] double getBudget() const;

    const QString &getOverview();

    [[maybe_unused]] double getPopularity() const;

    [[maybe_unused]] const QString &getPosterPath();


    [[maybe_unused]] double getRevenue() const;

    [[maybe_unused]] double getRuntime() const;

public slots:

    [[maybe_unused]] void imageDownloaded(QNetworkReply *replyReceived);

    void dataFinished();

    void imageFinished();


signals:

    void finishedLoading();
};


#endif //MCPP_TMDB_H
