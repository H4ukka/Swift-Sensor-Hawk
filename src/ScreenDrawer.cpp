#include "ScreenDrawer.h"
#include "colors.h"

extern UTFT LCD0_;

extern uint8_t ArialNumFontPlus[];
extern uint8_t Sinclair_Inverted_S[];
extern uint8_t arial_normal[];
extern uint8_t franklingothic_normal[];

extern unsigned int settings[];

ScreenDrawer::ScreenDrawer () {

    step_ = 0;

    axis_min_ = 0;
    axis_max_ = 99;

    pixel_ratio_ = 0.75;

    current_view_ = CENTER;

    is_drawn_ = false;
    reset_graph_on_update_ = false;
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
        LCD0_.printNumI((160/6)*i, 8, 120-i*20-4,3);
    }

    // LCD0_.print("`C", 5, 55);
}

void ScreenDrawer::draw_graph (Channel *channel) {

    LCD0_.setColor(channel->R, channel->G, channel->B);

    //convert y to degrees
    float adj_value = convertd(channel->value);

    //convert degrees to pixels
    adj_value *= pixel_ratio_;

    //constrain pixel range
    adj_value = constrain(adj_value, 1, 119);

    if (reset_graph_on_update_) {

        step_ = 0;
        reset_graph_on_update_ = false;
    }

    if (step_ == 0) {

        channel->prev_X = 41;
        channel->prev_Y = adj_value;

    }else {

        // y = (y <= 0) ? 0 : (y >= 120) ? 117 : y;

        if (41 + step_ < 400)
            LCD0_.drawLine(channel->prev_X, channel->prev_Y,41+step_,120-adj_value);
    }

    channel->prev_X = 41+step_;
    channel->prev_Y = 120-adj_value;
}

void ScreenDrawer::draw_view (String panel_name) {

    cli();

    LCD0_.clrScr();
    is_drawn_ = false;

    if (panel_name == "MAIN_VIEW") {

        draw_graph_frame ();
        draw_graph_grid ();
        draw_axis ();
        draw_legend();

        drawSettingsButton ();
        drawDisplaysButton ();

        current_view_ = CENTER;
        reset_graph_on_update_ = true;
        is_drawn_ = true;
    }else if (panel_name == "LEFT_VIEW") {

        current_view_ = LEFT;
        is_drawn_ = true;
    }else if (panel_name == "RIGHT_VIEW") {

        current_view_ = RIGHT;
        is_drawn_ = true;
    }

    sei();
}

void ScreenDrawer::step_forward () {

    if (step_ >= 357) {

        step_ = 0;
        clear_redraw_grid ();

    }else{
        step_+=1;
    }
}

void ScreenDrawer::draw_sensor_box (short xpos, short ypos, Channel *channel) {

    xpos += 45;

    float adj_value = convertd(channel->value);

    LCD0_.setBackColor(channel->R, channel->G, channel->B);
    LCD0_.setColor(BLACK);
    LCD0_.setFont(ArialNumFontPlus);

    LCD0_.printNumI(adj_value, xpos, ypos, 3, '0');

    if(step_ >= 357) {

        channel->count = 1;
        channel->total = adj_value;
    }else{

        channel->total += adj_value;
        channel->count++;
    }
}

void ScreenDrawer::draw_stats_box (short xpos, short ypos, Channel *channel) {

    xpos += 45;

    float mean_value = channel->total / channel->count;

    LCD0_.setBackColor(channel->R, channel->G, channel->B);
    LCD0_.setColor(BLACK);
    LCD0_.setFont(arial_normal);

    LCD0_.printNumF(mean_value, 1, xpos, ypos, '.', 6);
    // BUG?! MIN MAX SWITCHED
    LCD0_.printNumF(convertd(channel->max), 1, xpos, ypos + 17, '.', 6);
    LCD0_.printNumF(convertd(channel->min), 1, xpos, ypos + 34, '.', 6);
}

float ScreenDrawer::convertd (short value) {

    //return (502 - value) * 1.494;
    return value;
}

void ScreenDrawer::draw_legend () {
    LCD0_.setColor(DEFAULT_RED);
    LCD0_.fillRect(0,120,39,239);

    LCD0_.setColor(BLACK);
    LCD0_.drawLine(0,175,39,175);
    LCD0_.drawLine(0,192,39,192);
    LCD0_.drawLine(0,209,39,209);
    LCD0_.drawLine(0,226,39,226);

    LCD0_.setColor(WHITE);

    LCD0_.setFont(franklingothic_normal);
    LCD0_.print("`C",0,141);

    LCD0_.setFont(Sinclair_Inverted_S);
    LCD0_.print("AVG",8,180);
    LCD0_.print("MIN",8,197);
    LCD0_.print("MAX",8,214);
}

void ScreenDrawer::drawSettingsButton () {

    LCD0_.setColor(DEFAULT_RED);
    LCD0_.fillRect(345, 176, 395, 225);

    LCD0_.drawBitmap(345, 176, 24, 24, settings);

}

void ScreenDrawer::drawDisplaysButton () {

    LCD0_.setColor(DEFAULT_RED);
    LCD0_.fillRect(345, 125, 395, 174);
}

short ScreenDrawer::view () {
    return current_view_;
}