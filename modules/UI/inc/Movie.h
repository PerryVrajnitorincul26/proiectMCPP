//
// Created by Iusaq on 11/11/2022.
//

#ifndef MCPP_MOVIE_H
#define MCPP_MOVIE_H


#include <string>
#include <array>
#include <vector>
#include <ostream>

class Movie {
    std::string m_title;
    std::vector<std::string> m_genres;
public:
    Movie(const std::string &title, const std::vector<std::string> &genres);

    Movie(const std::string &title, const std::string &str);

    explicit Movie(const std::string &title);

    Movie();

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    const std::vector<std::string> &getGenres() const;

    void addGenre(const std::string& genre);

    std::string genresToString(); ///returns a string of genres delimited with | to fit in the movie_row classe's genres string

    void removeGenre(const std::string& genre);

    ~Movie();

};


#endif //MCPP_MOVIE_H
