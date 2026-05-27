#include "Diamond.h"
#include <cmath>
#include <stdexcept>

Diamond::Diamond(Coord center, int radius, char id, int color)
    : Shape(id, color), center_(center), radius_(radius)
{
    if (radius < 0)
    {
        throw std::invalid_argument("Diamond radius cannot be negative.");
    }
}

void Diamond::draw(DrawableSurface& surface)
{
    for (int y = -radius_; y <= radius_; y++)
    {
        int rowWidth = radius_ - std::abs(y);

        for (int x = -rowWidth; x <= rowWidth; x++)
        {
            int drawX = center_.getX() + x;
            int drawY = center_.getY() + y;

            surface.setGridChar(drawX, drawY, L'♦');
            surface.setGridColor(drawX, drawY, getColor());
        }
    }

    surface.setGridChar(center_.getX(), center_.getY(), wchar_t(getId()));
    surface.setGridColor(center_.getX(), center_.getY(), getColor());
}

std::vector<Coord> Diamond::getBoundaryCoords() const
{
    return {{center_.getX(), center_.getY() - radius_},
            {center_.getX() + radius_, center_.getY()},
            {center_.getX(), center_.getY() + radius_},
            {center_.getX() - radius_, center_.getY()}};
}

std::ostream& operator<<(std::ostream& os, const Diamond& d)
{
    Coord c = d.getCenterCoord();
    os << "Diamond(id=" << d.getId()
       << ", center=(" << c.getX() << "," << c.getY() << ")"
       << ", radius=" << d.getRadius()
       << ", color=" << d.getColor()
       << ")";
    return os;
}
