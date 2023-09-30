/* This program is a very simple implication of checkers.
    It has the logic and functioning to run the game as well as an AI to try to beat.
    The controls involve inputting numbers to pick what piece to move and where to move it.
    This program is ran in the terminal.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

char ca = '.', one = '0', two = 'X';
const int SIZE = 8;
vector<pair<int, int>> twop{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}};
vector<pair<int, int>> onep{{7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7}};
map<pair<int, int>, char> pos;
int pick, mof, mos;
void moves(){
    
    int f = onep[pick].first - mof;
    int s = onep[pick].second + mos;
    auto itwop = find(twop.begin(), twop.end(), make_pair(f, s));
    auto ionep = find(onep.begin(), onep.end(), make_pair(f, s));
    
    if (f < 0 || f >= SIZE || s < 0 || s >= SIZE) {
        return;
    } else {
        
        if(itwop != twop.end()){
            onep[pick] = make_pair(f, s);
            twop.erase(find(twop.begin(), twop.end(), onep[pick]));
        } else {
            onep[pick] = make_pair(f, s);
        }
    }
}
void ai(){
    bool retry = true;
    
    while (retry == true){
        
        
        int rp = static_cast<unsigned int>(rand()) % 7;
        int rf = static_cast<signed int>(rand()) % 5 - 2;
        int rs = static_cast<signed int>(rand()) % 5 - 2;
        int f = twop[rp].first + rf;
        int s = twop[rp].second + rs;
        auto itwop = find(twop.begin(), twop.end(), make_pair(f, s));
        auto ionep = find(onep.begin(), onep.end(), make_pair(f, s));
        
        
        
        if (f < 0 || f >= SIZE || s < 0 || s >= SIZE){
            retry = true;
            continue;
        } else {
            
            retry = false;
            if(ionep != onep.end()){
                twop[rp] = make_pair(f, s);
                onep.erase(find(onep.begin(), onep.end(), twop[rp]));
            } else {
                twop[rp] = make_pair(f, s);
            }
        }
    }
}

void checkerboard(){
    
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            auto ionep = find(onep.begin(), onep.end(), make_pair(i, j));
            auto itwop = find(twop.begin(), twop.end(), make_pair(i, j));
            
            if(itwop != twop.end()) {
                pos[{i, j}] = two;
                cout << two << " ";
            } else if (ionep != onep.end()){
                pos[{i, j}] = one;
                cout << one << " ";
            } else {
                pos[{i, j}] = ca;
                cout << ca << " ";
            }
        }
        cout << endl;
    }
}


int main(){
    
    srand(time(NULL));
    
    bool run = true;
    while(run == true){
        
        checkerboard();
        cout << "Pick: ";
        cin >> pick;
        cout << "Move: ";
        cin >> mof >> mos;
        ai();
        moves();
    }
}