#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <iostream>
#include "common.h"

void translate(int x, int y, int tx, int ty) {
    setcolor(YELLOW);
    line(x, y, x + 50, y);  // Draw original lines
    line(x, y, x, y - 50);

    setcolor(RED);  // Color for the translated lines
    x = x + tx;     // Apply translation on X-axis
    y = y + ty;     // Apply translation on Y-axis
    line(x, y, x + 50, y);  // Draw translated lines
    line(x, y, x, y - 50);
}

void scale(int x, int y, float sx, float sy) {
    setcolor(YELLOW);
    line(x, y, x + 50, y);  // Draw original lines
    line(x, y, x, y - 50);

    setcolor(RED);  // Color for the scaled lines
    line(x, y, x + 50 * sx, y);   // Scale lines on X-axis
    line(x, y, x, y - 50 * sy);   // Scale lines on Y-axis
}

void rotate(int x, int y, float angle) {
    setcolor(YELLOW);
    line(x, y, x + 50, y);  // Draw original lines
    line(x, y, x, y - 50);

    setcolor(RED);  // Color for the rotated lines
    float rad = angle * 3.14159 / 180;  // Convert degrees to radians
    line(x, y, x + 50 * cos(rad), y + 50 * sin(rad));  // Rotate line
    line(x, y, x - 50 * sin(rad), y + 50 * cos(rad));  // Rotate line
}

/*int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*) "");

    // Example usage
    translate(100, 100, 50, 50); // Translate by (50, 50)
    scale(300, 100, 1.5, 0.5);   // Scale by (1.5, 0.5)
    rotate(500, 100, 45);        // Rotate by 45 degrees

    getch();
    closegraph();
    return 0;
} */

