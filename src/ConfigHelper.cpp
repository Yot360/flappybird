//
// Created by yot on 25/02/23.
//

#include <fstream>
#include "ConfigHelper.h"

bool ConfigHelper::Initialize() {
    // Load JSON and parse its info
    std::ifstream f("Assets/config.json");
    data = json::parse(f);
    return true;
}

int ConfigHelper::GetBestScore() {
    return data.at("best_score");
}

void ConfigHelper::SetBestScore(int score) {
    data["best_score"] = score;
}

float ConfigHelper::GetGravity() {
    return data.at("gravity");
}

float ConfigHelper::GetJumpVelocity() {
    return data.at("jump_velocity");
}

float ConfigHelper::GetPipeSpeed() {
    return data.at("pipe_speed");
}

int ConfigHelper::GetPipeGap() {
    return data.at("pipe_gap");
}

int ConfigHelper::GetPipeWidth() {
    return data.at("pipe_width");
}

void ConfigHelper::SaveJson() {
    std::ofstream file("Assets/config.json");
    file << std::setw(4) << data << std::endl;
    file.flush();
}

