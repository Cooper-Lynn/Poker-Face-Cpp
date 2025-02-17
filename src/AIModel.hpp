//
// Created by coope on 17/02/2025.
//

#ifndef AIMODEL_HPP
#define AIMODEL_HPP

#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#include <ctime>

class AIModel {
private:
  std::vector<std::vector<double>> qTable;
  double alpha = 0.01;
  double gamma = 0.95;
  double epsilon = 0.1;
  std::mt19937 rng;
  int games_played;
public:
  AIModel();
  ~AIModel();
  void quickTrain(int episodes);
  void learn(const std::vector<double>& state, int action, double reward,
               const std::vector<double>& next_state);
  int selectAction()
};


#endif //AIMODEL_HPP
