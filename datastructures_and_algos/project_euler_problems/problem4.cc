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
    int iterations = 0;
    int a_max = 0;
    int b_max = 0;
    for (int a = 999; a > 100; a--) {
        if (a_max*b_max > a*999)
            break;
        for (int b = 999; b > 100; b--) {
            iterations++;
            int current = a*b;
            if (isPalindrome(current)) {
                if (current > largestPalindrome) {
                    a_max = a; b_max = b;
                    largestPalindrome = current;   
                }
                break;
            }
        }
    }

    cout << "The largest palindrome is formed by multiplying " << a_max << " and " << b_max << " and is " << largestPalindrome << endl;
    cout << "That took " << iterations << " iterations to solve" << endl;
}