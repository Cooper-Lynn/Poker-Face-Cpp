 //
// Created by coope on 17/02/2025.
//

#include "AIModel.hpp"

#include <algorithm>
#include <fstream>


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



double AIModel::getLearningRate() {
    return alpha;
}

double AIModel::getDiscount() {
     return gamma;
 }

double AIModel::getExploration() {
    return epsilon;
}

void AIModel::save(std::string& filename) {

}

int AIModel::getStateID(std::vector<double> &state) {
     position = state[0] * 2;
     handStrength = state[1] * 9;
     potRatio = state[3] * 4;

     return position + (handStrength * 3) + (potRatio * 30);

}

int AIModel::selectAction(std::vector<double> &state, bool training) {

     int stateID = getStateID(state);

     if (training) {
         explorationRate = getExploration();
     }
     else {
         explorationRate = getExploration() * 0.1;
     }

     std::uniform_real_distribution<double> dist(0.0, 1.0);
     if(dist(rng) < explorationRate) {
         std::uniform_int_distribution<int> action(0, 2);
         return action(rng);
     }
     auto& qValues = qTable[stateID];
     int bestAction = 0;
     double bestValue = qValues[0];
     for (int i = 1; i < qValues.size(); i++) {
         if (qValues[i] > bestValue) {
             bestValue = qValues[i];
             bestAction = i;
         }
     }

     return bestAction;
}

double AIModel::simHand(std::vector<double> &state, int action) {
     position = state[0];
     handStrength = state[1];
     potRatio = state[3];

     if (action == 2) { //FOLD
         if (handStrength < 0.2) {
             return 0.1;
         }
         else if (handStrength > 0.5) {
             return -1.0;
         }
         else {
             if (position < 0.3 && potRatio < 0.3) {
                 return 0.05;
             }
             return -0.3;
         }
     }
     else if (action == 1) { //RAISE
         if (handStrength > 0.6) {
             return 1.0;
         }
         else if (handStrength > 0.4 && potRatio>0.5) {
             return 0.5;
         }
         else if (handStrength > 0.3 && potRatio>0.4) {
             return 0.3;
         }
         else if (handStrength > 0.3 && position > 0.4) {
             return 0.2;
         }



     }
     else {

     }

}





