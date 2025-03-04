#ifndef COMMON_H
#define COMMON_H


// Function prototypes
void translate(int x, int y, int tx, int ty);  // Translate point (x, y) by tx, ty
void scale(int x, int y, float sx, float sy);  // Scale point (x, y) by sx, sy
void rotate(int x, int y, float angle);        // Rotate point (x, y) by angle
int getRegionCode(int x, int y);               // Get region code for point (x, y)
void cohenSutherlandClip(int &x1, int &y1, int &x2, int &y2); // Cohen-Sutherland line clipping

#endif 

