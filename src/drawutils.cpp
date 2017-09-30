#include "drawutils.h"

void drawClock(cairo_t *cr, uint16_t height, uint16_t width) {
    time_t rawtime;
    struct tm *timeinfo; 
    cairo_text_extents_t extents;
     
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //printf("%s", asctime(timeinfo));
    
    cairo_select_font_face(cr, "Inconsolata",
            CAIRO_FONT_SLANT_NORMAL,
            CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_text_extents(cr, asctime(timeinfo), &extents);
    
    // center text
    //cairo_move_to(cr, x / 2 - extents.width / 2, y / 2);
    // bottom left
    cairo_move_to(cr, 10, width - extents.height * 2);
    
    cairo_show_text(cr, asctime(timeinfo)); 
}

void drawPasswd(cairo_t *cr, uint16_t height, uint16_t width) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 0.5);

}
