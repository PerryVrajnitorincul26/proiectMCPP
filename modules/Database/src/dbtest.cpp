//
// Created by Perry on 11/7/2022.
//

#include<sqlite_orm/sqlite_orm.h>
#include<iostream>
#include "db_headers.h"
#include "MovieDatabase.h"
//This is the database modules and as such this makes sense imho.

using namespace sqlite_orm;

int main() {
    auto &ref = MovieDatabase::movieDatabase();
    auto sal = ref.moviesByUserWishlist(1);


}

