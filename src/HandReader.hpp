//
// Created by coope on 28/01/2025.
//

#ifndef HANDREADER_HPP
#define HANDREADER_HPP

#include <string>
#include <utility>
#include <vector>

class HandReader{
    private:
      std::vector<std::string>playerHand;
      std::vector<std::string>communityCards;
    public:
      std::string getSuit();
      std::string getRank();
      int compareRanks();
      std::string valueHand();
};
#endif //HANDREADER_HPP
