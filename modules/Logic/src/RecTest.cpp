
#include "RecommenderSystem.h"
#include <iostream>

int main() {

    RecommenderSystem test(3);
    test.sumGenomeVect(test.m_userScores, test.m_consideredMovies[0]);
    //auto coaie = test.deepCopyVector(test.m_userScores);
    for (int i = 1; i < 98; ++i) {
        auto multefort = test.getDist(test.m_userScores, test.m_consideredMovies[i]);
        std::cout << multefort<<"\n";
    }
    return 0;
}