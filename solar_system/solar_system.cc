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
		long double x, y, z;
		Vec3d(): x(0), y(0), z(0) {}
		Vec3d(const long double x, const long double y, const long double z): x(x), y(y), z(z){}
		Vec3d(const Vec3d& orig): x(orig.x), y(orig.y), z(orig.z) {}
		Vec3d(Vec3d&& orig): x(orig.x), y(orig.y), z(orig.z) {}

		Vec3d& operator =(const Vec3d& orig) {
			x = orig.x;
			y = orig.y;
			z = orig.z;
			
			return *this;
		}

		Vec3d operator /(const long double scalar) const {
			Vec3d a(x/scalar, y/scalar, z/scalar);
			return a;
		}
		
		Vec3d operator +(const Vec3d& vec) const {
			Vec3d a(vec.x+x, vec.y+y, vec.z+z);
			return a;
		}

		Vec3d operator -(const Vec3d& vec) const {
			return (*this + (-vec));
		}

		Vec3d operator -() const {
			return Vec3d(-x, -y, -z);
		}

		Vec3d operator *(const Vec3d& vec) const {
			Vec3d a(x*vec.x, y*vec.y, z*vec.z);
			return a;
		}

		Vec3d operator *(const long double scalar) const {
			Vec3d a(x*scalar, y*scalar, z*scalar);
			return a;
		}

		Vec3d perpendicular2D() const {
			return Vec3d(-y, x, 0);
		}

		Vec3d handleNan() {
			if (isnan(x))
				x = 0;
			if (isnan(y))
				y = 0;
			if (isnan(z))
				z = 0;

			return (*this);
		}

		long double mag() const {
			return sqrt(x*x + y*y + z*z);
		}

		Vec3d unitVector() const {
			Vec3d unit = (*this) * (1/(*this).mag());
			return unit;
		}

		friend long double dot(const Vec3d& left, const Vec3d& right) {
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
		const long double G = 6.67430e-11;
		Vec3d pos, vel, acc;
		long double mass, radius, orb; //orb = orbital distance
		string name;

		int random = distribution(gen);
	public:
		Body(): pos(), vel(), acc(), mass(), radius(), orb(), name() {}
		Body(const Vec3d& pos, const Vec3d& vel, const Vec3d& acc, const long double mass, const long double radius, const string& name):
			pos(pos), vel(vel), acc(acc), mass(mass), radius(radius), orb(orb), name(name) {}
		Body(const Body& o): pos(o.pos), vel(o.vel), acc(o.acc), mass(o.mass), radius(o.radius), orb(o.orb), name(o.name) {}
		Body(Body&& o): pos(o.pos), vel(o.vel), acc(o.acc), mass(o.mass), radius(o.radius), orb(o.orb), name(o.name) {}

		Body operator =(const Body& o) {
			pos = o.pos; vel = o.vel; acc = o.acc; mass = o.mass; 
			radius = o.radius; name = o.name;
			return *this;
		}

		Vec3d calcGravForce(Body* body) {
			// gravitational force equation
			long double force = (G * mass * body->mass) / ((body->pos - pos).mag() * (body->pos - pos).mag());
			// cout << "force vector "<< force << endl;
			Vec3d forceVector = (body->pos-pos).unitVector() * force;
			return forceVector;
		}

		void update(vector<Body*>& bodies, const long double dt) {
			Vec3d netForce(0,0,0);
			for (auto body : bodies) {
				if(body != this) {
					// cout << "net force " << netForce << endl;
					netForce = netForce + calcGravForce(body);
				} else {
					// cout << "This is in the array!" << endl;
				}
			}

			pos = pos + vel*dt + acc*0.5*pow(dt, 2);
			vel = vel + acc*dt;
			acc = acc + (netForce/mass);
		}

		Vec3d getPos() const {
			return pos;
		}

		string getName() const {
			return name;
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
				long double rad = (stod(attribs.at(4)) + stod(attribs.at(5))) / 2;
				long double diam = rad*2;
				b.pos = Vec3d(rad*cos(b.random), rad*sin(b.random), 0).handleNan();

				Vec3d velocity_direction = Vec3d(-rad*sin(b.random), rad*cos(b.random), 0).handleNan();
				Vec3d velocity_unit = velocity_direction.unitVector().handleNan();
				long double velocity_mag = (diam * M_PI) / (stod(attribs.at(6)) * 24  * 60 * 60);
				if (isnan(velocity_mag))
					velocity_mag = 0;
				b.vel = velocity_unit * velocity_mag; 
				cout << "velocity " << b.vel << endl;
				Vec3d acceleration = (b.vel.perpendicular2D() * b.vel.perpendicular2D()).handleNan() / rad;
				b.acc = acceleration.handleNan();
		}
};

class SolarSystem {
	private:
		vector<Body*> bodies;
	public:
		SolarSystem(string filepath) {
			stringstream ss;
			string line;
			string name, orbits, mass, diam, rest;
			ifstream f(filepath);
			int counter = 0;
			while(getline(f, line)) {
				if (line.substr(0, 4) == "Name")
					continue;
				Body* b = new Body();;
				ss << line;
				ss >> (*b);
				bodies.push_back(b);
				counter ++;
				ss.clear();
			}
		}

		SolarSystem(vector<Body*>& bodies): bodies(bodies) {}

		void timeStep(long double dt) {
			for (auto body : bodies) {
				body->update(bodies, dt);
			}
		}

		friend ostream& operator <<(ostream& s, const SolarSystem& ss) {
			for (auto body : ss.bodies) {
				s << body->getPos() << endl;
			}
			// s << endl;
			return s;
		}
};

int main() {
	SolarSystem s("solarsystem.dat"); // this must not change
    // each body should have a random position in a circular or elliptical orbit around the sun
    // each  body should start with an appropriate velocity
    //each body should have velocity = https://en.wikipedia.org/wiki/Circular_orbit v= sqrt(GM/r)
    long double earthYear = 365.2425 *  24  * 60 * 60;
    const int numTimeSteps = 1000;
    long double dt = earthYear / numTimeSteps;
	cout << s << endl;
    for (int i = 0; i < numTimeSteps; i++)
        s.timeStep(dt);
    cout << s; // print out the state of the solar system (where each object is, location only)
	
	return 0;
    // if you do it right, earth should be in roughly the same place...
}