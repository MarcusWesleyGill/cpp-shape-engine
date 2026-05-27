#pragma once

class Coord {
    public:
        Coord() : Coord(0,0) {}
        Coord(int x, int y) : x_(x), y_(y) {};
        Coord operator+(const Coord& c);
        Coord operator-(const Coord& c);
        Coord operator/(int d);
        
        int getX() const { return x_; }
        int getY() const { return y_; }
        void setX(int x) { x_ = x; }
        void setY(int y) { y_ = y; }
    private:
        int x_, y_;
};
