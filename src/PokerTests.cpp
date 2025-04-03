//
// Created by coope on 01/04/2025.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "HandReader.hpp"
#include "GameRunner.hpp"
#include "Player.hpp"

TEST_CASE("GameRunner, Card Detail gives correct card details", "[CARD LOGIC]") {
    std::vector<std::unique_ptr<Player> > players;
    std::string name = "player1";
    players.push_back(std::make_unique<UserPlayer>(name));
    std::vector<std::string> currentDeck;
    GameRunner game_runner(1, players, currentDeck);
    std::string card = "s1";
    std::pair<std::string, std::string> result = game_runner.cardDetail(card);

    REQUIRE(result.first == "Spades");
    REQUIRE(result.second == "Ace");
}

TEST_CASE("GameRunner, Hand Detail gives correct hand details", "[CARD LOGIC]") {
    std::vector<std::unique_ptr<Player> > players;
    std::string name = "player1";
    players.push_back(std::make_unique<UserPlayer>(name));

    std::vector<std::string> currentDeck;
    std::unique_ptr<GameRunner> gameRunner = std::make_unique<GameRunner>(1, players, currentDeck);
    std::string card = "s1";
    std::string card2 = "d13";

    std::vector<std::string> hand;
    hand.push_back(card);
    hand.push_back(card2);

    std::vector<std::string> detailHand = gameRunner->handDetail(hand);

    REQUIRE(detailHand.size() == 2);
}

TEST_CASE("GameRunner, Give 2 cards to a player using .giveHandsToPlayer", "[CARD LOGIC]") {
    std::vector<std::unique_ptr<Player> > players;
    std::vector<std::string> currentDeck;
    std::string name = "player1";
    players.push_back(std::make_unique<UserPlayer>(name));

    GameRunner game_runner(1, players, currentDeck);
    currentDeck = game_runner.createDeck();
    game_runner.setCurrentDeck(currentDeck);

    game_runner.giveHandsToPlayers();
    players = game_runner.getPlayers();

    std::vector<std::string> playerHand = players[0]->getHand();

    REQUIRE(playerHand.size() == 2);
}

TEST_CASE("HandReader, test for every strength", "[HAND LOGIC]") {
    SECTION("Royal Flush") {
        std::vector<std::string> playerHand = {"s10", "s1"};
        std::vector<std::string> communityCards = {"s11", "s12", "s13", "d2", "c5"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 10);
    }

    SECTION("Straight Flush") {
        std::vector<std::string> playerHand = {"d8", "d9"};
        std::vector<std::string> communityCards = {"d10", "d11", "d12", "s4", "c3"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 9);
    }

    SECTION("Four of a Kind") {
        std::vector<std::string> playerHand = {"h7", "s7"};
        std::vector<std::string> communityCards = {"d7", "c7", "h9", "d2", "s3"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 8);
    }

    SECTION("Full House") {
        std::vector<std::string> playerHand = {"c6", "d6"};
        std::vector<std::string> communityCards = {"h6", "s9", "c9", "s1", "s12"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 7);
    }

    SECTION("Flush") {
        std::vector<std::string> playerHand = {"s3", "s8"};
        std::vector<std::string> communityCards = {"s11", "s12", "s6"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 6);
    }

    SECTION("Straight") {
        std::vector<std::string> playerHand = {"c4", "s5"};
        std::vector<std::string> communityCards = {"h6", "d7", "s8"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 5);
    }

    SECTION("Three of a Kind") {
        std::vector<std::string> playerHand = {"s2", "h2"};
        std::vector<std::string> communityCards = {"d2", "c9", "s10"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 4);
    }

    SECTION("Two Pair") {
        std::vector<std::string> playerHand = {"c5", "s5"};
        std::vector<std::string> communityCards = {"h9", "d9", "s3"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 3);
    }

    SECTION("One Pair") {
        std::vector<std::string> playerHand = {"h8", "s8"};
        std::vector<std::string> communityCards = {"d10", "c6", "s7"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 2);
    }

    SECTION("High Card") {
        std::vector<std::string> playerHand = {"s2", "h7"};
        std::vector<std::string> communityCards = {"d10", "c6", "s9"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.valueHand();
        REQUIRE(result.first == 1);
    }
}

TEST_CASE("HandReader, test for every prediction", "[HAND LOGIC]") {
    SECTION("Royal Flush") {
        std::vector<std::string> playerHand = {"s10", "s1"};
        std::vector<std::string> communityCards = {"s11", "s12"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.predictWorth();
        REQUIRE(result == 10);
    }

    SECTION("Straight Flush") {
        std::vector<std::string> playerHand = {"d8", "d9"};
        std::vector<std::string> communityCards = {"d7"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.predictWorth();
        REQUIRE(result == 9);
    }


    SECTION("Flush") {
        std::vector<std::string> playerHand = {"s2"};
        std::vector<std::string> communityCards = {"s11", "s7"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.predictWorth();
        REQUIRE(result == 6);
    }

    SECTION("Straight") {
        std::vector<std::string> playerHand = {"c4", "s5"};
        std::vector<std::string> communityCards = {"h6", "d7"};
        HandReader handReader(playerHand, communityCards);
        auto result = handReader.predictWorth();
        REQUIRE(result == 5);
    }
}

TEST_CASE("", "") {
}
