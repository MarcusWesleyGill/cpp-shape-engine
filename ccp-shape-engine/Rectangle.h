#pragma once
#include "DrawableSurface.h"
#include "Shape.h"
#include "Point.h"
#include "Coord.h"
#include <ostream>

template <typename T>
bool inRange(T value, T low, T high) {
    return value >= low && value <= high;
}

class Rectangle : public Shape {
private:
    Coord topLeft_;
    Coord bottomRight_;
    int width_;
    int height_;
    void updateBottomRight();

public:
    Rectangle(Coord topLeft, int width, int height, char id, int color = 37);

    Coord getTopLeft() const { return topLeft_; }
    Coord getBottomRight() const { return bottomRight_; }
    Coord getCenter();
    void setTopLeft(const Coord& coord);

    int getWidth() const { return width_; }
    void setWidth(int width);

    int getHeight() const { return height_; }
    void setHeight(int height);

    void draw(DrawableSurface& board) override;
    friend void drawFilled(DrawableSurface& board, const Rectangle& rect);
    std::vector<Coord> getBoundaryCoords() const override;

    bool intersectsWith(const Rectangle& rect) const;
    bool containsPoint(const Point& point) const;
};

std::ostream& operator<<(std::ostream& os, const Rectangle& r);
