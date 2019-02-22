#include<vector>
#include<iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    cin.ignore();
    string line;
    getline(cin, line);
    for(int tn = 0; tn < t; tn++){
        int n;
        cin >> n;
        // d - deck and nd - new deck.
        vector<int> d(52), nd(52);
        // initialize deck
        for(int i=0;i<52;i++){
            d[i] = i;
        }
        // permutation
        vector<int> p(52);
        vector<vector<int> > ps;
        for(int k=0;k<n;k++){
            for(int i=0;i<52;i++){
                int j;
                cin >> j;
                p[i] = j - 1;
            }
            ps.push_back(p);
        }
        // several lines of input that means which shuffle was used.
        cin.ignore();
        while(true){
            string line;
            getline(cin, line);
            if(line == ""){
                // if not the first write an space before output
                if(tn != 0) {
                    cout << endl;
                }
                for(int i=0;i<52;i++){
                    vector<string> values = {"2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};
                    vector<string> suites = {"Clubs","Diamonds","Hearts","Spades"};
                    // cout << d[i] << " ";
                    cout  << values[d[i] % 13] + " of " + suites[d[i] / 13] << endl;
                }
                break;
            }
            int permutationNumber = stoi(line) - 1;
            for(int i=0;i<52;i++){
                int j = ps[permutationNumber][i];
                nd[i] = d[j];
            }
            for(int i=0;i<52;i++){
                d[i] = nd[i];
            }
        }
    }
}