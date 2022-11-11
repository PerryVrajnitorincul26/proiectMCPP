//
// Created by Iusaq on 11/11/2022.
//

#include "../inc/Movie.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

///CONSTRUCTORS
Movie::Movie()  = default; //default constructor

Movie::Movie(const std::string &title) {
    if (title.size() < 1)
        throw std::invalid_argument("Title cannot be empty");
    this->m_title=title;
} //only title

Movie::Movie(const std::string &title, const std::vector<std::string> &genres) : m_genres(genres) {
    if (title.size() < 1)
        throw std::invalid_argument("Title cannot be empty");
    this->m_title=title;
}  //only title a vector of genres

Movie::Movie(const std::string &title, const std::string &genres) { //if the genres are received as a string, they are split by | delimiter
    std::stringstream ss(genres);

    if (title.size() < 1)
        throw std::invalid_argument("Title cannot be empty");

    this->m_title = title;

    while(!ss.eof()){
        std::string word;

        std::getline(ss, word, '|');

        if(word.size()>0)
            this->m_genres.push_back(word);
    }
} //title and a string of genres delimited by '|'

///GETTERS
const std::string &Movie::getTitle() const {
    return m_title;
}

const std::vector<std::string> &Movie::getGenres() const {
    return m_genres;
}

///SETTERS
void Movie::setTitle(const std::string &title) {
    if(title.size()<1)
        throw std::invalid_argument("Title cannot be empty");
    m_title = title;
}

///DESTRUCTOR
Movie::~Movie() {};

///UTILITY FUNCTIONS
void Movie::addGenre(const std::string &genre) {
    if(genre.size()<1)
        throw std::invalid_argument("Genre cannot be empty");
    this->m_genres.push_back(genre);
}

void Movie::removeGenre(const std::string &genre){
    this->m_genres.erase(std::remove(this->m_genres.begin(), this->m_genres.end(), genre), this->m_genres.end());
}

std::string Movie::genresToString() {
    if(this->m_genres.size()==0)
        return "";
    std::string result;
    int nr=this->m_genres.size();
    for(auto str: this->m_genres){
        for(char c: str)
            result.push_back(c);
        if(nr>1)
        result.push_back('|');
        nr--;
    }
    return result;
}


