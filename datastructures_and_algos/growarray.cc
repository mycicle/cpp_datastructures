#include <iostream>
#include <memory.h>
#include <chrono>
using namespace std;

template<typename T>
class GrowArray {
    private:
        T* data;
        int capacity;
        int used;

        void grow() { // O(n)
            T* temp = this->data;
            this->capacity *= 2;
            this->data = new T[this->capacity];
            memcpy(this->data, temp, this->used*sizeof(T));
            delete [] temp;
        }

    public:
        GrowArray(int initialSize): data(new T[initialSize]), capacity(initialSize), used(0) {}
        GrowArray() {
            this(1);
        }
        ~GrowArray() {
            delete [] this->data;
        }

        GrowArray(const GrowArray<T> &orig): capacity(orig.capacity), used(orig.used), data(new T[orig.capacity]) { // O(n)
            memcpy(this->data, orig.data, orig.used * sizeof(T));
        }

        GrowArray& operator =(GrowArray<T> &orig) { // O(n)
            if (this != &orig) {
                delete [] this->data;
                this->capacity = orig.capacity;
                this->used = orig.used;
                this->data = new T[orig.capacity];
                memcpy(this->data, orig.data, orig.used * sizeof(T));
            }

            return *this;
        }

        void addEnd(T v) { // OMEGA(1) O(n)
            if (used >= capacity) {
                grow();
            }
            data[used] = v;
            used++;
        }

        void addStart(T v) { // O(n)
            if (used >= capacity)
                grow();

            T* old = data;
            data = new T[capacity];
            memcpy(&data[1], old, used*sizeof(T));
            data[0] = v;
            used++;
            delete [] old;
        }

        void insert(int i, T v) { //OMEGA(1) O(n)
            if (i >= used)
                throw out_of_range("Index out of bounds");
            if (used >= capacity)
                grow();
            if (i == used-1)
                return addEnd(v);
            if (i == 0)
                return addStart(v);
                
            memmove(&data[i+1], &data[i], (used-i)*sizeof(T));
            data[i] = v;
            used++;
        }

        T removeEnd() { // O(1)
            T temp = data[--used];
            return temp;
        }

        T removeStart() { // O(n)
            T old = data[0];
            memmove(data, (data+1), (--used)*sizeof(T));
            return old;
        }

        T remove(int i) { // OMEGA(1) O(n)
            if (i == 0)
                return removeStart();
            if (i==used-1)
                return removeEnd();
            if (i >= used)
                throw out_of_range("Index out of bounds");

            T old = data[i];
            memmove((data+i), (data+i+1), (used-i)*sizeof(T));
            used--;
            return old;
        }

        int size() const { // O(1)
            return this->used;
        }

        T operator [](const int i) const { // O(1)
            if (i > capacity-1)
                throw out_of_range("Index out of bounds");
            return this->data[i];
        }
        T& operator [](const int i) { // O(1)
            if (i > capacity-1) 
                throw out_of_range("Index out of bounds");
            return this->data[i];
        }

        friend ostream& operator <<(ostream &s, GrowArray<T>& arr) { // O(n)
            for (int i = 0; i < arr.size(); i++) {
                s << arr[i] << ',';
            }
            return s << &arr.data;
        }
};


int main(int argc, char **argv) {
    int a, b, c;
    if (argc != 4) {
        cout << "No command line arguments provided. Defaulting to stdin." << endl;
        cout << "Input A: ";
        cin >> a;
        cout << "Input B: ";
        cin >> b;
        cout << "Input C: ";
        cin >> c;
    }
    else {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        c = atoi(argv[3]);
    }


    GrowArray<int> arr(a+b+c);
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 1; i <= a; i++) {
        arr.addEnd(i);
    }
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Time to add " << a << " elements to the end of the array: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 1; i <= 1000; i++) {
        arr.addStart(i);
    }
    t2 = chrono::high_resolution_clock::now();
    cout << "Time to add " << b << " elements to the start of the array: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 1; i <= b; i++) {
        arr.insert(c, i);
    }
    t2 = chrono::high_resolution_clock::now();
    cout << "Time to add " << b << " elements to index " << c << " of the array: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl << endl;

    cout << "max size of array: " << arr.size() << endl;
    t1 = chrono::high_resolution_clock::now();
    for (int i = 1; i <= a; i++) {
        arr.removeEnd();
    }
    t2 = chrono::high_resolution_clock::now();
    cout << "Time to remove " << a << " elements from the end of the array: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl << endl;

    t1 = chrono::high_resolution_clock::now();
    for (int i = 1; i <=b; i++) {
        arr.removeStart();
    }
    t2 = chrono::high_resolution_clock::now();
    cout << "Time to remove " << b << " elements from the start of the array: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl << endl;
    cout << "Size after removal of a+b elements: " << arr.size() << endl;

    long double total = 0;
    for (int i = 0; i < arr.size(); i++) {
        total += arr[i];
    }

    cout << "Sum of remaining elements: " << total << endl;
    return 0;
}