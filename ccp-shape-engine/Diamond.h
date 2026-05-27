#pragma once
#include "Shape.h"
#include "Coord.h"
#include "DrawableSurface.h"
#include <ostream>

class Diamond : public Shape {
private:
    Coord center_;
    int radius_;

public:
    Diamond(Coord center, int radius, char id, int color = 37);

    Coord getCenterCoord() const { return center_; }
    int getRadius() const { return radius_; }
    void setCenterCoord(const Coord& center) { center_ = center; }
    void setRadius(int radius) { radius_ = radius; }

    void draw(DrawableSurface& surface) override;
    std::vector<Coord> getBoundaryCoords() const override;
};

std::ostream& operator<<(std::ostream& os, const Diamond& d);
