#include<cmath> 
#include<vector>
#include<sstream>
#include<iostream>
#include <iterator>
#include<algorithm>
using namespace std;

vector<string> split1(const string& str)
{
    vector<string> res;
    istringstream iss(str);
    copy(std::istream_iterator<string>(iss),
         istream_iterator<std::string>(),
         back_inserter(res));
    return res;
}

int main(){
    while(true){
        string line;
        getline(cin, line);
        if(line == "") break;
        vector<string> numbersStrs = split1(line);
        vector<int> numbers;
        auto toInt = [](string x){ return stoi(x); };
        // pop the first number
        if(numbersStrs.size() == 1) { cout << "Not jolly\n"; continue; }
        numbersStrs.erase(numbersStrs.begin());
        transform(numbersStrs.begin(), numbersStrs.end(), back_inserter(numbers), toInt);
        // generate differences.
        vector<bool> exists(numbers.size() - 1, false);
        for(int i=0, j=1;i<numbers.size() - 1; i++ ,j++){
            if(numbers[i] != numbers[j]) exists[abs(numbers[j] - numbers[i]) - 1] = true;
        }
        // any_of false
        if(any_of(exists.begin(), exists.end(), [](bool x){ return !x;})){
            cout << "Not jolly\n";
        } else {
            cout << "Jolly\n";
        }
    }
    
}