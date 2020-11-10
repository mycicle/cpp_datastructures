// clang++ -std=c++2a -c linkedlist.cpp -Xclang -emit-module-interface -o linkedlist.pcm

module;
#include <iostream>

export module linkedlist;
export class LinkedList {
    private:
        class Node {
            public:
                int value;
                Node* next;
                Node(const int& val, Node* next=nullptr): value(val), next(next) {}
                //operator = 
                Node& operator =(const Node& orig) {
                    value = orig.value;
                    next = orig.next;
                    return (*this);
                }
        };

        Node* head;
        Node* tail;
        int length;

        Node get(const int i) const {
            if (head == nullptr) {
                throw std::out_of_range("Attempting to access a value from an empty list");
            } else if (i > length) {
                throw std::out_of_range("inthe list does not have that many elements");
            }
            Node* temp = head;
            for (int j = 1; j < i; j++) {
                temp = temp->next;
            }
            return (*temp);
        }
        
        Node& get(const int i) {
            if (head == nullptr) {
                throw std::out_of_range("Attempting to access a value from an empty list");
            } else if (i > length) {
                throw std::out_of_range("inthe list does not have that many elements");
            }
            Node* temp = head;
            for (int j = 1; j < i; j++) {
                temp = temp->next;
            }
            return (*temp);
        }

    public:
        //constructor
        LinkedList(): head(nullptr), tail(nullptr), length(0) {}
        LinkedList(int& val): head(new Node(val)), tail(head), length(1) {} 
        //destructor
        ~LinkedList() {
            while(head != nullptr) {
                this->removeStart();
            }
        }
        //copy constructor
        LinkedList(const LinkedList& orig) {
            if (orig.length <= 0) {
                head = nullptr;
                tail = nullptr;
                return;
            }

            head = new Node(orig.head->value);
            if (orig.head == orig.tail) {
                tail = head;
                return;
            }
            
            Node* temp = head;
            for (int i = 1; i < orig.length; i++) {
                temp->next = new Node(orig[i]);
                temp = temp->next;
            }
            tail = temp;
        }
        //move constructor
        LinkedList(LinkedList&& orig) {
            std::swap(head, orig.head);
            std::swap(tail, orig.tail);
        }
        //operator =
        LinkedList& operator =(const LinkedList& orig) {
            if (&orig != this) {
                (*this).~LinkedList();
                if (orig.length == 0) {
                    head = nullptr;
                    tail = nullptr;
                    return (*this);
                }
                head = new Node(orig.head->value);
                length++;
                if (orig.head == orig.tail) {
                    tail = head;
                } else {
                    Node* temp = head;
                    for (int i = 1; i < orig.length; i++) {
                        temp->next = new Node(orig[i]);
                        temp = temp->next;
                        length++;
                    }
                    tail = temp;
                }
            }
            return (*this);
        }
        //operator +
        void operator +(const LinkedList& orig) {
            tail->next = orig.head;
        }
        //read-write operator []
        int& operator [](const int i) {
            if (i >= length)
                throw std::out_of_range("Attempting to access element out of range");
            if (head == nullptr)
                throw std::out_of_range("Attempting to access an element from an empty list");
            Node* temp = head;
            for (int j = 1; j <= i; j++) {
                temp = temp->next;
            }

            return temp->value;
        }
        //read only operator []
        int operator [](const int i) const {
            if (i >= length)
                throw std::out_of_range("Attempting to access element out of range");
            if (head == nullptr)
                throw std::out_of_range("Attempting to access an element from an empty list");
            Node* temp = head;
            for (int j = 1; j <= i; j++) {
                temp = temp->next;
            }
            
            return temp->value;
        }

        void addEnd(const int val) {
            if (length <= 0) {
                head = new Node(val);
                tail = head;
                length++;
            } else if (length == 1) {
              head->next = new Node(val);
              tail = head->next;
              length++;  
            } else {
                tail->next = new Node(val);
                tail = tail->next;
                length++;
            }
        }

        void addStart(const int val) {
            Node* temp = head;
            head = new Node(val);
            head->next = temp;
            length++;
        }

        void insert(const int i, int val) {
            if (i > length) 
                throw std::out_of_range("Attempting to insert to an index out fo range");
            Node* temp = head;
            for (int j = 1; j < i; j++) {
                temp = temp->next;
            }
            temp->next = new Node(val, temp->next);
            length++;
        }

        int removeEnd() {
            if (length <= 0) 
                throw std::out_of_range("Attempting to remove from an index out of range");
            Node* temp = head;
            for (int i = 1; i < length-1; i++) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
            tail = temp;
            length--;
            return tail->value;
        }

        void removeStart() {
            if (length <= 0) 
                throw std::out_of_range("Attempting to remove from an index out of range");
            Node* temp = head->next;
            delete head;
            head = temp;
            length--;
            if (length == 0) {
                tail = head;
            }
        }

        void remove(const int i) {
            if (i > length) 
                throw std::out_of_range("Attempting to remove from an index out of range");
            if (length == 0) {
                throw std::out_of_range("Attempting to remove from an empty list");
            }
            Node* temp = head;
            for (int j = 1; j < i; j++) {
                temp = temp->next;
            }
            Node* killed = temp->next;
            temp->next = killed->next;
            delete killed;
            length--;
        }

        void print() {
            Node* temp = head;
            for (int i = 0; i < length; i++) {
                std::cout << temp->value << ' ';
                temp = temp->next;
            }
            std::cout << std::endl;
        }
        //print
        friend std::ostream& operator <<(std::ostream& s, const LinkedList& ll) {
            Node* temp = ll.head;
            for (int i = 0; i < ll.length; i++) {
                s << temp->value << ' ';
                temp = temp->next;
            }
            std::cout << std::endl;
            return s;
        }
        
        class iterator {
                private:
                    Node* current;
                public:
                    iterator(LinkedList& list) {
                        current = list.head;
                    }
                    bool operator !() const {
                        return current != nullptr;
                    }
                    void operator ++() {
                        current = current->next;
                    }
                    int& operator *(){
                        return current->value;
                    }
        };

        class const_iterator {
            private:
                Node* current;
            public:
                const_iterator(const LinkedList& list) {
                    current = list.head;
                }
                bool operator !() const {
                    return current != nullptr;
                }
                void operator ++() {
                    current = current -> next;
                }
                int operator *() {
                    return current->value;
                }
        };
};