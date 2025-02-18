//
// Created by coope on 28/01/2025.
//
#include "HandReader.hpp"
#include <iostream>
#include <algorithm>

HandReader::HandReader(std::vector<std::string>playerHand, std::vector<std::string>communityCards){
    this->playerHand = playerHand;
    this->communityCards = communityCards;
}

char HandReader::getSuit(std::string &card){
  return card[0];
}

int HandReader::getRank(std::string &card){
  rankString = card.substr(1);
  return std::stoi(rankString);
}

std::pair<int, std::vector<std::string>> HandReader::valueHand(){
  returnCards.clear();
  rankCount.clear();
  suitCount.clear();

  totalCards = communityCards;
  totalCards.insert(totalCards.end(), playerHand.begin(), playerHand.end());
  for (auto& card : totalCards){
        int rank = getRank(card);
        char suit = getSuit(card);
        rankCount[rank]++;
        suitCount[suit]++;
    }

  bool flush=false, straight = false;
  int consecutive= 1, fourKind= 0, threeKind= 0, pairs = 0;
  std::vector<int> ranks;

  for (auto& [rank, count] : rankCount){
    ranks.push_back(rank);
  }
  std::sort(ranks.begin(), ranks.end());

  for (int i= 1; i < ranks.size(); i++){
    if (ranks[i] == ranks[i-1]+1){
      consecutive++;
      if (consecutive >= 5){
        straight = true;
        for (auto& card: totalCards) {
          returnCards.push_back(card);
        }
      }
    }
    else{
      consecutive = 1;
    }
  }


  for (auto& [suit, count] : suitCount){
      if (count>=5){
        flush = true;
        for (auto& card: totalCards) {
          if (getSuit(card)==suit && returnCards.size()<=5) {
            returnCards.push_back(card);
          }
        }
        if(straight) {
          return std::make_pair(10, returnCards);
        }
        return std::make_pair(6, returnCards);
      }
  }
  if(straight) {
    return std::make_pair(5, returnCards);
  }

  for (auto& [rank, count] : rankCount) {
    if (count==4) {
      fourKind++;
      for(auto& card: totalCards) {
        if (getRank(card) == rank){
          returnCards.push_back(card);
        }
      }
    }

    if (count ==3) {
      threeKind++;
      for(auto& card: totalCards) {
        if (getRank(card) == rank){
          returnCards.push_back(card);
        }
      }
    }

    if (count ==2) {
      pairs++;
      for(auto& card: totalCards){
        if (getRank(card) == rank){
          returnCards.push_back(card);
        }
      }
    }
  }

          //if (flush && straight) std::pair(10,returnCards);     // Straight Flush

          if (fourKind) return std::make_pair(8,returnCards);        // Four of a Kind
          if (threeKind && pairs) return std::make_pair(7,returnCards); // Full House
          //if (flush) return std::make_pair(6, returnCards);              // Flush
          //if (straight) return std::make_pair(5, returnCards);           // Straight
          if (threeKind) return std::make_pair(4,returnCards);       // Three of a Kind
          if (pairs >= 2) return std::make_pair(3,returnCards);         // Two Pair
          if (pairs == 1) return std::make_pair(2,returnCards);         // One Pair

          // High Card
          if (returnCards.empty()) {
              for (auto& card: totalCards) {
                if (getRank(card) == rankCount.rbegin()->first) {
                  returnCards.push_back(card);
                  break;
                }
              }
              return std::make_pair(1, returnCards);
            }
}

