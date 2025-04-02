//
// Created by coope on 28/01/2025.
//
#include "HandReader.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_set>

HandReader::HandReader(std::vector<std::string> playerHand, std::vector<std::string> communityCards) {
    this->playerHand = playerHand;
    this->communityCards = communityCards;
}

HandReader::~HandReader() = default;


char HandReader::getSuit(std::string &card) {
    return card[0];
}

int HandReader::getRank(std::string &card) {
    rankString = card.substr(1);
    if (rankString == "1") {
        rankString = "14";
    }
    return std::stoi(rankString);
}


bool HandReader::isRoyalFlush(std::vector<std::string> &cards) {
    if (cards.size() < 5) return false;

    char constantSuit = getSuit(cards[0]);
    for (auto &card: cards) {
        if (getSuit(card) != constantSuit) return false;
    }

    std::sort(ranks.begin(), ranks.end(), std::greater<int>());
    return std::equal(ranks.begin(), ranks.begin() + 5, royalRanks.begin());
}

bool HandReader::isStraightFlush() {
    flushRanks.clear();
    if (!isFlush(flushCards)) return false;

    for (auto &card: flushCards) {
        flushRanks.push_back(getRank(card));
    }

    std::sort(flushRanks.begin(), flushRanks.end());

    if (!isStraight(flushRanks)) {
        return false;
    }
    straightFlushCards = straightCards;
    return true;
}


/*
 * this helper function is used to determine the best flush in a hand
 * flush is when the hand contains 5 cards of same suit
 */
bool HandReader::isFlush(std::vector<std::string> &flushCards) {
    for (auto &[suit, cards]: suitToCard) {
        if (cards.size() >= 5) {
            flushCards = cards;
            std::sort(flushCards.begin(), flushCards.end(),
                      [this](std::string &card1, std::string &card2) {
                          return getRank(card1) < getRank(card2);
                      });
            return true;
        }
    }
    return false;
}

/*
 * this helper function is used to determine if there is 5 consecutive cards
 */
bool HandReader::isStraight(std::vector<int> &ranks) {
    if (ranks.size() < 5) return false;

    compareRanks = ranks;

    if (ranks.back() == 14) {
        compareRanks.insert(compareRanks.begin(), 1);
    }

    int consecutive = 1;
    std::sort(compareRanks.begin(), compareRanks.end());

    for (int i = 1; i < compareRanks.size(); i++) {
        if (compareRanks[i] == compareRanks[i - 1] + 1) {
            consecutive++;


            if (consecutive == 5) {
                int startRank = compareRanks[i] - 4;
                int endRank = compareRanks[i];

                if (startRank == 1) {
                    endRank = 5;
                    startRank = 14;
                }

                straightCards.clear();
                for (auto &card: totalCards) {
                    int rank = getRank(card);
                    if ((rank >= startRank && rank <= endRank) ||
                        (rank == 14 && rank <= 5)) {
                        straightCards.push_back(card);
                    }
                }
                return true;
            }
        } else if (compareRanks[i] != compareRanks[i - 1]) {
            consecutive = 1;
        }
    }
    return false;
}

void HandReader::countCards(std::vector<std::string> &totalCards) {
    returnCards.clear();
    ranks.clear();
    rankCount.clear();
    suitCount.clear();
    tempConsecCards.clear();
    pairReturnCards.clear();
    tripReturnCards.clear();
    quadReturnCards.clear();
    flushCards.clear();
    straightCards.clear();
    straightFlushCards.clear();
    predFlush = false;
    predRoyal = false;
    predStraight = false;
    predStraightFlush = false;
    straight = false;
    flush = false;


    for (auto &card: totalCards) {
        int rank = getRank(card);
        char suit = getSuit(card);
        rankCount[rank]++;
        suitCount[suit]++;
    }

    for (auto &card: totalCards) {
        suitToCard[getSuit(card)].push_back(card);
    }

    for (auto &[rank, count]: rankCount) {
        ranks.push_back(rank);
    }
    std::sort(ranks.begin(), ranks.end());
}

std::pair<double, std::vector<std::string> > HandReader::valueHand() {
    totalCards = communityCards;
    totalCards.insert(totalCards.end(), playerHand.begin(), playerHand.end());

    countCards(totalCards);

    int fourKind = 0, threeKind = 0, pairs = 0;

    for (auto &[rank, count]: rankCount) {
        if (count == 4) {
            fourKind++;
            for (auto &card: totalCards) {
                if (getRank(card) == rank) {
                    quadReturnCards.push_back(card);
                }
            }
        }

        if (count == 3) {
            threeKind++;
            for (auto &card: totalCards) {
                if (getRank(card) == rank) {
                    tripReturnCards.push_back(card);
                }
            }
        }

        if (count == 2) {
            pairs++;
            for (auto &card: totalCards) {
                if (getRank(card) == rank) {
                    pairReturnCards.push_back(card);
                }
            }
        }
    }

    if (isFlush(flushCards)) {
        if (isRoyalFlush(flushCards)) {
            if (std::find(skipStrength.begin(), skipStrength.end(), 10) == skipStrength.end()) {
                return std::make_pair(10, std::vector<std::string>(flushCards.end() - 5, flushCards.end()));
            }
        }
        if (isStraightFlush()) {
            if (std::find(skipStrength.begin(), skipStrength.end(), 9) == skipStrength.end()) {
                return std::make_pair(9, straightFlushCards);
            }
        }
        if (std::find(skipStrength.begin(), skipStrength.end(), 6) == skipStrength.end()) {
            return std::make_pair(6, flushCards);
        }
    }
    if (isStraight(ranks)) {
        if (std::find(skipStrength.begin(), skipStrength.end(), 5) == skipStrength.end()) {
            return std::make_pair(5, returnCards);
        }
    }


    if (fourKind) {
        if (std::find(skipStrength.begin(), skipStrength.end(), 8) == skipStrength.end()) {
            return std::make_pair(8, quadReturnCards); // Four of a Kind
        }
    }

    if (threeKind && pairs) {
        returnCards = tripReturnCards;
        returnCards.insert(returnCards.end(), pairReturnCards.begin(), pairReturnCards.end());
        if (std::find(skipStrength.begin(), skipStrength.end(), 7) == skipStrength.end()) {
            return std::make_pair(7, returnCards); // Full House
        }
    }

    if (threeKind) {
        if (std::find(skipStrength.begin(), skipStrength.end(), 4) == skipStrength.end()) {
            return std::make_pair(4, tripReturnCards); // Three of a Kind
        }
    }

    if (pairs >= 2) {
        if (std::find(skipStrength.begin(), skipStrength.end(), 3) == skipStrength.end()) {
            return std::make_pair(3, pairReturnCards); // Two Pair
        }
    }
    if (pairs == 1) {
        if (std::find(skipStrength.begin(), skipStrength.end(), 2) == skipStrength.end()) {
            return std::make_pair(2, pairReturnCards); // One Pair
        }
    }

    // High Card
    if (returnCards.empty()) {
        for (auto &card: totalCards) {
            if (getRank(card) == rankCount.rbegin()->first) {
                returnCards.push_back(card);
                break;
            }
        }

        return std::make_pair(1, returnCards);
    }
}


void HandReader::updateHands(std::vector<std::string> playerCards, std::vector<std::string> communityCards) {
    this->playerHand = playerCards;
    this->communityCards = communityCards;
    skipStrength.clear();
}


double HandReader::predictWorth() {
    totalCards = communityCards;
    totalCards.insert(totalCards.end(), playerHand.begin(), playerHand.end());
    countCards(totalCards);

    for (auto &[suit, cards] : suitToCard) {
        flushCards = cards;
        std::sort(flushCards.begin(), flushCards.end(),
                  [this](std::string &card1, std::string &card2) {
                      return getRank(card1) < getRank(card2);
                  });
        if (flushCards.size() >= 3) {
            predFlush = true;
        }
    }

    compareRanks = ranks;

    if (ranks.back() == 14) {
        compareRanks.push_back(1);
    }
    std::sort(compareRanks.begin(), compareRanks.end());

    consecutive = 1;

    for (int i = 1; i < compareRanks.size(); i++) {
        if (compareRanks[i] == compareRanks[i - 1] + 1) {
            consecutive++;
            if (consecutive == 3) {
                int startRank = compareRanks[i] - 4;
                int endRank = compareRanks[i];
                if (startRank == 1) {
                    endRank = 5;
                    startRank = 14;
                }
                straightCards.clear();
                for (auto &card : totalCards) {
                    int rank = getRank(card);
                    if ((rank >= startRank && rank <= endRank) || (rank == 14 && endRank == 5)) {
                        straightCards.push_back(card);
                    }
                }
                straight = true;
            }
        } else if (compareRanks[i] != compareRanks[i - 1]) {
            consecutive = 1;
        }
    }

    if (straight && predFlush) {
        predStraightFlush = true;
    }

    std::unordered_set<int> uniqueRoyalCards;

    for (auto ranks : rankCount) {
        if(ranks.first >=10 && ranks.second >=1) {
            uniqueRoyalCards.insert(ranks.first);
        }

    }
    int predRoyalCount = uniqueRoyalCards.size();

    if (predRoyalCount >= 3  && predStraightFlush) {
        predRoyal = true;
    }



    if (predRoyal) {
        return 10;
    }
    if (predStraightFlush) {
        return 9;
    }
    if (predFlush) {
        return 6;
    }
    if (straight) {
        return 5;
    }

    return 0;
}



std::pair<double, std::vector<std::string> > HandReader::tieBreaker(double matching) {
    skipStrength.push_back(matching);
    return valueHand();
}
