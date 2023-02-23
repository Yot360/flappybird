//
// Created by yot on 23/02/23.
//

#ifndef FLAPPYBIRD_SCOREMANAGER_H
#define FLAPPYBIRD_SCOREMANAGER_H

#include <string>

class ScoreManager {

public:
    ScoreManager(const std::string& filename) : m_filename(filename) {

    }

    bool saveScore(int score);
    bool loadScore(int& score);

private:
    std::string m_filename;

};


#endif //FLAPPYBIRD_SCOREMANAGER_H
