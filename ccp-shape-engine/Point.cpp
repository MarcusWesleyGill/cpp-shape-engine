#include "Point.h"

void Point::draw(DrawableSurface& surface) {
    surface.setGridChar(coord_.getX(), coord_.getY(), wchar_t(getId()));
    surface.setGridColor(coord_.getX(), coord_.getY(), getColor());
}

std::vector<Coord> Point::getBoundaryCoords() const {
    return {coord_};
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "Point(id=" << p.getId()
       << ", x=" << p.getX()
       << ", y=" << p.getY()
       << ", color=" << p.getColor()
       << ")";
    return os;
}
