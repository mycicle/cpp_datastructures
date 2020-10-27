#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <string>

using namespace std;

class DynamicBitmap {
private:
	uint32_t color;
	uint32_t* p;
	uint32_t w, h;

	int iround( double x ) {
		int i = ( x >= 0 ? x + 0.5 : x - 0.5 );
		return i;
	}
	void plot(int x, int y, uint32_t color) {
		// bounds checking
		if (x < 0 || x > w || y < 0 || y > h) {
			throw out_of_range("Cannot plot the input points, out of range");
		}
		else {
			(*this) (x,y) = color;
		}

	}
	
public:
	// create a 1D array of size w*h to improve speed, array[i][j] = i*h+j
	DynamicBitmap(uint32_t w, uint32_t h, const uint32_t color): w(w), h(h), color(color), p(new uint32_t[w*h]) {
		memset(p, color, w*h*sizeof(uint32_t));
	}
	
	~DynamicBitmap() {
		delete [] p;
	}

	DynamicBitmap(DynamicBitmap &d): w(d.w), h(d.h), p(new uint32_t[d.w*d.h]) {
		memcpy(p, d.p, w*h*sizeof(uint32_t));
	}

	DynamicBitmap(DynamicBitmap &&orig): w(orig.w), h(orig.h), p(orig.p) {}

	DynamicBitmap& operator =(DynamicBitmap &orig) {
		if (this != &orig) {
			delete [] p;
			w = orig.w;
			h = orig.h;
			p = new uint32_t[w*h];
			memcpy(p, orig.p, w*h*sizeof(uint32_t));
		}

		return *this;
	}

	uint32_t operator ()(int x, int y) const {
    	// return p[y * w + x]; //reverse y and x input arguments
		return p[x*h + y];
	}

	uint32_t& operator ()(int x, int y) {
    	// return p[y * w + x]; // reverse y and x input arguments
		return p[x*h + y];
	}

	void line(int y0, int x0, int y1, int x1, uint32_t color) {
		int dx = abs(x1 - x0);
		int sx = x0<x1 ? 1 : -1;
		int dy = -abs(y1-y0);
		int sy = y0<y1 ? 1 : -1;
		int err = dx + dy;

		while(true) {
			plot(x0, y0, color);
			if (x0 == x1 && y0 == y1) break;
			int e2 = 2*err;
			if (e2 >= dy) {
				err += dy;
				x0 += sx;
			}
			if (e2 <= dx) {
				err += dx;
				y0 += sy;
			}
		}
	}

	void vertLine(int x0,int x1,int y,uint32_t color) {
		for (int x = x0;x <= x1;x++) {
			plot(x, y, color);
		}
	}

	void horizLine(int y0,int y1,int x,uint32_t color) {
		for (int y = y0;y <= y1;y++) {
			plot(x, y, color);
		}
	}
	void drawRect(int xi,int yi,int width,int height,uint32_t color) {
		vertLine(yi,yi+height,xi,color);
		horizLine(xi,xi+width,yi,color);
		vertLine(yi,yi+height,xi+width,color);
		horizLine(xi,xi+width,yi+height,color);
	}
	void fillRect(int xi,int yi,int width,int height,uint32_t color) {
		for(int x = xi; x <= xi + width; x++){
			vertLine(yi,yi+height,x,color);
		}
	}
	 void ellipse(int xcenter,int ycenter,int xdiameter,int ydiameter,uint32_t color) {
		if (xdiameter % 2 != 0) {
			throw domain_error("X diameter cannot be an odd number");
		}
		double rx = xdiameter / 2.0, ry = ydiameter / 2.0;    // ellipse semi-axes
   		for ( int x = iround(xcenter - rx); x <= iround(xcenter + rx); x++ )
   		{
      		double xrel = ( x - xcenter ) / rx;
      		double yrel = sqrt( 1.0 - xrel * xrel );
     		int y1 = iround(ycenter - ry * yrel);
      		int y2 = iround(ycenter + ry * yrel);
      		vertLine(y1,y2,x,color);
    	}
	 }

	friend ostream& operator <<(ostream& s, DynamicBitmap& d) {
		for (int i = 0; i < d.w; i++) {
			s << endl;
			for (int j = 0; j < d.h; j++) {
				s << d(i, j) << " ";
			}
		}
		s << endl;
		return s;
	}

	void save(const char filepath[]) {
		stbi_write_png(filepath, w, h, sizeof(uint32_t), p, h*sizeof(uint32_t));
	}
};

int main() {
	// FIRST PART (ADD COLORS HERE)
	constexpr uint32_t BLACK = 0xFF000000; // black opaque
	constexpr uint32_t RED = 0xFFFF0000; // red opaque
	constexpr uint32_t GREEN = 0xFF00FF00;
	constexpr uint32_t BLUE = 0xFF0000FF;
	constexpr uint32_t PURPLE = 0xFF800080;
	constexpr uint32_t YELLOW = 0xFFFFFF00;
	constexpr uint32_t GRAY = 0xFF808080;
	constexpr uint32_t DARKGREEN = 0xFF008000;
	constexpr uint32_t DARKBLUE = 0xFF000080;
	constexpr uint32_t WHITE = 0xFFFFFFFF;
	const uint32_t TEST = 1;
	const uint32_t TEST2 = 2;

	// SECOND PART (DO NOT EDIT)
	int xcenter = 100;
	int ycenter = 100;
	int xdiameter = 200;
	int ydiameter = 100;

	DynamicBitmap b(1024, 1024, BLACK); // Potentially dynamic size (Now: 1024 x 1024 pixels)
	b(32,32) = RED;
	cout << b(32,32);
	
	b.horizLine(0, 500, 200, RED); // Red horizontal line, from x=0 to x=500, at y = 200
	b.vertLine(0, 399, 300, RED); // Red vertical line, from y=0 to y=399, at x = 300
	
	b.drawRect(200,200, 100,50, BLUE); // Blue rectangle, TOP-LEFT at x=200, y=200. width=100, height=50
	b.fillRect(201,201, 98,48, WHITE); // White rectangle, same rules as above, but filled with color
	
	b.line(400,0, 550,300, YELLOW); // Line drawn using https://en.wikipedia.org/wiki/Bresenham's_line_algorithm
	
	b.ellipse(xcenter, ycenter, xdiameter, ydiameter, BLUE); //Ellipse using specs from above

	b.save("bitmap2.png"); 
	DynamicBitmap b2 = b; // test copy constructor
	b2 = b; // test operator =
	
}