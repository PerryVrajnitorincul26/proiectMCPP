//
// Created by perry on 11/11/22.
//

#ifndef MCPP_MOVIEDATABASE_H
#define MCPP_MOVIEDATABASE_H

#include "db_headers.h"
#include "sqlite_orm/sqlite_orm.h"
#include <iostream>

using namespace sqlite_orm;

/*!
 * Singleton that contains a pointer to the database
 * NOTE: You should only be able to create references to this object by calling
 */
class MovieDatabase {
private:
    MovieDatabase() {
        dbPtr = std::make_unique<Storage>(init_storage("identifier.sqlite"));
        std::cout<<"database created"<<std::endl;
    }
    /*!
     * This should make it impossible to create anything other reference to this class. As such we avoid duplicating
     * any information regarding the database.
     */
    MovieDatabase(MovieDatabase &) = delete;
    MovieDatabase(MovieDatabase &&) = delete;
    MovieDatabase &operator=(MovieDatabase &) = delete;
    MovieDatabase &operator=(MovieDatabase &&) = delete;

public:
    //Pointer will remain public for now mostly for testing purposes but this will at some point be changed.(hopefully)
    std::unique_ptr<Storage> dbPtr;
    static MovieDatabase &instance()
    {
        static std::unique_ptr<MovieDatabase> md(new MovieDatabase);
        return *md;
    }
    static MovieDatabase &movieDatabase(){
        return instance();
    }



};


#endif //MCPP_MOVIEDATABASE_H
