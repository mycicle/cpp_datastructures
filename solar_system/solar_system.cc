#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

	default_random_engine gen(0);
	uniform_int_distribution<int> distribution(0, 99);

class Vec3d {
	public: 
		double x, y, z;
		Vec3d(): x(0), y(0), z(0) {}
		Vec3d(double x, double y, double z): x(x), y(y), z(z){}
		Vec3d(const Vec3d& orig): x(orig.x), y(orig.y), z(orig.z) {}
		Vec3d(Vec3d&& orig): x(orig.x), y(orig.y), z(orig.z) {}

		Vec3d& operator =(const Vec3d& orig) {
			x = orig.x;
			y = orig.y;
			z = orig.z;
		}

		friend double dot(const Vec3d& left, const Vec3d& right) {
			return left.x*right.x + left.y*right.y + left.z*right.z;
		}

		friend Vec3d cross(const Vec3d& left, const Vec3d& right) {
			return Vec3d(left.y*right.z - left.z*right.y, left.z*right.x - left.x*right.z, left.x*right.y - left.y*right.x);
		}

		friend ostream& operator <<(ostream& s, const Vec3d& v) {
			return s << "(" << v.x << "," << v.y << "," << v.z <<")";
		}
};

class Body {
	private:
		Vec3d pos, vel, acc;
		double mass, radius, orb; //orb = orbital distance
		string name;

		int random = distribution(gen);
	public:
		Body(): pos(), vel(), acc(), mass(), radius(), orb(), name() {}
		Body(const Vec3d& pos, const Vec3d& vel, const Vec3d& acc, const double mass, const double radius, const string name):
			pos(pos), vel(vel), acc(acc), mass(mass), radius(radius), orb(orb), name(name) {}
		Body(const Body& o): pos(o.pos), vel(o.vel), acc(o.acc), mass(o.mass), radius(o.radius), orb(o.orb), name(o.name) {}
		Body(Body&& o): pos(o.pos), vel(o.vel), acc(o.acc), mass(o.mass), radius(o.radius), orb(o.orb), name(o.name) {}

		Body& operator =(const Body& o) {
			pos = o.pos; vel = o.vel; acc = o.acc; mass = o.mass; 
			radius = o.radius; name = o.name;
		}

		void update(const Vec3d& p, const Vec3d& v, const Vec3d& a) {
			pos = p; vel = v; acc = a;
		}

		friend ostream& operator <<(ostream& s, const Body& b) {
			return s << "Name: " << b.name << " Mass: " << b.mass << " Radius: " << b.radius << " Position: " << b.pos
			<< endl << "Velocity: " << b.vel << " Acceleration: " << b.acc;
		}

		friend void operator >>(istream &out, Body& b) {
				string i;
				vector<string> attribs;
				while (out >> i) {
					attribs.push_back(i);
				}
				if (attribs.size() != 10) {
					throw length_error("Invalid input length. Expected 10 columns");
				}
				b.name = attribs.at(0);
				b.mass = stod(attribs.at(2));
				b.radius = stod(attribs.at(3))/2;
				double rad = stod(attribs.at(4)) + stod(attribs.at(5)) / 2;
				b.pos = Vec3d(rad*cos(b.random), rad*sin(b.random), 0);
		}
};

// class Body {
// 	private:
// 		string name;
// 		double mass, radius;
// 		Vec3d position;
// 		int random = distribution(gen);
// 	public:
// 		Body() {}

// 		friend ostream& operator <<(ostream& s, Body &b) {
// 			return s << "Name: " << b.name << " Mass: " << b.mass << " Radius: " << b.radius << " Position: " << b.position;
// 		}

// 		friend void operator >>(istream &out, Body &b) {
// 				string i;
// 				vector<string> attribs;
// 				while (out >> i) {
// 					attribs.push_back(i);
// 				}
// 				if (attribs.size() != 10) {
// 					throw length_error("Invalid input length. Expected 10 columns");
// 				}
// 				b.name = attribs.at(0);
// 				b.mass = stod(attribs.at(2));
// 				b.radius = stod(attribs.at(3))/2;
// 				double rad = stod(attribs.at(4)) + stod(attribs.at(5)) / 2;
// 				b.position = Vec3d(rad*cos(b.random), rad*sin(b.random), 0);
// 		}
// };

int main() {
	stringstream ss;
	string line;
	string name, orbits, mass, diam, rest;
	vector<Body> bodies;
	ifstream f("solarsystem.dat");

	int counter = 0;
	while(getline(f, line)) {
		if (line.substr(0, 4) == "Name")
			continue;
		Body b;
		ss << line;
		ss >> b;
		cout << b << endl;
		bodies.push_back(b);
		counter ++;
		ss.clear();
	}
}