#include <vector>
#include <string>
#include <db_headers.h>
#include <MovieDatabase.h>
#include <cmath>
//If I'm correct user vector should be the same.
using movieRatingVec = decltype(std::vector<std::unique_ptr<genome_scores_row>>());
using userRatingVec = decltype(std::vector<std::unique_ptr<user_scores_row>>());
using tagNameVec = decltype(std::vector<std::unique_ptr<genome_tag_row>>());

class RecommenderSystem {
    int m_uid;

    RecommenderSystem();

public:
    RecommenderSystem(const std::vector<std::string> &userLikedGenres, const std::vector<std::string> &userLikedMovies);

    userRatingVec m_userScores, m_weights;
    tagNameVec tagNames;
    std::vector<movieRatingVec> m_consideredMovies;
    std::vector<std::string> userLikedMovies, userLikedGenres;

    RecommenderSystem(int uid);

    //adding movieRatingVec with userRatingVec
    //for now, return for userid
    template<typename T>
    T addUserMovieRating(const userRatingVec &ur, const movieRatingVec &mr, int index);


    template<typename vecA, typename vecB>
    void sumGenomeVect(vecA &lhs, const vecB &rhs) {
        try {
            for (int i = 0; i < lhs.size(); ++i) {
                lhs[i]->m_relevance += rhs[i]->m_relevance;
            }
        } catch (std::range_error &e) {
            std::cout << "Index out of range in summing genome tags " << e.what() << "\n";
        }
    }

    template<typename vecA, typename vecB>
    void prodGenomeVect(vecA &lhs, const vecB &rhs) {
        try {
            for (int i = 0; i < lhs.size(); ++i) {
                lhs[i]->m_relevance *= rhs[i]->m_relevance;
            }
        } catch (std::range_error &e) {
            std::cout << "Index out of range in summing genome tags " << e.what() << "\n";
        }
    }

    template<typename vecA, typename vecB>
    void prodGenomeSquareVect(vecA &lhs, const vecB &rhs) {
        try {
            for (int i = 0; i < lhs.size(); ++i) {
                lhs[i]->m_relevance *= rhs[i]->m_relevance;
                lhs[i]->m_relevance *= rhs[i]->m_relevance;
            }
        } catch (std::range_error &e) {
            std::cout << "Index out of range in summing genome tags " << e.what() << "\n";
        }
    }

    template<typename vecA>
    double sumVect(const vecA &arg) {
        float sum = 0;
        for (const auto &i: arg) {
            sum += i->m_relevance;
        }
        return sum;
    }

    template<typename vecA>
    vecA deepCopyVector(const vecA &arg) {
        vecA newcopy;
        for (const auto &i: arg) {
            newcopy.emplace_back(*i);
        }
        return std::move(newcopy);
    }

    void avgVec(userRatingVec &modified, const std::vector<movieRatingVec> &arg) {
        for (const auto &i: arg) {
            sumGenomeVect(modified, i);
        }
        for (auto &i: modified) {
            i->m_relevance /= arg.size();
        }
    }


    userRatingVec deepCopyVector(const userRatingVec &arg) {
        userRatingVec newcopy;
        for (const auto &i: arg) {
            newcopy.push_back(std::make_unique<user_scores_row>(*i));
        }
        return std::move(newcopy);
    }

    movieRatingVec deepCopyVector(const movieRatingVec &arg) {
        movieRatingVec newcopy;
        for (const auto &i: arg) {
            newcopy.push_back(std::make_unique<genome_scores_row>(*i));
        }
        return std::move(newcopy);
    }

    double getDist(const userRatingVec &user, const movieRatingVec &movie);

    //calculating the sum(k=1->n) of Wk*Xk*Yk
    float sumOfGenomes(userRatingVec ur, movieRatingVec mr);

    void populateUserScores(int uid = -1);

    std::vector<std::string> GetUserLikedGenres() const;

    std::vector<std::string> GetUserLikedMovies() const;

    void setUserLikedGenres(const std::vector<std::string> &userLikedGenres);

    void setUserLikedMovies(const std::vector<std::string> &userLikedMovies);

    std::vector<std::unique_ptr<movie_row>> recommendedByLikedGenres(std::string genre);

    std::vector<std::vector<std::unique_ptr<movie_row>>> recommendedByLikedMovies();

    virtual ~RecommenderSystem();
};