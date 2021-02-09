static char *dec_font_colors[] = {
    "#AAAAAA",  /* DecStateNormal */
    "#000000",  /* DecStateSelect */
    "#000000",  /* DecStateUrgent */
};

static struct DecorationGeometry dgeo = {
    .top_height = 22,
    .left_width = 5,
    .right_width = 5,
    .bottom_height = 5,
};

static struct SubImage dec_coords[] = {
    { .x = 9,  .y = 9, .w = 22, .h = 22 },  /* DecTopLeft */
    { .x = 40, .y = 9, .w = 35, .h = 22 },  /* DecTop */
    { .x = 76, .y = 9, .w = 22, .h = 22 },  /* DecTopRight */

    { .x = 9,  .y = 35, .w = 5, .h = 15 },  /* DecLeft */
    { .x = 93, .y = 35, .w = 5, .h = 15 },  /* DecRight */

    { .x = 9,  .y = 56, .w = 22, .h = 22 },  /* DecBottomLeft */
    { .x = 35, .y = 73, .w = 35, .h = 5 },   /* DecBottom */
    { .x = 76, .y = 56, .w = 22, .h = 22 },  /* DecBottomRight */
};

static bool dec_has_title = true;
static struct TitleArea dec_title = {
    .left_offset = 9,
    .right_offset = 9,
    .baseline_top_offset = 17,
};
