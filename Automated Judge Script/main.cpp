#include<vector>
#include<cctype>
#include<iostream>
#include<sstream>

using namespace std;
string getLines(){
    vector<string> res;
    ostringstream ss;
    int k;
    cin >> k;
    for(int i=0;i<k;i++)
    {
        string str;
        getline(cin, str);
        res.push_back(str);
        cin.ignore();
    }
    return ss.str();
}
long long addToHash(long long currentHash, char ch){
    long long p = 1000969;
    long long z = 283;
    return ((int)ch % z + currentHash * z) % p;
}
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
        long long cnh=0, snh=0, cuh=0, suh=0, coh = 0, soh = 0; // correct/solution number/unumeric hashes
        for(int i=0;i<k;i++)
        {
            string str;
            getline(cin, str);
            for(char ch: str)
            {
                coh = addToHash(coh, ch);
                if(isdigit(ch))
                {
                    cnh = addToHash(cnh, ch);
                } else { 
                    cuh = addToHash(cuh, ch);
                }
            }

            cuh = addToHash(cuh, '\n');
            coh = addToHash(coh, '\n');
        }
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
            for(char ch: str)
            {
                soh = addToHash(soh, ch);

                if(isdigit(ch))
                {
                    snh = addToHash(snh, ch);
                } 
                else 
                { 
                    suh = addToHash(suh, ch);
                }
            }
            soh = addToHash(soh, '\n');
            suh = addToHash(suh, '\n');
        }
        if(soh == coh && suh == cuh && snh == cnh){
            cout << "Run #" << n << ": Accepted"<< endl;
        } else if (snh == cnh){
            cout << "Run #" << n << ": Presentation Error"<< endl;
        } else {
            cout << "Run #" << n << ": Wrong Answer" << endl;
        }
    }
}