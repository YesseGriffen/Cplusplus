#include <iostream>


using namespace std;
// This code uses the Wilsons Theorm to find primes up to any number...*Larger numbers may take a while, working with factorials*...


//unsigned long long can hold a much larger number...
unsigned long long factorial(unsigned int n){
    if(n == 0){
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

string ifDivisible(unsigned long long int n, unsigned long long int x){
    int check = 0;
    while(n % x == 0){
        check++;
        n /= x;
    }
    if(check == 1){
        string primeNumber = " is a prime number";
        return primeNumber;
    } else if(check == 2){
        string primeNumber = " is a wilsons prime number";
        return primeNumber;
    } else {
        string primeNumber = " is not a prime number";
        return primeNumber;
    }
}
int userInput(){
    int input;
    cout << "Number: ";
    cin >> input;
    return input;
}
int main(){
    cout << "***   Finding primes   ***" << endl;
    int long long Uinput = userInput();
    int long long result = factorial(Uinput - 1) + 1;
    string prime = ifDivisible(result, Uinput);
    cout << "Result: " << result << "--- --- ---: " << Uinput << prime << endl;

}