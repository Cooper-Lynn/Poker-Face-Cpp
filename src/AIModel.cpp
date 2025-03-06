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

    qTable.resize(250, std::vector<double>(3, 0.0));
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
         saveFile();
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

void AIModel::saveFile() {
     std::ofstream file(fileName);
     if (!file.is_open()) {
         std::cerr << "Could not open file for saving: " << fileName << std::endl;
         return;
     }

     file<<std::to_string(alpha)<<std::endl;
     file<<std::to_string(gamma)<<std::endl;
     file<<std::to_string(epsilon)<<std::endl;

     int rows = qTable.size();
     int cols = qTable[0].size();

     file<<std::to_string(rows)<<std::endl;
     file<<std::to_string(cols)<<std::endl;

     for (auto& row : qTable) {
         for (int i = 0; i < cols; i++) {
             file << std::to_string(row[i]);

             if (i < cols - 1) {
                 file << ",";
             }
         }
         file << std::endl;

     }

     file.close();

}

void AIModel::loadFile() {
     std::ifstream file(fileName);
     if (!file.is_open()) {
         std::cerr << "Could not open file for loading: " << fileName << std::endl;
         return;
     }

     std::string line;

     std::getline(file, line);
     alpha = std::stod(line);

     std::getline(file, line);
     gamma = std::stod(line);

     std::getline(file, line);
     epsilon = std::stod(line);

     std::getline(file, line);
     int rows = std::stoi(line);

     std::getline(file, line);
     int cols = std::stoi(line);

     qTable.resize(rows, std::vector<double>(cols));

     for (int r = 0; r < rows; r++) {
         if (!std::getline(file, line)) {
             std::cerr << "Error reading Q-table row " << r << std::endl;
             break;
         }

         std::vector<std::string> values;
         size_t pos = 0;
         std::string token;
         std::string delimiter = ",";

         while ((pos = line.find(delimiter)) != std::string::npos) {
             token = line.substr(0, pos);
             values.push_back(token);
             line.erase(0, pos + delimiter.length());
         }
         values.push_back(line);

         for (int c = 0; c < cols && c < values.size(); c++) {
             qTable[r][c] = std::stod(values[c]);
         }
     }

     file.close();
}


int AIModel::getStateID(std::vector<double> &state) {
     position = static_cast<int>(state[0] * 5);
     handStrength = static_cast<int>(state[1] * 10);
     potRatio = static_cast<int>(state[2] * 5);

     return position + (handStrength * 5) + (potRatio * 50);

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
     potRatio = state[2];

     switch(action) {
         case 2: // FOLD
             if (handStrength < 0.2) {
                 baseReward = 0.1;
                 }
             else if (handStrength > 0.4) {
                baseReward = -1.0;
             }
             else if (position < 0.3 && potRatio < 0.3) {
                baseReward = 0.05;
             }
             else {
                 baseReward = -0.3;
             }

         break;

         case 1: // RAISE
             if (handStrength > 0.6) {
                 baseReward = 1.0;
             }
             else if (handStrength > 0.4 && potRatio>0.5) {
                 baseReward = 0.5;
             }
             else if (handStrength > 0.3 && potRatio>0.4) {
                 baseReward = 0.3;
             }
             else if (handStrength > 0.3 && position > 0.4) {
                 baseReward = 0.2;
             }
             else {
                 baseReward = -1.0;
             }

             break;

         case 0: // CALL/CHECK
             if (handStrength > 0.3) {
                 baseReward = 0.4;
             }
             else if (handStrength >0.2 ) {
                 baseReward = 0.2;
             }
             else if (handStrength < 0.3 && (potRatio>0.4 || position>0.4)) {
                 baseReward = 0.4;
             }
             else {

             }
             break;
     }

     // Add slight randomness to encourage exploration
     return baseReward + ((static_cast<double>(rand()) / RAND_MAX) - 0.5) * 0.1;

}





