#include <iostream>
#include <vector>

using namespace std;
/*
    I'm proud of the logic on this one - modifications are made with O(1) memory requirements
*/
void removeDuplicates(vector<int>& list) {
    int j = 0; 
    for (int i = 1; i < list.size(); i++) {
        if (list[i] == list[j]) {
            list[j] = list[i];
            while (list[i] == list[j]) {
                i++;
            }
        }
        j++;
        list[j] = list[i];
    }
    list.resize(j+1);
}

int main() {
    int numbers[] = {0, 0, 0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 8, 9, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 15, 16, 17, 17, 18, 18, 19, 19, 20, 20, 20, 22};
    vector<int> list;
    for (int i : numbers)
        list.push_back(i);
    
    for(auto i : list) 
        cout << i << " ";
    cout << endl;

    removeDuplicates(list);

    for(auto i : list) 
        cout << i << " ";
    cout << endl;

    return 0;
}