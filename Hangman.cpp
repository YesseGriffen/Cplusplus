/* Very basic version of hangman */


#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
vector<char> let = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
vector<string> wordbank = {"frog", "light"};
vector<char> usedlet;

void game(){
    int count;
    int rindex = rand() % wordbank.size();
    string relement = wordbank[rindex];
    vector<string> gui(relement.length(), " __");
    bool run = true, check = false;
    char guess;

    while (run == true){

        auto iter = find(usedlet.begin(),usedlet.end(), guess);
        if(iter == usedlet.end()){
            usedlet.push_back(guess);
        }
        if(relement.length() == count){
            cout << "   Won!   ";
            run = false;
        } else if(check == true){
            cout << "Guess: ";
            cin >> guess;
        } 
        check = true;
        for (int n = 0; n < relement.length(); n++){
            if(guess == relement[n]){
                gui[n] = guess;
                if(find(usedlet.begin(), usedlet.end(), guess) == usedlet.end()){
                    count++;
                } 
            } 
            cout << gui[n];
        }
    }
}

int main(){
    srand(time(0));
    game();
    return 0;
}