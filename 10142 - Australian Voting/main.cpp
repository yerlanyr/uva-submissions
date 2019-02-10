#include<sstream>
#include<vector>
#include<iostream>
#include<queue>
#include<map>
#include<climits>
#include<set>
using namespace std;

int main(){
    int t;
    cin >> t;
    cin.get();
    while(t--){
        int n;
        cin >> n;
        vector<string> candidates;
        cin.get();
        for(int i=0;i<n;i++) {
            string name;
            getline(cin, name);
            candidates.push_back(name);
        }
        string line;
        vector<queue<int> > votes;
        while(true){
            getline(cin, line);
            if(line == "") break;
            istringstream ss(line);
            queue<int> person;
            for(int i=0;i<n;i++){
                int vote;
                ss >> vote;
                person.push(vote-1);
            }
            votes.push_back(person);
        }
        int amount = votes.size();
        // initialize non eliminated.
        set<int> nonEliminated;
        for(auto& vote: votes){
            nonEliminated.insert(vote.front());
        }
        while(true){
            // we counting currently existing votes.
            map<int, int> cnt;
            for(auto& vote: votes) if(nonEliminated.count(vote.front()))cnt[vote.front()]++;
            // determine leader
            int maxVotes = 0, maxCandidate = 0, minVotes = INT_MAX;
            for(auto& c: cnt){
                int j = c.first, v = c.second;
                minVotes = min(minVotes, v);
                if(v > maxVotes){
                    maxVotes = v;
                    maxCandidate = j;
                }
            }
            if(amount / 2 < maxVotes){
                // we know the winner!
                cout << candidates[maxCandidate] << endl;
                if(t!=0)cout << endl;
                break;
            } else if(maxVotes == minVotes){
                // we have tie!
                for(int i=0;i<n;i++){
                    if(cnt[i] == maxVotes){
                        cout << candidates[i] << endl;
                    }
                }
                if(t!=0)cout << endl;
                break;
            } else { 
                // determine losers and distribute them votes
                for(auto& c : cnt){
                    if(c.second == minVotes){
                        nonEliminated.erase(c.first);
                    }
                }
                // roll votes.
                for(auto& vote: votes){
                    while(!nonEliminated.count(vote.front())){
                        vote.pop();
                    }
                }
            }
        }
        
    }

}