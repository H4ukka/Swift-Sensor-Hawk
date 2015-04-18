#ifndef SCREEN_DRAWERH
#define SCREEN_DRAWERH

#include "vector.h"
#include <UTFT.h>

class ScreenDrawer {

public:
    ScreenDrawer ();
    //~MasterScreen ();

    void step_forward ();

    //Panel drawing functions
    void draw_panel (String);
    void draw_graph (short);
    void draw_sensor_box (short,short,short);

    //Screen parts
    void draw_temperature_box ();

    void set_color (short,short,short);

private:
    void clear_redraw_grid ();
    void draw_graph_frame ();
    void draw_graph_grid ();
    void draw_axis ();

    float step_;
    short previous_graph_coords_[2];

    short channel_R_;
    short channel_G_;
    short channel_B_;

    bool first_;

    short axis_min_;
    short axis_max_;
};

#endif