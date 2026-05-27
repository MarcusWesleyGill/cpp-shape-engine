#include "BoardRectangle.h"

void BoardRectangle::draw(DrawableSurface& board) {
    int color = 37;

    board.setGridChar(topLeft_.getX(), topLeft_.getY(), L'╔');
    board.setGridChar(topLeft_.getX() + width_ - 1, topLeft_.getY(), L'╗');
    board.setGridChar(topLeft_.getX(), topLeft_.getY() + height_ - 1, L'╚');
    board.setGridChar(topLeft_.getX() + width_ - 1, topLeft_.getY() + height_ - 1, L'╝');

    board.setGridColor(topLeft_.getX(), topLeft_.getY(), color);
    board.setGridColor(topLeft_.getX() + width_ - 1, topLeft_.getY(), color);
    board.setGridColor(topLeft_.getX(), topLeft_.getY() + height_ - 1, color);
    board.setGridColor(topLeft_.getX() + width_ - 1, topLeft_.getY() + height_ - 1, color);

    for (int x = topLeft_.getX() + 1; x < topLeft_.getX() + width_ - 1; x++) {
        board.setGridChar(x, topLeft_.getY(), L'═');
        board.setGridChar(x, topLeft_.getY() + height_ - 1, L'═');
        board.setGridColor(x, topLeft_.getY(), color);
        board.setGridColor(x, topLeft_.getY() + height_ - 1, color);
    }

    for (int y = topLeft_.getY() + 1; y < topLeft_.getY() + height_ - 1; y++) {
        board.setGridChar(topLeft_.getX(), y, L'║');
        board.setGridChar(topLeft_.getX() + width_ - 1, y, L'║');
        board.setGridColor(topLeft_.getX(), y, color);
        board.setGridColor(topLeft_.getX() + width_ - 1, y, color);
    }

    const wchar_t label[] = L"board";
    for (int i = 0; i < 5 && topLeft_.getX() + 1 + i < topLeft_.getX() + width_ - 1; i++) {
        board.setGridChar(topLeft_.getX() + 1 + i, topLeft_.getY(), label[i]);
        board.setGridColor(topLeft_.getX() + 1 + i, topLeft_.getY(), color);
    }
}

std::vector<Coord> BoardRectangle::getBoundaryCoords() const {
    return {topLeft_,
        {topLeft_.getX() + width_ - 1, topLeft_.getY()},
        {topLeft_.getX(), topLeft_.getY() + height_ - 1},
        {topLeft_.getX() + width_ - 1, topLeft_.getY() + height_ - 1}
    };
}
