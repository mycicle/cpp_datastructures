#pragma once
#include "Shape.hh"

class Rect : public Shape {
private:
	float x, y, w, h;
public:
	Rect(float x, float y, float w, float h) :
		x(x), y(y), w(w), h(h){}
	void draw(std::ostream& s) const override {
		s << x << ' ' << y << " moveto " <<
			x+w << ' ' << y << " lineto " <<
			x+w << ' ' << y+h << " lineto " <<
			x << ' ' << y+h << " lineto closepath stroke\n";
	}

	void fill(std::ostream& s) const {
		s << x << ' ' << y << " moveto " <<
			x+w << ' ' << y << " lineto " <<
			x+w << ' ' << y+h << " lineto " <<
			x << ' ' << y+h << " lineto closepath fill\n";
	}

};