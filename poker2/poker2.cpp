#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

enum Suit {
    SPADES,
    HEARTS,
    DIAMONDS,
    CLUBS
};

struct Card {
    Suit suit;
    int value;
};

class PokerGame {
private:
    vector<Card> deck;
    vector<Card> playerHand;
    vector<Card> computerHand;

public:
    PokerGame() {
        initializeDeck();
        shuffleDeck();
        dealInitialCards();
    }

    void initializeDeck() {
        for (int suit = SPADES; suit <= CLUBS; ++suit) {
            for (int value = 2; value <= 14; ++value) {
                deck.push_back({ static_cast<Suit>(suit), value });
            }
        }
    }

    void shuffleDeck() {
        srand(static_cast<unsigned int>(time(0)));
        random_shuffle(deck.begin(), deck.end());
    }

    void dealInitialCards() {
        for (int i = 0; i < 5; ++i) {
            playerHand.push_back(deck.back());
            deck.pop_back();

            computerHand.push_back(deck.back());
            deck.pop_back();
        }
    }

    void displayHand(const vector<Card>& hand) {
        for (const auto& card : hand) {
            cout << getSuitSymbol(card.suit) << card.value << " ";
        }
       cout << endl;
    }

    char getSuitSymbol(Suit suit) {
        switch (suit) {
        case SPADES:
            return 'S';
        case HEARTS:
            return 'H';
        case DIAMONDS:
            return 'D';
        case CLUBS:
            return 'C';
        default:
            return '?';
        }
    }

    void discardAndDraw() {
        int discardCount;
        cout << "How many cards do you throw away?: ";
        cin >> discardCount;

        for (int i = 0; i < discardCount; ++i) {
            int cardIndex;
            cout << "How many do you throw away? (0-4): ";
            cin >> cardIndex;

            playerHand[cardIndex] = deck.back();
            deck.pop_back();
        }
    }

    bool isFlush(const vector<Card>& hand) {
        Suit firstSuit = hand[0].suit;
        for (const auto& card : hand) {
            if (card.suit != firstSuit) {
                return false;
            }
        }
        return true;
    }

    bool isStraight(const vector<Card>& hand) {
        vector<int> values;
        for (const auto& card : hand) {
            values.push_back(card.value);
        }
        sort(values.begin(), values.end());

        for (size_t i = 1; i < values.size(); ++i) {
            if (values[i] != values[i - 1] + 1) {
                return false;
            }
        }
        return true;
    }

    bool hasPair(const vector<Card>& hand) {
        vector<int> valueCounts(15, 0);

        for (const auto& card : hand) {
            valueCounts[card.value]++;
        }

        for (int count : valueCounts) {
            if (count == 2) {
                return true;
            }
        }

        return false;
    }

    bool hasTwoPair(const vector<Card>& hand) {
        vector<int> valueCounts(15, 0);
        int pairCount = 0;

        for (const auto& card : hand) {
            valueCounts[card.value]++;
        }

        for (int count : valueCounts) {
            if (count == 2) {
                pairCount++;
            }
        }

        return pairCount == 2;
    }

    void evaluateHand() {
        if (isFlush(playerHand) && isStraight(playerHand)) {
            cout << "Straight Flush!" << endl;
        }
        else if (isFlush(playerHand)) {
            cout << "Flush!" << endl;
        }
        else if (isStraight(playerHand)) {
            cout << "Straight!" << endl;
        }
        else if (hasTwoPair(playerHand)) {
            cout << "Two Pair!" << endl;
        }
        else if (hasPair(playerHand)) {
            cout << "One Pair!" << endl;
        }
        else {
            cout << "High Card!" << endl;
        }
    }

    void play() {
        while (true) {
            cout << "Your hand: ";
            displayHand(playerHand);

            discardAndDraw();

            cout << "Your new hand: ";
            displayHand(playerHand);

            evaluateHand();

        }
    }
};

int main() {
    PokerGame game;
    game.play();

    return 0;
}
