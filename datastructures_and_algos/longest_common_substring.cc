#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>

#define MAX 75

using namespace std;

struct strAndLen {
    vector<char> str;
    char *strin;
    int len;
};

void printTable(int table[MAX+1][MAX+1], int x, int y, char a[], char b[]) {

    for (int i = 0; i <= x; i++) {
       for (int j = 0; j <= y; j++) {
           if (j == 0 && i > 0) {
               cout << a[i-1] << " ";
               continue;
           }
           if (i == 0 && j > 0) {
               cout << b[j-1] << " ";
               if (j == y){
                   cout<<'\n';
                }
               continue;
           }

          // Prints ' ' if j != n-1 else prints '\n'           
          cout << table[i][j] << " \n"[j == y]; 
       }
    }
}

int LCS(char a[], char b[]) {
    const int x = (int) strlen(a);
    const int y = (int) strlen(b);
    if (x > MAX+1 || y > MAX+1) {
        return -1;
    }

    int table[MAX+1][MAX+1] = {0};
    for (int i = 1; i <= x; i++){
        for (int j = 1; j <= y; j++) {
            if (a[i-1] == b[j-1]) {
                table[i][j] = 1 + table[i-1][j-1];
                continue;
            } else {
                table[i][j] = max(table[i-1][j], table[i][j-1]);
            }
        }
    }

    // printTable(table, x, y, a, b);
    int output = table[x][y];

    return output;
}

vector<char> CS(char a[], char b[]) {
    const int x = (int) strlen(a);
    const int y = (int) strlen(b);
    if (x > MAX+1 || y > MAX+1) {
        return vector<char>();
    }
    vector<char> stack;
    int table[MAX+1][MAX+1] = {0};
    int m = 0;
    int row = 0;
    int col = 0;
    for (int i = 1; i <= x; i++){
        for (int j = 1; j <= y; j++) {
            if (a[i-1] == b[j-1]) {
                table[i][j] = 1 + table[i-1][j-1];
                if (table[i][j] > m) {
                    m++;
                    // cout<<a[i-1]<<" "<<b[j-1]<<" "<<i-1<<endl;
                    stack.push_back(a[i-1]);
                }
                row++;
                col++;
                continue;
            } else {
                table[i][j] = max(table[i-1][j], table[i][j-1]);
            }
        }
    }
    cout<<"The memoization table is:\n";
    printTable(table, x, y, a, b);
    cout<<"\n\n";

    return stack;

}

void printOutputPretty(char s1[], char s2[]) {
    cout<<"string 1: "<<s1<<"\nstring 2: "<<s2<<'\n'<<endl;
    vector<char> cs = CS(s1, s2);
    printf("Stack length: %ld\n", cs.size());
    printf("\nOutput:\n\t");
    cout<<"\"";
    for (auto it = cs.begin(); it <= cs.end(); it++) {
        cout<<*it<<"";
    }
    cout<<"\""<<endl;
    cout<<"\t"<<LCS(s1,s2)<<endl;
}

int main() {
    cout<<"Stack length is a check on the bonus length (theoretically you can use the bonus function CS to do everything)"<<endl;
    cout<<"Every time this program is run, the bonus function is called 4x and the standard function is called 3x\n"<<endl;
    char s1[] = "hello there";
    char s2[] = "helxxxxxlo thxxxexrxxxxe";
    printOutputPretty(s1, s2);
    cout<<"\n\n";
    char s7[] = "GEZZZNZZERAZZLZZZ KZEZNZOZBZZZZI";
    char s8[] = "GENERAL KENOBI";
    printOutputPretty(s7, s8);
    cout<<"\n\n";
    char s3[] = "dzzidz zyozzuzz kzznzzzzow";
    char s4[] = "dxixxxd yxoxxxux kxnxoxxxxw";
    printOutputPretty(s3, s4);
    cout<<"\n\n";    
    char s5[] = "that wzez azrze ztzhzze zbezzzst zzgzrozzuzp ezvzzezzr";
    char s6[] = "that wle larle tllhe lblest lgrloulpll";
    printOutputPretty(s5, s6);
    cout<<"\n\n";    
    return 0;
}
