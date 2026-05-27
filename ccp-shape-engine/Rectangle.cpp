#include "Rectangle.h"
#include "DrawableSurface.h"
#include <stdexcept>

Rectangle::Rectangle(Coord topLeft, int width, int height, char id, int color)
    : Shape(id, color), topLeft_(topLeft), width_(width), height_(height)
{
    if (width < 0 || height < 0)
    {
        throw std::invalid_argument("Rectangle width and height cannot be negative.");
    }
    updateBottomRight();
}

void Rectangle::updateBottomRight()
{
    bottomRight_ = Coord(topLeft_.getX() + width_ - 1,
                         topLeft_.getY() + height_ - 1);
}

void Rectangle::setTopLeft(const Coord& coord)
{
    topLeft_ = coord;
    updateBottomRight();
}

void Rectangle::setWidth(int width)
{
    if (width < 0)
    {
        throw std::invalid_argument("Rectangle width cannot be negative.");
    }
    width_ = width;
    updateBottomRight();
}

void Rectangle::setHeight(int height)
{
    if (height < 0)
    {
        throw std::invalid_argument("Rectangle height cannot be negative.");
    }
    height_ = height;
    updateBottomRight();
}

Coord Rectangle::getCenter()
{
    return topLeft_ + (bottomRight_ - topLeft_) / 2;
}

void drawFilled(DrawableSurface& board, const Rectangle& rect)
{
    if (rect.getHeight() <= 0 || rect.getWidth() <= 0)
    {
        return;
    }

    Coord topLeft = rect.getTopLeft();

    // draw one row, then recurse on the smaller rectangle under it
    for (int x = topLeft.getX(); x < topLeft.getX() + rect.getWidth(); x++)
    {
        board.setGridChar(x, topLeft.getY(), L'█');
        board.setGridColor(x, topLeft.getY(), rect.getColor());
    }

    Coord nextTopLeft(topLeft.getX(), topLeft.getY() + 1);
    Rectangle smaller(nextTopLeft, rect.getWidth(), rect.getHeight() - 1, rect.getId(), rect.getColor());
    drawFilled(board, smaller);
}

void Rectangle::draw(DrawableSurface& board)
{
    drawFilled(board, *this);

    Coord center = getCenter();
    board.setGridChar(center.getX(), center.getY(), wchar_t(getId()));
    board.setGridColor(center.getX(), center.getY(), getColor());
}

bool Rectangle::intersectsWith(const Rectangle& other) const
{
    if (bottomRight_.getX() < other.topLeft_.getX()) return false;
    if (other.bottomRight_.getX() < topLeft_.getX()) return false;
    if (bottomRight_.getY() < other.topLeft_.getY()) return false;
    if (other.bottomRight_.getY() < topLeft_.getY()) return false;
    return true;
}

bool Rectangle::containsPoint(const Point& point) const
{
    return inRange(point.getX(), topLeft_.getX(), bottomRight_.getX()) &&
           inRange(point.getY(), topLeft_.getY(), bottomRight_.getY());
}

std::vector<Coord> Rectangle::getBoundaryCoords() const
{
    return {topLeft_,
            {bottomRight_.getX(), topLeft_.getY()},
            {topLeft_.getX(), bottomRight_.getY()},
            bottomRight_};
}

std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    Coord tl = r.getTopLeft();
    os << "Rectangle(id=" << r.getId()
       << ", topLeft=(" << tl.getX() << "," << tl.getY() << ")"
       << ", width=" << r.getWidth()
       << ", height=" << r.getHeight()
       << ", color=" << r.getColor()
       << ")";
    return os;
}
