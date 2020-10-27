#pragma once
#include <string>
#include <iostream>
#include "Fonts.hh"
#include "Shape.hh"

class Text: public Shape {
    private:
        const char* text;
        uint32_t color;
        float x, y, font, fs;
    public:
        float rot;
        Text(float x, float y, const char* text, int font, uint32_t color, float fontsize, float rotate): 
            x(x), y(y), text(text), font(font), color(color), fs(fontsize), rot(rotate)  {}
        Text(float x, float y, const char* text, int font, uint32_t color): 
            x(x), y(y), text(text), font(font), color(color), fs(12), rot(0)  {}
        Text(float x, float y, const char* text, uint32_t color): 
            x(x), y(y), text(text), font(Fonts::Times), color(color), fs(12), rot(0)  {}
        const char* getFont(const int f) const {
            switch (f) {
                case Fonts::Helvetica:
                    return "/Helvetica";
                    break;
                case Fonts::Times:
                    return "/Times-Roman";
                    break;
                default:
                    std::cout << "Invalid Font" << std::endl;
                    throw;
                    break;
            }
        }

        void internaldraw(std::ostream& s) const {
            this->drawColor(s, this->color);
            s << this->getFont(this->font) << " findfont\n"
            << this->fs << " scalefont\n" << "setfont\n"
            << this->rot << " rotate\n" << "newpath\n" 
            << this->x << " " << this->y << " moveto\n"
            << "(" << this->text << ")" ;
        }

        void draw(std::ostream& s) const override {
            Text::internaldraw(s);
            s << " show\n" << -this->rot << " rotate\n";
        }
};
