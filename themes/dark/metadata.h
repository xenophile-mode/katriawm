static char *dec_font_colors[] = {
    "#555555",  /* DecStateNormal */
    "#FFFFFF",  /* DecStateSelect */
    "#FFFFFF",  /* DecStateUrgent */
};

static struct DecorationGeometry dgeo = {
    .top_height = 28,
    .left_width = 6,
    .right_width = 6,
    .bottom_height = 6,
};

static struct SubImage dec_coords[] = {
    { .x =  13, .y = 27, .w =  7, .h = 28 },  /* DecTopLeft */
    { .x =  25, .y = 27, .w = 70, .h = 28 },  /* DecTop */
    { .x = 107, .y = 27, .w =  7, .h = 28 },  /* DecTopRight */

    { .x =  13, .y = 60, .w = 6, .h = 40 },  /* DecLeft */
    { .x = 108, .y = 60, .w = 6, .h = 40 },  /* DecRight */

    { .x =  13, .y = 101, .w =  6, .h = 6 },  /* DecBottomLeft */
    { .x =  20, .y = 101, .w = 70, .h = 6 },  /* DecBottom */
    { .x = 108, .y = 101, .w =  6, .h = 6 },  /* DecBottomRight */
};

static bool dec_has_title = true;
static struct TitleArea dec_title = {
    .left_offset = 12,
    .right_offset = 12,
    .baseline_top_offset = 21,
};
