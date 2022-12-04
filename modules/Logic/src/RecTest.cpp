
#include "RecommenderSystem.h"
#include <iostream>

int main(){

    RecommenderSystem test;
    std::vector<std::string> userLikedGenres;
//    for(int i=0;i<3;i++)
//    {
//        std::string genre;
//        std::cin>>genre;
//        userLikedGenres.push_back(genre);
//    }
//    test.setUserLikedGenres(userLikedGenres);

//    for(int i=0;i<test.GetUserLikedGenres().size();i++)
//    {
//        auto result = test.recommendedByLikedGenres(userLikedGenres[i]);
//        if(!result->empty())
//        {
//            for(auto &movies: *result)
//                std::cout<<movies.m_title<<" ";
//            std::cout<<"\n";
//        }
//    }

    std::vector<std::string> userLikedMovies;
    for(int i=0;i<3;i++)
    {
        std::string movie;
        std::cin>>movie;
        userLikedMovies.push_back(movie);
    }
    test.setUserLikedMovies(userLikedMovies);

    auto result = test.recommendedByLikedMovies();
    for(auto &genres: result)
    {
        if(!genres->empty())
        {
            for(auto &movies: *genres)
                std::cout<<movies.m_title<<" ";
            std::cout<<"\n";
        }
    }


    return 0;
}