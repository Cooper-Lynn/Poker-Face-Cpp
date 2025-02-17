//
// Created by coope on 28/01/2025.
//

#ifndef HANDREADER_HPP
#define HANDREADER_HPP

#include <string>
#include <utility>
#include <vector>
#include <map>

class HandReader{
    private:
      std::vector<std::string>playerHand;
      std::vector<std::string>communityCards;
      std::string rankString;
      std::vector<std::string> totalCards;
      std::map<int,int> rankCount;
      std::map<char,int> suitCount;
    public:
      HandReader(std::vector<std::string>playerHand, std::vector<std::string>communityCards);
      ~HandReader();
      char getSuit(std::string &card);
      int getRank(std::string &card);
      std::pair<int, std::vector<std::string>> valueHand();
};
#endif //HANDREADER_HPP
