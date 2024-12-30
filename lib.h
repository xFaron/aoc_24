#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Vec2D {
public:
    int x;
    int y;

    Vec2D();
    Vec2D(int xC, int yC);

    friend std::ostream& operator<< (std::ostream& outStream, const Vec2D& vec);
    friend bool operator== (const Vec2D& vec1, const Vec2D& vec2);
    friend bool operator!= (const Vec2D& vec1, const Vec2D& vec2);
    friend Vec2D operator+ (Vec2D pos1, const Vec2D pos2);
    friend Vec2D operator- (Vec2D pos1, const Vec2D pos2);
    friend Vec2D operator* (Vec2D pos1, const int num);
};

class Map {
private:
    std::vector<std::vector<char>> matrix;

public:
    Map(std::vector<std::vector<char>> map);

    int rowsLen() const;
    int colsLen() const;

    char at(const int x, const int y) const;
    char at(const Vec2D& vec) const;

    void change(const int x, const int y, char temp);
    void change(const Vec2D& vec, char temp);

    friend std::ostream& operator<< (std::ostream& outStream, const Map& map);
};

std::vector<std::vector<char>>& getInput(const std::string filename, std::vector<std::vector<char>>& matrix);

#endif // LIB_H