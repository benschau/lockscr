#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <X11/Xlib.h>
#include <inttypes.h>
#include <cairo.h>
#include <cairo-xcb.h>
#include <thread>

#include "drawutils.h"
#include "sysutils.h"

static xcb_visualtype_t *find_visual(xcb_connection_t *conn, xcb_visualid_t vis);
void xcb_event_handler(xcb_connection_t *conn);

int main (int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./lockscr [bg_path]");        

        return -1;
    } 

    xcb_connection_t *conn;
    xcb_screen_t *scr;
    xcb_drawable_t win;
    xcb_gcontext_t fg;
    xcb_ewmh_connection_t EWMH;
    xcb_intern_atom_cookie_t *cookie;
    xcb_visualtype_t *visual;
    cairo_surface_t *surface;
    cairo_t *cr;
    uint32_t mask;
    uint16_t width_p, height_p;
    const std::string bg_path = argv[1];
    
    if (!fpath_exists(bg_path)) {
        // set default background as white/black
        fprintf(stderr, "ERR: Couldn't find background path: %s.\nContinuing...", bg_path.c_str());
    }
    
    conn = xcb_connect(NULL, NULL);
    scr = xcb_setup_roots_iterator(xcb_get_setup(conn)).data;
    uint32_t values[2] = {scr->black_pixel, 0};
    win = scr->root;
    fg = xcb_generate_id(conn);
    mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    width_p = scr->width_in_pixels;
    height_p = scr->height_in_pixels;

    xcb_create_gc(conn, fg, win, mask, values);

    win = xcb_generate_id(conn);
    mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    values[0] = scr->black_pixel;
    values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;

    xcb_create_window(conn, 
                      XCB_COPY_FROM_PARENT,
                      win,
                      scr->root,
                      0, 0,
                      150, 150,
                      10,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      scr->root_visual,
                      mask,
                      values);

    cookie = xcb_ewmh_init_atoms(conn, &EWMH);

    if (!xcb_ewmh_init_atoms_replies(&EWMH, cookie, NULL)) {
        fprintf(stderr, "ERR: Couldn't inititalize cookie replies.");
        xcb_disconnect(conn);

        return -1;
    }

    xcb_change_property(conn, XCB_PROP_MODE_REPLACE, win, EWMH._NET_WM_STATE, XCB_ATOM_ATOM, 32, 1, &(EWMH._NET_WM_STATE_FULLSCREEN));
    xcb_map_window(conn, win);

    // set background image
    visual = find_visual(conn, scr->root_visual);
    if (visual == NULL) {
        fprintf(stderr, "ERR: Couldn't find screen visual.");
        xcb_disconnect(conn);
        
        return -1; 
    }
    surface = cairo_xcb_surface_create(conn, win, visual, width_p + 1, height_p + 1);
    cr = cairo_create(surface);
    cairo_surface_destroy(surface);
    
    // generate pw thing
    //passHandler();
    
    // event loop
    xcb_flush(conn);

    std::thread event(xcb_event_handler, conn); 
    
    struct timespec ts = {0, 5000000};

    while (true) {
        cairo_push_group(cr);
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);
    
        drawClock(cr, width_p, height_p); 

        cairo_pop_group_to_source(cr);
        cairo_paint(cr);
        cairo_surface_flush(surface);

        nanosleep(&ts, NULL);
    }  

    event.join();

    cairo_destroy(cr); 
    xcb_disconnect(conn);

    return EXIT_SUCCESS;
}

void xcb_event_handler(xcb_connection_t *conn) {
    xcb_generic_event_t *event;
    
    while ((event = xcb_wait_for_event(conn))) {
        switch (event->response_type & ~0x80) {
            case XCB_EXPOSE: 
                printf("EXPOSE");
                break;
            case XCB_BUTTON_PRESS: {
                   xcb_button_press_event_t *bp = (xcb_button_press_event_t *) event;
                   printf("BUTTON PRESS");

                   break;
            }
            default: 
               #ifdef DEBUG 
                    printf("DEFAULT\n");
               #endif
               break;
        }
    }

    free(event);
}

// xcb black magic
static xcb_visualtype_t *find_visual(xcb_connection_t *conn, xcb_visualid_t vis) {
    xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(xcb_get_setup(conn));
    
    for (; screen_iter.rem; xcb_screen_next(&screen_iter)) {
        xcb_depth_iterator_t depth_iter = xcb_screen_allowed_depths_iterator(screen_iter.data);
        
        for (; depth_iter.rem; xcb_depth_next(&depth_iter)) {
            xcb_visualtype_iterator_t visual_iter = xcb_depth_visuals_iterator(depth_iter.data);
            if (vis == visual_iter.data->visual_id)
                return visual_iter.data; 
        }
    }

    return NULL;
}
