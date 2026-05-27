#pragma once
#include "DrawableSurface.h"
#include <vector>

class Coord;

class Shape {
protected:
    char id_;
    int color_;

public:
    Shape(char id = '?', int color = 37) : id_(id), color_(color) {}
    virtual void draw(DrawableSurface& surface) = 0;
    virtual std::vector<Coord> getBoundaryCoords() const = 0;
    virtual ~Shape() = default;

    char getId() const { return id_; }
    void setId(char id) { id_ = id; }

    int getColor() const { return color_; }
    void setColor(int color) { color_ = color; }
};
