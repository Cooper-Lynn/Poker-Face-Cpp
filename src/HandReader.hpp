//
// Created by coope on 28/01/2025.
//

#ifndef HANDREADER_HPP
#define HANDREADER_HPP

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>

class HandReader{
    private:
      std::string rankString;

      std::map<int,int> rankCount;
      std::map<char,int> suitCount;
      std::unordered_map<char,std::vector<std::string>> suitToCard;

      char flushSuit;
      int flushConsecutive =0;
      int consecutive =1;
      bool isRoyal;
      bool flush;
      bool straight;

      bool predFlush;
      bool predStraight;
      bool predStraightFlush;
      bool predRoyal;

      std::vector<std::string> totalCards;
      std::vector<std::string>playerHand;
      std::vector<std::string>communityCards;
      std::vector<std::string> returnCards;
      std::vector<std::string> flushCards;
      std::vector<std::string> tempConsecCards;
      std::vector<std::string> pairReturnCards;
      std::vector<std::string> tripReturnCards;
      std::vector<std::string> quadReturnCards;
      std::vector<std::string> tempStraightFlush;
      std::vector<std::string> straightFlushCards;
      std::vector<std::string> straightCards;
      std::vector<int> royalRanks = {14, 13, 12, 11, 10};
      std::vector<int> flushRanks;
      std::vector<int> compareRanks;
      std::vector<int> ranks;

      bool isRoyalFlush(std::vector<std::string> &cards);
      bool isStraightFlush() ;
      bool isFlush(std::vector<std::string>& flushCards) ;
      bool isStraight(std::vector<int>& ranks) ;
      void countCards(std::vector<std::string>& totalCards);



    public:
      HandReader(std::vector<std::string>playerHand, std::vector<std::string>communityCards);
      ~HandReader();
      char getSuit(std::string &card);
      int getRank(std::string &card);
      std::pair<double, std::vector<std::string>> valueHand();
      void updateHands(std::vector<std::string> playerCards, std::vector<std::string> communityCards);
      double predictWorth();

};
#endif //HANDREADER_HPP
