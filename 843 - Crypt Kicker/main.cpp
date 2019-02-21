#include<functional>
#include<iostream>
#include<sstream>
#include<iterator>
#include<map>
#include<vector>
#include<set>
using namespace std;
vector<string> split(string str){
    istringstream ss(str);
    return vector<string>(istream_iterator<string>{ss}, istream_iterator<string>());
}
bool checkMatchings(map<char, char>& matchings, vector<string>& encrypted, set<string> dictionarySet,  set<char> hasMatchings){
    // well how to check the fact that the matchings are pointing at the same thing twice?
    if(matchings.size() != hasMatchings.size()) return false;
    bool rightMatchings = true;
    // decrypt phrase and check if the word exists in dictionary
    for(auto& word: encrypted){
        // for every word create new ostringstream
        ostringstream ss;
        for(auto& letter: word){
            ss << matchings[letter];
        }
        if(!dictionarySet.count(ss.str())){
            return false;
        }
    }
    return rightMatchings;
}
int main(){
    int n;
    cin >> n;
    vector<string> dictionary;
    for(int i=0;i<n;i++){
        string word;
        cin >> word;
        dictionary.push_back(word);
    }
    set<string> dictionarySet(dictionary.begin(), dictionary.end());
    cin.ignore();
    while(true){
        string line;
        getline(cin, line);
        if(line == "") break;
        auto encrypted = split(line);
        // it should be full search!
        // we should have reversible matchings
        map<char, char> matchings;
        set<char> hasMatchings;
        function<bool(int)> search = [&encrypted, &matchings, &dictionary, &search, &dictionarySet, &hasMatchings](int currentWord){
            if(currentWord == encrypted.size()){
                return checkMatchings(matchings, encrypted, dictionarySet, hasMatchings);
            }
            for(auto& word : dictionary){
                if(word.size() == encrypted[currentWord].size()){
                    // cool we found the word in dictionary with same size
                    // we check if all matchings are consistent with hypothesis that is the right word
                    bool consistant = true;
                    for(int i=0; (i<word.size()) && consistant;i++){ // 8
                        char letter = encrypted[currentWord][i];
                        if(matchings.count(letter) && matchings[letter] != word[i] || !matchings.count(letter) && hasMatchings.count(word[i])) {
                            consistant = false;
                        }
                    }
                    if(!consistant) continue;
                    // if consistant we check the letters that weren't in matchings and add them, 
                    // also write them to the list that will be used when we remove them from matchings in case when no matching is found.
                    vector<char> newLetters;
                    for(int i=0; i<word.size();i++){ // 8
                        char letter = encrypted[currentWord][i];
                        if(!matchings.count(letter)){
                            newLetters.push_back(letter);
                            matchings[letter] = word[i];
                            hasMatchings.insert(word[i]);
                        }
                    }
                    // after adding new matchings we need to check if there are enough matching to do decryption
                    // hypothesis that it is right matchings.
                    bool weDoNotNeedToSearchMore = false;
                    if(hasMatchings.size() == 26 && checkMatchings(matchings, encrypted, dictionarySet, hasMatchings)){
                        return true;
                    }
                    // so let's move to the next word and hope for the best
                    if(search(currentWord + 1)) {
                        return true;
                    }
                    // well if we came here there must be a misstake in this try so what we do 
                    // we backtrack things we did, remove matchings that was added.
                    for(char& letter: newLetters){
                        // and move on to the next word that is consistant.
                        hasMatchings.erase(matchings[letter]);
                        matchings.erase(letter);
                    }
                }
            }
            return false;
        };
        bool res = search(0);
        for(int i=0;i<encrypted.size();i++){
            auto& word = encrypted[i];
            for(auto& letter: word){
                if(res){
                cout << matchings[letter];
                } else {
                    cout << '*';
                }
            }
            if(i != encrypted.size() - 1) {
                cout << ' ';
            }
        }
        cout << endl;
    }
}