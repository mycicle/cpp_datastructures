#include <iostream>
#include <memory.h>
#include <cmath>
using namespace std;

class Vec2d {
    // all vec3d objects contain a payload of n integer numbers 
    // just because 
    private:
        double x, y, length;
        //allocate 100 int values of memory for p 
        int *p;
    public:
        Vec2d(): x(0), y(0), p(nullptr) {}
        Vec2d(double x, double y, int length, int value): x(x), y(y), length(length), p(new int[length]) {
            for (int i = 0; i < length; i++) {
                p[i] = value;
            }
        }
        ~Vec2d() {
            delete [] p;
        }

        friend ostream& operator <<(ostream& s , const Vec2d& v){ // Cout
            s << "(" << v.x << ',' << v.y << ", ";
            for (int i = 0; i < v.length; i++) {
                s << v.p[i] << " ";
            }
            s << ")";
            return s;
        }

        Vec2d operator *(const Vec2d& v){ // Vector * Vector
            Vec2d a(x*v.x , y*v.y, 10, 2);
            return a;
        }
        // Move constructor!
        Vec2d(Vec2d&& v): x(x), y(y) {
            swap(p, v.p);
        } 
        //Copy Constructor
        Vec2d(const Vec2d& orig):x(orig.x),y(orig.y),length(orig.length){
            memcpy(p,orig.p,sizeof(int)*orig.length);
        }

        Vec2d operator *(const double& d){ // Vector * Double
            Vec2d a(x*d , y*d, 10, 2);
            return a;
        }
        Vec2d operator /(const Vec2d& v){ // Vector / Vector
            Vec2d a(x/v.x , y/v.y, 10, 2);
            return a;
        }
        Vec2d operator /(const double& d){ // Vector / Double
            Vec2d a(x/d , y/d, 10, 2);
            return a;
        }
        Vec2d operator =(const Vec2d& v){ // Vector = Vector
            // copying the content of v into *this
            x = v.x;
            this->y = v.y;
            length = v.length;
            memcpy(p, v.p, sizeof(int)*v.length);

            return (*this);
        }
        Vec2d operator +(const Vec2d& v){ // Vector + Vector
            Vec2d a(x + v.x , y + v.y, 10, 2);
            return a;
        }
        Vec2d operator +(const double& d){ // Vector + Double
            Vec2d a(x + d , y + d, 10, 2);
            return a;
        }
        Vec2d operator -(const Vec2d& v){ // Vector - Vector
            Vec2d a(x - v.x , y - v.y, 10, 2);
            return a;
        }
        Vec2d operator -(const double& d){ // Vector - Double
            Vec2d a(x - d , y - d, 10, 2);
            return a;
        }
        // you need to define the following operators:
        /*
        vector * vector
        vector * double
        vector / double
        vector / vector
        vector = vector
        vector + vector
        vector + double
        vector - vector
        vector - double
        */
};

class ChessPiece {
    
};

class King {

};

class Queen {

};

class Bishop {
    
};

class Rook {
    
};

class Knight {
    
};

class Pawn {

}; 

class ChessBoard {
// print out a board of diffrent ascii symbols to represent the position of each piece on the board   
};

int main() {


    // x = 1, y = 2, p = new int[10] filled with the number 1
    Vec2d a(1, 2, 10, 1);
    Vec2d b(1, 5, 10, 2);
    Vec2d c = a + b;
    // x, y, 1 1 1 1 1 1 1 1 1 1 1 1
    cout << a << " " << b << " " << c << endl;
    // subtract x and y of a and b
    cout << a - b << endl;
    // adds 2 to x and y
    cout << a + 2 << endl;

    // ChessBoard("output.txt");
    // ChessBoard.addKing();
    // ChessBoard.addQueen();
    // ChessBoard.addRook();
    // ChessBoard.addPiece(Pawn(1, 2));
    // ChessBoard.print();
    // ChessBoard.move();
    // ChessBoard.toFile();

}
