#include<sstream>
#include<vector>
#include<iostream>
#include<utility>
#include<algorithm>
#include<map>
using namespace std;
map<int, pair<int,int>> solve(vector<string>& lines, int m, int n, vector<string>& words){
    map<int, pair<int,int>> res;
    int found = 0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            vector<string> strs;
            ostringstream ss;
            // LTR
            for(int j_1 = j; j_1 < n; j_1++) ss << lines[i][j_1];
            strs.push_back(ss.str()); ss.str(""); ss.clear();
            // RTL
            for(int j_1 = j; j_1 >= 0; j_1--) ss << lines[i][j_1];
            strs.push_back(ss.str()); ss.str(""); ss.clear();
            // UTB
            for(int i_1=i;i_1<m;i_1++) ss << lines[i_1][j];
            strs.push_back(ss.str()); ss.str(""); ss.clear();
            // BTU
            for(int i_1 = i; i_1 >= 0; i_1--) ss << lines[i_1][j];
            strs.push_back(ss.str()); ss.str(""); ss.clear();
            // DRB
            for(int i_1 = i, j_1 = j; i_1 < m && j_1 < n;i_1++, j_1++ ) ss << lines[i_1][j_1];
            strs.push_back(ss.str()); ss.str(""); ss.clear();
            // DRU
            for(int i_1 = i, j_1 = j; i_1 >= 0 && j_1 < n;i_1--, j_1++ ) ss << lines[i_1][j_1];
            strs.push_back(ss.str()); ss.str(""); ss.clear();
            // DLB
            for(int i_1 = i, j_1 = j; i_1 < m && j_1 >= 0;i_1++, j_1-- ) ss << lines[i_1][j_1];
            strs.push_back(ss.str()); ss.str(""); ss.clear();
            // DRU
            for(int i_1 = i, j_1 = j; i_1 >= 0 && j_1 >= 0;i_1--, j_1-- ) ss << lines[i_1][j_1];
            strs.push_back(ss.str()); ss.str(""); ss.clear();
            // CHECK ALL THE WORDS
            for(int w_i = 0; w_i < words.size(); w_i++){
                if(found & (1 << w_i)) continue;
                // we check this word with all the strings
                for(auto& s : strs){
                    auto sFind = s.find(words[w_i]);
                    if(sFind != string::npos && sFind == 0){
                        // well we found 
                        found |= 1 << w_i;
                        res[w_i] = make_pair(i+1,j+1);
                    }
                }
            }
        }
    }
    return res;
}
int main(){
    // 50 m, n at max. 20 k words max.
    int t;
    cin >> t;
    for(int i=0;i<t;i++){
        int m, n;
        cin >> m >> n;
        vector<string> lines;
        for(int j=0;j<m;j++){
            string line;
            cin >> line;
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            lines.push_back(line);
        }
        int k;
        cin >> k;
        vector<string> words;
        for(int j=0;j<k;j++){
            string line;
            cin >> line;
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            words.push_back(line);
        }
        auto res = solve(lines, m, n, words);
        for(int j=0;j<k;j++){
            cout << res[j].first << ' ' << res[j].second << endl;
        }
        if(i != t-1){
            cout << endl;
        }
    }
}