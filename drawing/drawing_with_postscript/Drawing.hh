#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Drawing {
private:
	std::ofstream ps;
	
public:
	Drawing(const std::string& filename) : ps(filename.c_str()) {}

	void add(Shape* s) {
		s->draw(ps);
	}
};
