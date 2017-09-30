#ifndef DRAWUTILS_H
#define DRAWUTILS_H

#include <cairo.h>
#include <cairo-xcb.h>
#include <stdio.h>
#include <unistd.h>
#include <ctime>

struct {
    uint16_t x, y;
    char c;
} passwdChar;

void drawClock(cairo_t *cr, uint16_t width, uint16_t height);
void drawPasswd(cairo_t *cr, uint16_t width, uint16_t height);

#endif
