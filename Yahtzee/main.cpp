#include<sstream>
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
   /* assert(getScore(0, {1,2,1,1,2}) == 3);
    assert(getScore(1, {1,2,1,1,2}) == 4);
    assert(getScore(2, {1,2,1,1,2}) == 0);
    assert(getScore(2, {1,2,3,1,3}) == 6);
    assert(getScore(4, {1,2,5,1,2}) == 5);
    assert(getScore(5, {1,2,6,6,2}) == 12);
    assert(getScore(6, {1,2,1,1,2}) == 7);
    assert(getScore(7, {1,1,1,2,3}) == getScore(6, {1,1,1,2,3}));
    assert(getScore(7, {1,1,2,2,3}) == 0);
    assert(getScore(8, {1,1,1,1,3}) == getScore(6, {1,1,1,1,3}));
    assert(getScore(8, {1,1,2,2,3}) == 0);
    assert(getScore(9, {1,1,1,1,1}) == 50);
    assert(getScore(9, {1,1,2,1,1}) == 0);
    assert(getScore(10, {1,2,3,4,1}) == 25);
    assert(getScore(10, {1,2,3,3,1}) == 0);
    assert(getScore(11, {1,2,3,4,5}) == 35);
    assert(getScore(11, {1,2,3,3,1}) == 0);
    assert(getScore(12, {1,1,3,3,1}) == 40);
    assert(getScore(12, {1,1,1,1,1}) == 40);
    assert(getScore(12, {2,1,1,1,1}) == 0);
    assert(getCount({1,2,3,5,5})[5] == 2);
    vector<vector<int> > cubes = {
        {1, 1, 1, 1, 1},
        {6, 6, 6, 6, 6},
        {6, 6, 6, 1, 1},
        {1, 1, 1, 2, 2},
        {1, 1, 1, 2, 3},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 6},
        {6, 1, 2, 6, 6},
        {1, 4, 5, 5, 5},
        {5, 5, 5, 5, 6},
        {4, 4, 4, 5, 6},
        {3, 1, 3, 6, 3},
        {2, 2, 2, 4, 6}
    };
    auto res = getHighestScore(cubes);
    vector<int> exp = {3, 6, 9, 12, 15, 30, 21, 20, 26, 50, 25, 35, 40, 35, 327};
    for(int i=0;i<res.size();i++){
        cout << res[i] << ' ';
    }
    assert(res == exp);*/
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
            for(auto x : getHighestScore(cubes)){
                cout << x << ' ';
            }
            cout << endl;
            cubes.clear();
        }
    }
}