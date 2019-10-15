#include<vector>
#include<cctype>
#include<iostream>
#include<sstream>
using namespace std;

long long addToHash(long long currentHash, char ch){
    // the possibility of a collision is estimated z / p ~ 0.03 %
    long long p = 1000969;
    long long z = 283;
    return ((int)ch % z + currentHash * z) % p;
}
long long evalHash(string input, bool (*predicate)(char))
{
    long long result = 0;
    for(char x : input){
        if(predicate(x)) result = addToHash(result, x);
    }
    return result;
}
bool isdigitf(char x){ return isdigit(x); }
bool isnotdigit(char x){ return !isdigit(x); }
bool truef(char x) { return true; }

int main() 
{

    string str;
    for(int n=1;;n++){
        int k;
        cin >> k;
        cin.ignore(100, '\n');
        if(k == 0) {
            break;
        }
        long long cnh=0, snh=0, cuh=0, suh=0, coh = 0, soh = 0; // correct/solution number/unumeric/overall hashes
        ostringstream ss;
        for(int i=0;i<k;i++)
        {
            string str;
            getline(cin, str);
            ss << str << endl;
        }

        cnh = evalHash(ss.str(), &isdigitf);
        cuh = evalHash(ss.str(), &isnotdigit);
        coh = evalHash(ss.str(), &truef);
        ss.str("");
        cin >> k;
        cin.ignore(100, '\n');
        if(k == 0) 
        {
            cout << "Run #" << n << ": Wrong Answer" << endl;
            break;
        }
        for(int i=0;i<k;i++)
        {
            string str;
            getline(cin, str);
            ss << str << endl;
        }
        snh = evalHash(ss.str(), &isdigitf);
        suh = evalHash(ss.str(), &isnotdigit);
        soh = evalHash(ss.str(), &truef);
        if(soh == coh && suh == cuh && snh == cnh){
            cout << "Run #" << n << ": Accepted"<< endl;
        } else if (snh == cnh){
            cout << "Run #" << n << ": Presentation Error"<< endl;
        } else {
            cout << "Run #" << n << ": Wrong Answer" << endl;
        }
    }
}