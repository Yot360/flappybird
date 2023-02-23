//
// Created by yot on 23/02/23.
//

#include <fstream>
#include <iostream>
#include "ScoreManager.h"

bool ScoreManager::saveScore(int score) {
    std::ofstream file(m_filename);
    if (!file) {
        std::cerr << "Failed to open file for writing: " << m_filename << std::endl;
        return false;
    }
    file << score << std::endl;
    return true;
}

bool ScoreManager::loadScore(int &score) {
    std::ifstream file(m_filename);
    if (!file) {
        std::cerr << "Failed to open file for reading: " << m_filename << std::endl;
        return false;
    }
    file >> score;
    return true;
}
