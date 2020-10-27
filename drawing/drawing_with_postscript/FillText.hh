#pragma once
#include <string>
#include <iostream>
#include "Fonts.hh"
#include "Shape.hh"
#include "Text.hh"

class FillText: public Text {
    public:
    FillText(float x, float y, const char* text, int font, uint32_t color, float fontsize, float rotate): 
        Text(x, y, text, font, color, fontsize, rotate) {}
    FillText(float x, float y, const char* text, int font, uint32_t color): 
        Text(x, y, text, font, color, 12, 0)  {}
    FillText(float x, float y, const char* text, uint32_t color): 
        Text(x, y, text, Fonts::Times, color, 12, 0)  {}

    void draw(std::ostream& s) const override {
        Text::internaldraw(s);
        s << " true charpath\n" << "fill\n" << -this->rot << " rotate\n";
    }
};
