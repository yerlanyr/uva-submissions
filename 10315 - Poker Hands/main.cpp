#include<functional>
#include<map>
#include<set>
#include<iostream>
#include<vector>
#include<iterator>
#include<sstream>
#include<algorithm>
#include<utility>
using namespace std;
vector<string> split(string str){
    istringstream ss(str);
    return vector<string>(istream_iterator<string>{ss}, istream_iterator<string>());
}
const string values = "23456789TJQKA";
int getValue(char c){
    return values.find(c);
}
enum t_rank {HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH};
map<char, int> getValuesCnt(vector<string> hand){
    map<char, int> valuesCnt;
    for(auto& card: hand){
        valuesCnt[card[0]]++;
    }
    return valuesCnt;
}
t_rank getRank(vector<string> hand, map<char, int> valuesCnt){
    bool straight = true;
    for(int cur=0, next = 1;cur<4;cur++, next++){
        if(getValue(hand[next][0]) != (getValue(hand[cur][0]) + 1)) {
            straight = false;
        }
    }
    bool flush = true;
    set<char> suits;
    for(auto& card: hand) suits.insert(card[1]);
    if(suits.size() != 1) flush = false;
    vector<int> cntSorted;
    for(auto& x: valuesCnt){
        cntSorted.push_back(x.second);
    }
    sort(cntSorted.begin(), cntSorted.end());
    switch(cntSorted.size()){
        case 2: 
            return cntSorted[0] == 1 ? FOUR_OF_A_KIND: FULL_HOUSE;
        case 3:
            return cntSorted[1] == 1 ? THREE_OF_A_KIND : TWO_PAIRS;
        case 4:
            return PAIR;
        case 5:
            if(straight) return flush ? STRAIGHT_FLUSH : STRAIGHT;
            return flush ? FLUSH : HIGH_CARD;
        default: return HIGH_CARD;
    }
}
void printIsBlackWins(bool isBlackWins){
    if(isBlackWins)
        cout << "Black wins.\n";
    else cout << "White wins.\n";
}
bool valueCmp(string a, string b){
    return getValue(a[0]) < getValue(b[0]);
}
void compareHands(vector<string>& blackHand, vector<string>& whiteHand){
    while(!blackHand.empty()){
        if(blackHand.back()[0] == whiteHand.back()[0]){
            blackHand.pop_back();
            whiteHand.pop_back();
        } else {
            break;
        }
    }
    if(blackHand.empty()) {
        cout << "Tie.\n";
        return;
    }
    printIsBlackWins(getValue(blackHand.back()[0]) > getValue(whiteHand.back()[0]));
}
void removeValues(char val, vector<string>& hand) { 
    hand.resize(distance(
        hand.begin(), 
        remove_if(hand.begin(), hand.end(), [&val](string card){ return card[0] == val;})
    ));
};
int main(){
    while(true){
        string line;
        getline(cin, line);
        if(line == "") return 0;
        auto hand = split(line);
        vector<string> blackHand(hand.begin(), hand.begin() + 5);
        vector<string> whiteHand(hand.begin() + 5, hand.end());
        sort(blackHand.begin(), blackHand.end(), valueCmp);
        sort(whiteHand.begin(), whiteHand.end(), valueCmp);
        auto blackValuesCnt = getValuesCnt(blackHand);
        auto whiteValuesCnt = getValuesCnt(whiteHand);
        auto blackRank = getRank(blackHand, blackValuesCnt);
        auto whiteRank = getRank(whiteHand, whiteValuesCnt);
        if(blackRank != whiteRank){
            printIsBlackWins(blackRank > whiteRank);
        } else {
            // now we need to make the type which will have pair<card, number>
            vector<pair<string, int> > blackWeightedHand;
            vector<pair<string, int> > whiteWeightedHand;
            for(string& card : blackHand){
                blackWeightedHand.push_back(make_pair(card, blackValuesCnt[card[0]]));
            }
            for(string& card : whiteHand){
                whiteWeightedHand.push_back(make_pair(card, whiteValuesCnt[card[0]]));
            }
            function<bool(pair<string, int>,pair<string, int>)> cmp = [](pair<string, int> a, pair<string, int> b){
                if(a.second > b.second){
                    return false;
                } if(a.second < b.second){
                    return true;
                } else {
                    return valueCmp(a.first, b.first);
                }
            };
            sort(blackWeightedHand.begin(), blackWeightedHand.end(), cmp);
            sort(whiteWeightedHand.begin(), whiteWeightedHand.end(), cmp);
            for(int i=0;i<5;i++){
                blackHand[i] = blackWeightedHand[i].first;
                whiteHand[i] = whiteWeightedHand[i].first;
            }
            compareHands(blackHand, whiteHand);
        }
    }
}