#include "Board.h"
#include <iostream>
#include <algorithm>

using std::endl;
using std::wcout;

Board::Board() : Board(50, 20) {}

Board::Board(int width, int height)
    : width_(width), height_(height), border_{{0, 0}, width_, height_}
{
    grid_ = new wchar_t[width_ * height_];
    colorGrid_ = new int[width_ * height_];
    shapes_.reserve(10);
}

Board::~Board()
{
    delete[] grid_;
    delete[] colorGrid_;

    for (Shape* shape : shapes_)
    {
        delete shape;
    }
}

bool Board::inBounds(const Shape* shape)
{
    std::vector<Coord> coords = shape->getBoundaryCoords();
    return std::all_of(coords.begin(), coords.end(), [&](const Coord& c) {
        return c.getX() >= 0 && c.getY() >= 0 &&
               c.getX() < width_ && c.getY() < height_;
    });
}

void Board::addShape(Shape* shape)
{
    if (!inBounds(shape))
    {
        delete shape;
        throw std::out_of_range("Shape is outside of board bounds");
    }

    shapes_.push_back(shape);
}

void Board::addRectangle(const Rectangle& rect)
{
    if (!inBounds(&rect))
    {
        throw std::out_of_range("Rectangle is out of bounds");
    }

    for (Shape* s : shapes_)
    {
        if (auto r = dynamic_cast<Rectangle*>(s))
        {
            if (rect.intersectsWith(*r))
            {
                throw std::logic_error("Rectangle intersects with existing rectangle");
            }
        }
    }

    shapes_.push_back(new Rectangle(rect));
}

void Board::addPoint(const Point& point)
{
    if (!inBounds(&point))
    {
        throw std::out_of_range("Point is outside of board bounds");
    }

    for (Shape* s : shapes_)
    {
        if (auto r = dynamic_cast<Rectangle*>(s))
        {
            if (r->containsPoint(point))
            {
                throw std::logic_error("Point is contained by an existing rectangle");
            }
        }
    }

    shapes_.push_back(new Point(point));
}

void Board::addDiamond(const Diamond& diamond)
{
    if (!inBounds(&diamond))
    {
        throw std::out_of_range("Diamond is outside of board bounds");
    }

    shapes_.push_back(new Diamond(diamond));
}

Shape* Board::getShape(char id)
{
    auto it = std::find_if(shapes_.begin(), shapes_.end(), [&](Shape* shape) {
        return shape->getId() == id;
    });

    if (it == shapes_.end())
    {
        return nullptr;
    }

    return *it;
}

bool Board::replaceShape(char id, Shape* replacement)
{
    if (!inBounds(replacement))
    {
        delete replacement;
        throw std::out_of_range("Replacement shape is outside of board bounds");
    }

    for (Shape*& shape : shapes_)
    {
        if (shape->getId() == id)
        {
            delete shape;
            shape = replacement;
            return true;
        }
    }

    delete replacement;
    return false;
}

void Board::display()
{
    for (int row = 0; row < height_; row++)
    {
        for (int col = 0; col < width_; col++)
        {
            setGridChar(col, row, L' ');
            setGridColor(col, row, 37);
        }
    }

    border_.draw(*this);

    for (Shape* shape : shapes_)
    {
        shape->draw(*this);
    }

    int currentColor = -1;
    for (int row = 0; row < height_; row++)
    {
        for (int col = 0; col < width_; col++)
        {
            int nextColor = getGridColor(col, row);
            if (nextColor != currentColor)
            {
                wcout << L"\033[" << nextColor << L"m";
                currentColor = nextColor;
            }
            wcout << getGridChar(col, row);
        }
        wcout << L"\033[0m" << endl;
        currentColor = -1;
    }

    int numRectangles = std::count_if(shapes_.begin(), shapes_.end(), [](Shape* s) {
        return dynamic_cast<Rectangle*>(s) != nullptr;
    });
    int numPoints = std::count_if(shapes_.begin(), shapes_.end(), [](Shape* s) {
        return dynamic_cast<Point*>(s) != nullptr;
    });
    int numDiamonds = std::count_if(shapes_.begin(), shapes_.end(), [](Shape* s) {
        return dynamic_cast<Diamond*>(s) != nullptr;
    });

    wcout << L"\033[0m";
    wcout << "Rectangles: " << numRectangles
          << ", Points: " << numPoints
          << ", Diamonds: " << numDiamonds
          << ", Total shapes: " << shapes_.size() << endl;
}

void Board::setGridChar(int x, int y, wchar_t c)
{
    if (x >= 0 && y >= 0 && x < width_ && y < height_)
    {
        grid_[y * width_ + x] = c;
    }
}

wchar_t Board::getGridChar(int x, int y)
{
    return grid_[y * width_ + x];
}

void Board::setGridColor(int x, int y, int color)
{
    if (x >= 0 && y >= 0 && x < width_ && y < height_)
    {
        colorGrid_[y * width_ + x] = color;
    }
}

int Board::getGridColor(int x, int y)
{
    return colorGrid_[y * width_ + x];
}

void Board::filterShapes(std::function<bool(const Shape*)> predicate)
{
    std::vector<Shape*> keptShapes;

    for (Shape* shape : shapes_)
    {
        if (predicate(shape))
        {
            keptShapes.push_back(shape);
        }
        else
        {
            delete shape;
        }
    }

    shapes_ = keptShapes;
}

void Board::transformShapes(std::function<Shape*(Shape*)> mapFunction)
{
    std::transform(shapes_.begin(), shapes_.end(), shapes_.begin(), [&](Shape* shape) {
        Shape* newShape = mapFunction(shape);
        if (newShape != shape)
        {
            delete shape;
        }
        return newShape;
    });
}
