#include "Coord.h"

Coord Coord::operator+(const Coord& c) {
    return Coord{this->getX() + c.getX(), this->getY() + c.getY()};
}

Coord Coord::operator-(const Coord& c) {
    return Coord{this->getX() - c.getX(), this->getY() - c.getY()};
}

Coord Coord::operator/(int d) {
    return Coord{this->getX()/d, this->getY()/d};
}

