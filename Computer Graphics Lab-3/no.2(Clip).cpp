#include <graphics.h>
#include <conio.h>
#include <iostream>

using namespace std;

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

const int xmin = 100, ymin = 100, xmax = 300, ymax = 300;

int getRegionCode(int x, int y) {
    int regionCode = 0;
    if (x < xmin) regionCode |= LEFT;
    if (x > xmax) regionCode |= RIGHT;
    if (y < ymin) regionCode |= BOTTOM;
    if (y > ymax) regionCode |= TOP;
    return regionCode;
}

void applyMatrixTransformation(float matrix[2][2], int &x, int &y) {
    int newX = matrix[0][0] * x + matrix[0][1] * y;
    int newY = matrix[1][0] * x + matrix[1][1] * y;
    x = newX;
    y = newY;
}

void cohenSutherlandClip(int &x1, int &y1, int &x2, int &y2) {
    int regionCode1 = getRegionCode(x1, y1);
    int regionCode2 = getRegionCode(x2, y2);
    bool accept = false;

    float identityMatrix[2][2] = {{1, 0}, {0, 1}};

    while (true) {
        if ((regionCode1 | regionCode2) == 0) {
            accept = true;
            break;
        } else if (regionCode1 & regionCode2) {
            break;
        } else {
            int outsideRegionCode = regionCode1 ? regionCode1 : regionCode2;
            int x, y;

            if (outsideRegionCode & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (outsideRegionCode & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (outsideRegionCode & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            applyMatrixTransformation(identityMatrix, x, y);

            if (outsideRegionCode == regionCode1) {
                x1 = x;
                y1 = y;
                regionCode1 = getRegionCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                regionCode2 = getRegionCode(x2, y2);
            }
        }
    }
    if (accept) line(x1, y1, x2, y2);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*) "");

    rectangle(xmin, ymin, xmax, ymax);

    int x1, y1, x2, y2;
    cout << "Enter coordinates of the line (x1, y1, x2, y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    line(x1, y1, x2, y2);

    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}
