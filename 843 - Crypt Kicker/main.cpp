#include<functional>
#include<iostream>
#include<sstream>
#include<iterator>
#include<vector>
using namespace std;
vector<string> split(string str){
    istringstream ss(str);
    return vector<string>(istream_iterator<string>{ss}, istream_iterator<string>());
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
    cin.ignore();
    while(true){
        string line;
        getline(cin, line);
        if(line == "") break;
        auto encrypted = split(line);
        // it should be full search!
        // we should have reversible matchings
        map<char, char> matchings;
        function search = [&encrypted, &matchings, &dictionary](int currentWord){
            if(currentWord >= encrypted.size()){
                return; // stop search we found the matchings.
            }
            for(auto& word : dictionary){
                if(word.size() == encrypted[currentWord].size()){
                    // cool we found the word in dictionary with same size
                    // we check if all matchings are consistent with hypothesis that is the right word
                    bool consistant = true;
                    for(int i=0; (i<word.size()) && consistant;i++){
                        if(matchings.count(encrypted[i]) && matchings[encrypted[i]] != word[i]) {
                            consistant = false;
                        }
                    }
                    if(!consistant) continue;
                    // if consistant we check the letters that weren't in matchings and add them, 
                    // also write them to the list that will be used when we remove them from matchings in case when no matching is found.
                    for(int i=0; i<word.size();i++){
                        matchings[encrypted[i]] = word[i];
                    }
                }
            }
        };
    }
}