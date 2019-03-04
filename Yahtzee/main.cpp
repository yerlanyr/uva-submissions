#include<iostream>
#include<map>
#include<algorithm>
#include<sstream>
#include<vector>
#include<functional>
#include<set>
using namespace std;
/*
 * Mutating the hell out of rating
 * It comes with cube values at first five and at the end it has all major rating it them.
 * */
void getRating(vector<int> &rating){
    vector<int> cube;
    for(int i=0;i<5;i++){
        cube.push_back(rating[i]);
    }
    map<int, int> count;
    for(auto x : cube){
        // we need to know every ranking to choose which we would use on this one.
        // first 6 values counting. ratings[0 - 5]
        rating[x - 1] += x; 
        // sum of all dice in 6th position
        rating[6] += x;
        // create count.
        count[x] += 1;
    }
    for(auto x: count){
        if(x.second >= 3){
            rating[7] += x.first * x.second;
        }
        if(x.second >= 4){
            rating[8] += x.first * x.second;
        }
        if(x.second == 5){
            rating[9] = 50;
        }
    }
    int inRow = 1;
    int maxInRow = 0;
    for(int i=2;i<=6;i++){
        if(count.count(i) && count.count(i - 1)) inRow++;
        else inRow = 1;
        maxInRow = max(maxInRow, inRow);
    }
    if(maxInRow >= 4) rating[10] = 25;
    if(maxInRow == 5) rating[11] = 35;
    // with size == 2 it could be 3 2, 4 1 to eliminate 4 of a kind possibility we check rating[8]
    if(count.size() == 2 && rating[8] == 0) rating[12] = 40;
}
vector<int> wholeScore(vector<vector<int> >& ratings, vector<int>& permutations){
    vector<int> res(15,0);
    for(int i=0;i<13;i++){
        int p = permutations[i];
        res[i] = ratings[p][i];
    }
    // what is on that 13nth and 14th
    int firstSix;
    for(int i=0;i<13;i++){
        if(i < 6) firstSix += res[i];
        res[14] += res[i];
    }
    res[13] = firstSix >= 63 ? 35 : 0;
    res[14] += res[13];
    return res;
}
int main(){
    vector<string> linesOfInput;
    vector<vector<int> > ratings(13, vector<int>(13, 0));
    string line;
    while(true){
        getline(cin, line);
        if(line == "") break;
        linesOfInput.push_back(line);
        if(linesOfInput.size() == 13){
            for(int i=0;i<13;i++){
                istringstream ss(lineToParse);
                ss >> ratings[i][0] >> ratings[i][1] >> ratings[i][2] >> ratings[i][3] >> ratings[i][4];
                getRating(ratings[i]);
            }
            /*
            cycle of optimization
            does swapping when there is a possibility to improve current score            
            */
            bool hasImprovements = false;
            vector<int> permutation;
            for(int i=0;i<13;i++) permutation.push_back(i);
            do{
                // observe to possibility of improvement.
                for(int i=0; (i + 1 < 13) && !hasImprovements;i++){
                    for(int j=i+1;j < 13 && !hasImprovements;j++){
                        // check if this combination of i and j is really improving the score.
                        int currentScore = wholeScore(ratings, permutation)[14];
                        int tmp = permutation[i];
                        permutation[i] = permutation[j];
                        permutation[j] = tmp;
                        int possibleScore = wholeScore(ratings, permutation)[14];
                        // swap back 
                         tmp = permutation[i];
                        permutation[i] = permutation[j];
                        permutation[j] = tmp;
                        if(possibleScore > currentScore){
                            hasImprovements = true;
                            // swap ratings
                            auto tmpR = ratings[i];
                            ratings[i] = ratings[j];
                            ratings[j] = tmpR;
                        }
                    }
                }
            }(hasImprovements); // if it doesn't so it must be the best permutation then the initial one.
            // cout the permutation.
            auto res = wholeScore(ratings, permutation);
            for(int i=0;i<15;i++){
                cout << res[i] << ' ';
            }
            cout << endl;
            linesOfInput.clear();
        }       
    }
}