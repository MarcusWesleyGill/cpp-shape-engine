#pragma once
#include "Rectangle.h"
#include "Point.h"
#include "Diamond.h"
#include "BoardRectangle.h"
#include "DrawableSurface.h"
#include <vector>
#include <functional>

class Board : public DrawableSurface {
private:
    int width_;
    int height_;
    std::vector<Shape*> shapes_;
    wchar_t* grid_;
    int* colorGrid_;
    BoardRectangle border_;

public:
    Board();
    Board(int width, int height);
    ~Board();

    void display();
    void addRectangle(const Rectangle& rect);
    void addPoint(const Point& point);
    void addDiamond(const Diamond& diamond);
    void addShape(Shape* shape);

    Shape* getShape(char id);
    bool replaceShape(char id, Shape* replacement);

    void setGridChar(int x, int y, wchar_t ch) override;
    wchar_t getGridChar(int x, int y) override;
    void setGridColor(int x, int y, int color) override;
    int getGridColor(int x, int y) override;

    bool inBounds(const Shape* shape);
    void filterShapes(std::function<bool(const Shape*)> predicate);
    void transformShapes(std::function<Shape*(Shape*)> mapFunction);
};
