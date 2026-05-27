#pragma once
#include "DrawableSurface.h"
#include "Shape.h"
#include "Coord.h"
#include <ostream>

class Point : public Shape {
private:
    Coord coord_;

public:
    Point(int x, int y, char id, int color = 37) : Shape(id, color), coord_{x, y} {}

    int getX() const { return coord_.getX(); }
    int getY() const { return coord_.getY(); }
    Coord getCoord() const { return coord_; }
    void setCoord(const Coord& coord) { coord_ = coord; }

    void draw(DrawableSurface& surface) override;
    std::vector<Coord> getBoundaryCoords() const override;
};

std::ostream& operator<<(std::ostream& os, const Point& p);
