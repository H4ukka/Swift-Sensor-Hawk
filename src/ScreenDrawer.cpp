#include "ScreenDrawer.h"
#include "colors.h"

extern UTFT LCD0_;

extern uint8_t ArialNumFontPlus[];
extern uint8_t Sinclair_Inverted_S[];

ScreenDrawer::ScreenDrawer () {

	step_ = 0;
    first_ = true;

    axis_min_ = 0;
    axis_max_ = 99;
}

void ScreenDrawer::clear_redraw_grid () {

	LCD0_.setColor(DARK_GRAY);
    LCD0_.fillRect(41,1,398,119);

    draw_graph_grid ();
}

void ScreenDrawer::draw_graph_frame () {

	LCD0_.setColor(DARK_GRAY);
    LCD0_.fillRect(0,0,399,120);

    LCD0_.setColor(DEFAULT_RED);
    LCD0_.fillRect(0,0,40,120);
    LCD0_.setColor(DARK_RED);
    LCD0_.drawRect(40,0,399,120);

}

void ScreenDrawer::draw_graph_grid () {

	LCD0_.setColor(GRAY);

    // Vertical lines
    for (int i = 1; i <= 17; ++i) {
        LCD0_.drawLine(40+i*20,1,40+i*20,119);
    }

    // Horizontal lines
    for (int i = 1; i <= 5; ++i) {
        LCD0_.drawLine(41,120 - i*20,398,120 - i*20);
    }
}

void ScreenDrawer::draw_axis () {

    for (int i = 1; i <= 5; ++i) {

        LCD0_.setColor(WHITE);
        LCD0_.setBackColor(DEFAULT_RED);
        LCD0_.setFont(Sinclair_Inverted_S);
        LCD0_.printNumF((100/6)*i,1, 2, 120-i*20-4);
    }

    // LCD0_.print("`C", 5, 55);
}

void ScreenDrawer::draw_graph (short y_value) {

	LCD0_.setColor(channel_R_, channel_G_, channel_B_);

    if (first_) {

        previous_graph_coords_[0] = 0;
        previous_graph_coords_[1] = y_value;
        first_ = false;
    }else {
        LCD0_.drawLine(previous_graph_coords_[0],previous_graph_coords_[1],41+step_,119-y_value);
    }

    if (step_ >= 357) {

        step_ = 0;
        clear_redraw_grid ();
    }

    previous_graph_coords_[0] = 41+step_;
    previous_graph_coords_[1] = 119-y_value;
}

void ScreenDrawer::draw_panel (String panel_name) {

	if (panel_name == "MAIN_GRAPH") {
		draw_graph_frame ();
		draw_graph_grid ();
        draw_axis ();
	}else if (panel_name == "") {

	}
}

void ScreenDrawer::step_forward () {

	step_+=0.1;
}

void ScreenDrawer::draw_sensor_box (short xpos, short ypos, short value) {

    LCD0_.setColor(channel_R_, channel_G_, channel_B_);
    LCD0_.setBackColor(BLACK);
    //LCD0_.fillRect(xpos, ypos, xpos + 48, ypos + 20);
    LCD0_.setFont(ArialNumFontPlus);
    LCD0_.printNumI(value, xpos, ypos, 3, '0');
}

void ScreenDrawer::set_color (short r, short g, short b) {

    channel_R_ = r;
    channel_G_ = g;
    channel_B_ = b;
}