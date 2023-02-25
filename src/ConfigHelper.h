//
// Created by yot on 25/02/23.
//

#ifndef FLAPPYBIRD_CONFIGHELPER_H
#define FLAPPYBIRD_CONFIGHELPER_H

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigHelper {

public:
    static ConfigHelper& getInstance()
    {
        static ConfigHelper instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    bool Initialize();
    void SaveJson();

    int GetBestScore();
    void SetBestScore(int score);
    float GetGravity();
    float GetJumpVelocity();
    float GetPipeSpeed();
    int GetPipeGap();
    int GetPipeWidth();

private:
    ConfigHelper() = default;

    json data;

public:
    ConfigHelper(ConfigHelper const&) = delete;
    void operator=(ConfigHelper const&) = delete;
};


#endif //FLAPPYBIRD_CONFIGHELPER_H
