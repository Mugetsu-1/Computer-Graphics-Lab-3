#include <graphics.h>
#include <conio.h>
#include <iostream>

using namespace std;

#define LEFT 1       // 1 in binary is 0001
#define RIGHT 2      // 2 in binary is 0010
#define BOTTOM 4     // 4 in binary is 0100
#define TOP 8        // 8 in binary is 1000

const int xmin = 100, ymin = 100, xmax = 300, ymax = 300;

int getRegionCode(int x, int y) {
    int regionCode = 0;
    if (x < xmin) regionCode |= LEFT;
    if (x > xmax) regionCode |= RIGHT;
    if (y < ymin) regionCode |= BOTTOM;
    if (y > ymax) regionCode |= TOP;
    return regionCode;
}

void cohenSutherlandClip(int &x1, int &y1, int &x2, int &y2) {
    int regionCode1 = getRegionCode(x1, y1), regionCode2 = getRegionCode(x2, y2);
    bool accept = false;

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

            // Update the endpoint outside the rectangle
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

    // Draw the clipping rectangle
    rectangle(xmin, ymin, xmax, ymax);

    // Get the coordinates for the line segment from the user
    int x1, y1, x2, y2;
    cout << "Enter coordinates of the line (x1, y1, x2, y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    // Draw the original line
    line(x1, y1, x2, y2);

    // Clip the line using Cohen-Sutherland algorithm
    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}

