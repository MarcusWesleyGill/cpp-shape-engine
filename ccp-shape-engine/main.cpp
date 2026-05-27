#include "Board.h"
#include "Rectangle.h"
#include "Point.h"
#include "Diamond.h"
#include <iostream>
#include <locale>
#include <limits>

using std::endl;
using std::wcin;
using std::wcout;

// Tasks completed for this assignment:
// 1. Add color to shapes
// 2. Add additional shape (Diamond)
// 3. Modify shapes by id

void showColorMenu()
{
    wcout << "Color options:" << endl;
    wcout << "31: Red" << endl;
    wcout << "32: Green" << endl;
    wcout << "33: Yellow" << endl;
    wcout << "34: Blue" << endl;
    wcout << "35: Magenta" << endl;
    wcout << "36: Cyan" << endl;
    wcout << "37: White" << endl;
}

int getColorFromUser()
{
    int color;
    showColorMenu();
    wcout << "Enter color number: ";
    wcin >> color;

    if (color < 31 || color > 37)
    {
        color = 37;
    }

    return color;
}

char getIdFromUser()
{
    wchar_t wideId;
    wcin >> wideId;
    return static_cast<char>(wideId);
}

void addRectangleMenu(Board& board)
{
    int x, y, width, height;
    char id;

    wcout << "Enter rectangle id: ";
    id = getIdFromUser();
    wcout << "Enter top left x y: ";
    wcin >> x >> y;
    wcout << "Enter width and height: ";
    wcin >> width >> height;
    int color = getColorFromUser();

    board.addRectangle(Rectangle(Coord(x, y), width, height, id, color));
}

void addPointMenu(Board& board)
{
    int x, y;
    char id;

    wcout << "Enter point id: ";
    id = getIdFromUser();
    wcout << "Enter x y: ";
    wcin >> x >> y;
    int color = getColorFromUser();

    board.addPoint(Point(x, y, id, color));
}

void addDiamondMenu(Board& board)
{
    int x, y, radius;
    char id;

    wcout << "Enter diamond id: ";
    id = getIdFromUser();
    wcout << "Enter center x y: ";
    wcin >> x >> y;
    wcout << "Enter radius: ";
    wcin >> radius;
    int color = getColorFromUser();

    board.addDiamond(Diamond(Coord(x, y), radius, id, color));
}

void modifyShapeMenu(Board& board)
{
    char id;
    wcout << "Enter id to change: ";
    id = getIdFromUser();

    Shape* shape = board.getShape(id);
    if (shape == nullptr)
    {
        wcout << "Shape not found." << endl;
        return;
    }

    if (Rectangle* rect = dynamic_cast<Rectangle*>(shape))
    {
        Coord topLeft = rect->getTopLeft();
        wcout << "Rectangle " << rect->getId()
              << " top left: " << topLeft.getX() << " " << topLeft.getY()
              << " width: " << rect->getWidth()
              << " height: " << rect->getHeight()
              << " color: " << rect->getColor() << endl;

        int x, y, width, height;
        wcout << "Enter new top left x y width height: ";
        wcin >> x >> y >> width >> height;
        int color = getColorFromUser();

        board.replaceShape(id, new Rectangle(Coord(x, y), width, height, id, color));
    }
    else if (Point* point = dynamic_cast<Point*>(shape))
    {
        wcout << "Point " << point->getId()
              << " x: " << point->getX()
              << " y: " << point->getY()
              << " color: " << point->getColor() << endl;

        int x, y;
        wcout << "Enter new x y: ";
        wcin >> x >> y;
        int color = getColorFromUser();

        board.replaceShape(id, new Point(x, y, id, color));
    }
    else if (Diamond* diamond = dynamic_cast<Diamond*>(shape))
    {
        Coord center = diamond->getCenterCoord();
        wcout << "Diamond " << diamond->getId()
              << " center: " << center.getX() << " " << center.getY()
              << " radius: " << diamond->getRadius()
              << " color: " << diamond->getColor() << endl;

        int x, y, radius;
        wcout << "Enter new center x y radius: ";
        wcin >> x >> y >> radius;
        int color = getColorFromUser();

        board.replaceShape(id, new Diamond(Coord(x, y), radius, id, color));
    }
}

int main()
{
    std::setlocale(LC_ALL, "en_US.UTF-8");

    int width = 50;
    int height = 20;

    wcout << "Enter board width and height: ";
    if (!(wcin >> width >> height))
    {
        return 0;
    }

    Board board(width, height);

    int choice = -1;
    while (choice != 0)
    {
        wcout << endl;
        board.display();
        wcout << endl;
        wcout << "What would you like to do?" << endl;
        wcout << "1: Add Rectangle" << endl;
        wcout << "2: Add Point" << endl;
        wcout << "3: Add Diamond" << endl;
        wcout << "4: Modify Shape by id" << endl;
        wcout << "0: Quit" << endl;
        wcout << "Enter choice: ";
        wcin >> choice;

        try
        {
            if (choice == 1)
            {
                addRectangleMenu(board);
            }
            else if (choice == 2)
            {
                addPointMenu(board);
            }
            else if (choice == 3)
            {
                addDiamondMenu(board);
            }
            else if (choice == 4)
            {
                modifyShapeMenu(board);
            }
            else if (choice != 0)
            {
                wcout << "Invalid choice." << endl;
            }
        }
        catch (const std::exception& e)
        {
            wcout << "Error: " << e.what() << endl;
        }
    }

    wcout << "Final board:" << endl;
    board.display();

    return 0;
}
