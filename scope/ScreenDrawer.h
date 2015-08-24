#ifndef SCREEN_DRAWERH
#define SCREEN_DRAWERH

#include <UTFT.h>
#include "Channel.h"

#define CENTER 0
#define LEFT 1
#define RIGHT 2

class ScreenDrawer {

public:
    ScreenDrawer ();

    void step_forward ();

    //Panel drawing functions
    void draw_view (String);
    void draw_graph (Channel *);
    void draw_sensor_box (short,short, Channel *);
    void draw_stats_box (short,short, Channel *);
    void draw_limit (Channel *);

    short view ();

    //Screen parts
    void draw_temperature_box ();

    void set_color (short,short,short);

    bool is_drawn_;

private:
    void clear_redraw_grid ();
    void draw_graph_frame ();
    void draw_graph_grid ();
    void draw_legend();
    void draw_axis ();

    void drawSettingsButton ();
    void drawDisplaysButton ();

    float convertd (short, Channel *);

    float step_;

    short axis_min_;
    short axis_max_;
    short _screen_height;
    short c_div;
    short _divs;

    float pixel_ratio_;

    short current_view_;

    bool reset_graph_on_update_;
};

#endif