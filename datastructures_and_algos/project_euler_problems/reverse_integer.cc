#include <iostream>
#include <memory.h>
using namespace std;

int reverseInteger(int n) {
    bool negative = false;
    if (n < 0) {
        negative = true;
        n *= -1;
    }
    string num = to_string(n);
    int length = num.length();
    const char *number = num.c_str();
    char *reverseNumber = new char[length-1];

    int j = 0;
    for (int i = length-1; i >=0; i--, j++) {
        reverseNumber[j] = number[i]; 
    }

    int reverse = atoi(reverseNumber);
    if(reverse%10 == (reverseNumber[length-1]-'0')) {
        if (negative)
            reverse *= -1;
        return reverse;
    } else {
        return 0;
    }
}

int main() {
    int numbers[] = {123, -123, 120, 0, 1234567899, 123456789};
    for (int number : numbers) {
        cout << reverseInteger(number) << endl;
    }
    return 0;
}