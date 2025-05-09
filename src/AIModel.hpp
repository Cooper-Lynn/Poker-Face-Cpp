//
// Created by coope on 17/02/2025.
//

#ifndef AIMODEL_HPP
#define AIMODEL_HPP

#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>

class AIModel {
private:
    std::vector<std::vector<double> > qTable;
    double alpha;
    double gamma;
    double epsilon;
    double explorationRate;
    double baseReward;
    std::mt19937 rng;
    int games_played;
    double position;
    double handStrength;
    double potRatio;
    std::string fileName = "src/aiModel.csv";

    int getStateID(std::vector<double> &state);

    double simHand(std::vector<double> &state, int action);

    enum actions {
        CHECK,
        RAISE,
        FOLD,
    };

public:
    AIModel(double learn, double discount, double explore);

    ~AIModel();

    void quickTrain(int episodes);

    void learn(std::vector<double> &state, int action, double reward,
               std::vector<double> &nextState);

    int selectAction(std::vector<double> &state, bool training = false);

    void saveFile();

    void loadFile();

    double getLearningRate();

    double getDiscount();

    double getExploration();
};


#endif //AIMODEL_HPP
