#pragma once
#include <iostream>
#include "Fonts.hh"
#include "Shape.hh"
#include "Text.hh"

class StrokeText: public Text {
    public:
        StrokeText(float x, float y, const char* text, int font, uint32_t color, float fontsize, float rotate): 
            Text(x,y,text,font,color,fontsize,rotate){}
        StrokeText(float x, float y, const char* text, int font, uint32_t color): 
            Text(x,y,text,font,color,48,45) {}
        StrokeText(float x, float y, const char* text, uint32_t color): 
            Text(x,y,text,Fonts::Times,color,48,45) {}
        
       void draw(std::ostream& s) const override {
           Text::internaldraw(s);
           s << " true charpath\n" << "stroke\n" << -this->rot << " rotate\n";
        }   
};

