#pragma once

// Abstract base class (basically an interface)
class DrawableSurface {
public:
    virtual void setGridChar(int x, int y, wchar_t ch) = 0;
    virtual wchar_t getGridChar(int x, int y) = 0;

    virtual void setGridColor(int x, int y, int color) = 0;
    virtual int getGridColor(int x, int y) = 0;
};
