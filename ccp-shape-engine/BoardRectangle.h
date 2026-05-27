#pragma once
#include "DrawableSurface.h"
#include "Shape.h"
#include "Coord.h"


class BoardRectangle : public Shape {
    private:
        Coord topLeft_;
        int width_;
        int height_;

    public:
        BoardRectangle(Coord topLeft, int width, int height) 
            : topLeft_(topLeft)
            , width_(width)
            , height_(height) { }

        Coord getTopLeft() { return topLeft_; }
        void setTopLeft(Coord& Coord) { topLeft_ = Coord; }

        int getWidth() { return width_; }
        void setWidth(int width) { width_ = width; }

        int getHeight() { return height_; }
        void setHeight(int height) { height_ = height; }

        void draw(DrawableSurface& board) override;
        std::vector<Coord> getBoundaryCoords() const override;

};

