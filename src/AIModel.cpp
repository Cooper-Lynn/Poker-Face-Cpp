 //
// Created by coope on 17/02/2025.
//

#include "AIModel.hpp"

#include <algorithm>


 AIModel::AIModel(double learn, double discount, double explore) {
    alpha = learn;
    gamma = discount;
    epsilon = explore;
    std::random_device rd;
    rng = std::mt19937(rd());

    qTable.resize(150, std::vector<double>(3, 0.0));
}

void AIModel::quickTrain(int episodes = 5000) {
    std::cout<<"Running quick training for " <<episodes<<" episodes"<<std::endl;
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int episode = 0; episode < episodes; episode++) {
        std::vector<double> state = {
            dist(rng), //position
            dist(rng), //hand
            dist(rng), //pot
        };

        int action = selectAction(state, true);
        double reward = simHand(state, action);

        std::vector<double> nextState = {
            dist(rng),
            dist(rng),
            dist(rng),
        };
        learn(state, action, reward, nextState);
        if ((episode + 1) % 100 == 0) {
            std::cout << "Training episode " << episode + 1 << "/" << episodes << "\n";
        }
    }
}

void AIModel::learn(std::vector<double> &state, int action, double reward,std::vector<double> &nextState) {
    int stateID = getStateID(state);
    int nextStateID = getStateID(nextState);

    double maxNextQ = *std::max_element(qTable[nextStateID].begin(), qTable[nextStateID].end());

     qTable[stateID][action] += alpha * (reward +gamma * maxNextQ - qTable[stateID][action]);
     games_played++;


     if (games_played % 100 == 0) {
         save("aiModel.dat");
     }
}


