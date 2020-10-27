#include <iostream>
#include "Rect.hh"
#include "Text.hh"
#include "FillText.hh"
#include "StrokeText.hh"
#include "Drawing.hh"

using namespace std;

const uint32_t red = 0xFF0000;
const uint32_t green = 0x00FF00;
const uint32_t blue = 0x0000FF;
const uint32_t purple = 0x800080;
const uint32_t black = 0x000000;
const uint32_t yellow = 0xFFFF00;
const uint32_t gray = 0x808080;
const uint32_t darkgreen = 0x008000;
const uint32_t darkblue = 0x000080;

int main() {

	Drawing draw("draw.ps");
	for (int x = 10; x <= 510; x += 100) {
		draw.add(new Rect(x, 20, 50, 30, red));
	}
	draw.add(new Text(500,100, "Mike is bad at smite", Fonts::Helvetica, black, 12, 0)); // Has contructor overloading
	draw.add(new FillText(400, 150, "C++ is cool", Fonts::Times, blue, 40, 30));
	draw.add(new StrokeText(200, 200, "The Sun is a Deadly Lazer", Fonts::Times, yellow, 40, 10));

}
