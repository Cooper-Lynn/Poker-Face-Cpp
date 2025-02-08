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

int HandReader::valueHand(){
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

  for (auto& [suit, count] : suitCount){
      if (count>5){
        flush = true;
        break;
      }
  }
  for (auto& [rank, count] : rankCount){
      ranks.push_back(rank);
  }
  std::sort(ranks.begin(), ranks.end());

  for (int i= 1; i < ranks.size(); i++){
    if (ranks[i] == ranks[i-1]+1){
      consecutive++;
      if (consecutive > 5){
            straight = true;
      }
    }
    else{
          consecutive = 1;
      }
  }
  for (auto& [rank, count] : rankCount){
    if (count==4){
        fourKind++;
    }
    if (count ==3){
        threeKind++;
    }
    if (count ==2){
        pairs++;
    }
  }
  if (flush && straight) return 10; // Straight Flush
        if (fourKind) return 8;        // Four of a Kind
        if (threeKind && pairs) return 7; // Full House
        if (flush) return 6;              // Flush
        if (straight) return 5;           // Straight
        if (threeKind) return 4;       // Three of a Kind
        if (pairs >= 2) return 3;         // Two Pair
        if (pairs == 1) return 2;         // One Pair
        return 1;                         // High Card



}