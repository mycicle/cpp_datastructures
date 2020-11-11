// A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

// Find the largest palindrome made from the product of two 3-digit numbers.
#include <string>
#include <iostream>

using namespace std;

bool isPalindrome(int n) {
    string number = to_string(n);
    char *backwards = new char[number.length()];
    int j = 0;
    for (int i = number.length()-1; i >= 0; i++, j++) {
        backwards[j] = number[i];
    }

    return atoi(backwards) == n;
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