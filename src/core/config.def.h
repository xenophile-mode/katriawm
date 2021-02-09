#ifndef _WM_CONFIG_H
#define _WM_CONFIG_H

char *dec_font = "Sans:pixelsize=10:style=bold:antialias=false";

struct WorkareaInsets wai = {
    .top = 20,
    .left = 0,
    .right = 0,
    .bottom = 20,
};

int gap_pixels = 5;
bool center_title = false;

struct Rule rules[] = {
    /* xprop(1):  WM_CLASS(STRING) = instance, class  */

    /* If both class and instance match a window, the defined actions
     * are taken. If "workspace", "monitor", "floating", or "decorated"
     * is -1, then the corresponding field is not changed. If "class" or
     * "instance" is NULL, then this field matches everything.
     *
     * "workspace" can be set to the special value -2, which will use
     * the currently active workspace on the target monitor.
     *
     * Both monitor indexes and workspace indexes start at 0. */

    /* class  instance  workspace  monitor  floating  decorated  enforced_title */
    {  NULL,  NULL,     -1,        -1,      -1,       -1,        NULL },
};

/* Have a look at ipc.h for valid values. */
enum LayoutAlgorithm default_layout = LATile;

/* When multiple monitors are connected to your workstation, you might
 * want to select different initial workspaces on each monitor. For
 * example, when 3 monitors are connected, select workspace 20 on
 * monitor 0, workspace 2 on monitor 1, and workspace 12 on monitor 3.
 * If none of these configurations matches, use default_workspace. */
int initial_workspaces[] = {
    2,  12, 2,      /* 2 monitors connected */
    3,  20, 2, 12,  /* 3 monitors connected */
};
int default_workspace = 1;

#endif /* _WM_CONFIG_H */
