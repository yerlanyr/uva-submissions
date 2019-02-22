#include<cassert>
#include<map>
#include<set> 
#include<vector>
#include<iostream>
#include<iterator>
#include<sstream>
#include<queue>
using namespace std;
string getBeforeSemicolon(string paper){
    return paper.substr(0, paper.find(":"));
}
bool canFindTwoComas(string list){
    return string::npos != list.find(",", list.find(",")+1);
}
string removeNameFromList(string& namesList){
    string name = namesList.substr(0, namesList.find(",", namesList.find(",")+1));
    // remove the part with the name.
    namesList.erase(0, name.length() + 2);
    return name;
}
vector<string> getAuthors(string paper){
    paper = getBeforeSemicolon(paper);
    vector<string> names;
    while(canFindTwoComas(paper)){
        string name = removeNameFromList(paper);
        names.push_back(name);
    }
    names.push_back(paper);
    return names;
}
int main(){
    int s;
    cin >> s;
    for(int s_i=1;s_i <= s; s_i++){
        int P, N;
        cin >> P >> N;
        vector<string> papers, names;
        cin.ignore();
        // Get papers
        for(int i=0;i<P;i++) {
            string paper;
            getline(cin, paper);
            papers.push_back(paper);
        }
        // Get names
        for(int i=0;i<N;i++){
            string name;
            getline(cin, name);
            names.push_back(name);
        }
        // Create VE graph. And map of adjucency.
        map<string, set<string> > A;
        for(auto& paper: papers){
            auto authors = getAuthors(paper);
            for(auto& author1: authors){
                for(auto& author2: authors) {
                    if(author1 == author2) continue;
                    // create link from 1 to 2
                    A[author1].insert(author2);
                }
            }
        }
        // bfs. find the shortest path to each author
        queue<string> Q;
        map<string, int> distances = {{"Erdos, P.", 0}};
        Q.push("Erdos, P.");

        set<string> visited;
        while(!Q.empty()){
            string author = Q.front();
            Q.pop();
            if(visited.count(author)){
                continue;
            }
            visited.insert(author);
            for(auto& coauthor: A[author]){
                if(!visited.count(coauthor)){
                    Q.push(coauthor);
                    if(!distances.count(coauthor))
                        distances[coauthor] = 1 + distances[author];
                }
            }
        }
        // Now when we have all the distances let's display
        //if(s_i != 1) { cout << endl; }
        cout << "Scenario " << s_i << endl;
        for(auto& name: names){
            cout << name << " " << ( distances.count(name) ? to_string(distances[name]) : "infinity" ) << endl;
        }
    }
}