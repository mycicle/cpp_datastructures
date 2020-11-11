// A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

// Find the largest palindrome made from the product of two 3-digit numbers.
#include <string>
#include <iostream>

using namespace std;

bool isPalindrome(int n) {
    string num = to_string(n);
    int length = num.length();
    const char *number = num.c_str();
    int start = 0;
    int end = length-1;
    bool palindrome = true;
    for (int i = 0; i < length/2; i++) {
        if (number[start] != number[end]) {
            palindrome = false;
            break;  
        }       
        start++; 
        end--;
    }

    return palindrome;
}

int main() {
    int largestPalindrome = 0;
    int a = 999;
    int b = 999;
    int i;
    for (i = 0; i < a*b; i++) {
        int current = a*b;
        if (isPalindrome(current)) {
            largestPalindrome = current;
            cout << "largest palindrome " << current << endl;
            break;
        }
        if (i % 2 == 0) {
            a--;
        } else {
            b--;
        }
    }

    cout << "The largest palindrome is formed by multiplying " << a << " and " << b << " and is " << largestPalindrome << endl;
    cout << "That took " << i << " iterations to solve" << endl;
}