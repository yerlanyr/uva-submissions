#include<sstream>
#include<iterator>
#include<functional> 
#include<map>
#include<cassert>
#include<iostream>
#include<vector>
#include<set>
#include<cmath>
using namespace std;
map<int,int> getCount(vector<int> cube){
    map<int,int> count;
    for(int x:cube){
        count[x]++;
    }
    return count;
}
int ofAKind(int i,vector<int> cube, int res){
    auto count = getCount(cube);
    for(auto x: count){
        if(x.second >=i) return res;
    }
    return 0;
}
int longestSequence(vector<int> cube){
    auto count = getCount(cube);
    int len = 1;
    int maxLen = 0;
    for(int i=1;i<6;i++){
        if(count.count(i) && count.count(i+1)){
            len ++;
            maxLen = max(len, maxLen);
        } else {
            len = 1;
        }
    }
    return maxLen;
}
int getScore(int category, vector<int> cube){
    int res = 0;
    switch(category){
        case 6:
            for(int x: cube){
                res += x;
            }
            return res;
        case 7:
            return ofAKind(3, cube, getScore(6, cube));
        case 8:
            return ofAKind(4, cube, getScore(6, cube));
        case 9:
            return ofAKind(5, cube, 50);
        case 10:
            if(longestSequence(cube) >= 4) return 25;
            else return 0;
        case 11: 
            if(longestSequence(cube) >= 5) return 35;
            else return 0;
        case 12:
        {
            auto count = getCount(cube);
            bool hasThree = false, hasFive= false, hasTwo= false;
            for(auto x: count){
                if(x.second == 2) hasTwo = true;
                if(x.second == 3) hasThree = true;
                if(x.second == 5) hasFive = true;
            }
            if((hasTwo && hasThree) || hasFive) return 40;
            return 0;
        }
        default: // 0 - 5
            for(int x: cube){
                if(x == (category + 1)){
                    res += x;
                }
            }
            return res;
        
    }
}
vector<int> getHighestScore(vector<vector<int> > cubes){
    map<pair<int, int>, vector<int> > memo;
    vector<vector<int> > ratings(13,vector<int>(13, 0));
    for(int cubeI=0;cubeI<13;cubeI++){
        for(int categoryI = 0; categoryI < 13; categoryI++){
            ratings[cubeI][categoryI] = getScore(categoryI, cubes[cubeI]);
        }
    }
    function<vector<int>(int, int)> subProblema = [&](int cubesLeft, int category){
        auto key = make_pair(cubesLeft, category);
        if(memo.count(key)){
            return memo[key];
        }
        if(category == 0){
            vector<int> score(15,0);
            score[0] = ratings[(int)log2(cubesLeft)][0];
            score[14] = score[0];
            return score;
        }
        vector<int> maxScore(15,0);
        for(int i=0;i<13;i++){
            if(0 == (cubesLeft & (1<<i))){
                continue;
            }
            auto subScore = subProblema(cubesLeft ^ (1<<i), category - 1);
            subScore[category] = ratings[i][category];
            subScore[14] += ratings[i][category];
            if(category == 5 && subScore[14] >= 63){
                subScore[13] = 35;
                subScore[14] += subScore[13];
            }
            if(maxScore[14] < subScore[14]){
                maxScore = subScore;
            } 
        }
        memo[key] = maxScore;
        return maxScore;
    };
    return subProblema(((1<<13) - 1), 12);
}
int main(){
    int t = 0;
    cin >> t;
    cin.ignore();
    string line;
    vector<vector<int> > cubes;
    while(true){
        getline(cin, line);
        if(line == "") break;
        istringstream ss(line);
        vector<int> cube(5);
        for(int i=0;i<5;i++) ss >> cube[i];
        cubes.push_back(cube);
        if(cubes.size() == 13){
            bool first = true;
            ostringstream result;
            ostream_iterator<int> oit(result, " ");
            auto highestScore = getHighestScore(cubes);
            copy(highestScore.begin(), highestScore.end(), oit);
            cout << result.str().substr(0, result.str().length() - 1) << endl;
            cubes.clear();
        }
    }
}