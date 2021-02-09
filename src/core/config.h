#ifndef _WM_CONFIG_H
#define _WM_CONFIG_H

#ifdef SRVR_triton
char *dec_font = "Sans:pixelsize=10:style=bold:antialias=false";
#else
char *dec_font = "Screen-Medium:pixelsize=11";
#endif

struct WorkareaInsets wai = {
    /* Approximate bar height + some inset above/below */
    .top = 40,
    .left = 0,
    .right = 0,
    .bottom = 40,
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

    /* class                  instance          workspace  monitor  floating  decorated  enforced_title */
    {  "Avidemux2_gtk",       NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Gimp",                NULL,             11,        -1,       -1,      -1,        NULL    },
    {  "Gitk",                NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Hgk",                 NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "MPlayer",             NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "mpv",                 NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "qemu",                NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Qemu-system-x86_64",  NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Sxiv",                NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Remote-viewer",       NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "VirtualBox",          NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Browser-Calendar",    NULL,             22,         1,       -1,      -1,        NULL    },
    {  "Browser-Chat",        NULL,             14,         0,       -1,      -1,        "Chat"  },
    {  "Browser-Monitoring",  NULL,             22,         1,       -1,      -1,        NULL    },
    {  "Datenstrahler",       "monitoring",     22,         1,       -1,      -1,        "Mon"   },
    {  "Wine",                NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Xdialog",             NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Xephyr",              "Xephyr",         -1,        -1,        1,      -1,        NULL    },
    {  "Xpdf",                NULL,             -1,        -1,        1,      -1,        NULL    },
    {  "Xlonitor",            NULL,             21,        -1,       -1,      -1,        NULL    },
    {  "Browser-Audio",       NULL,             10,         0,       -1,      -1,        NULL    },
    {  NULL,                  "term-audio",     10,         0,       -1,      -1,        NULL    },
    {  NULL,                  "term-floating",  -1,        -1,        1,      -1,        NULL    },
    {  NULL,                  "term-irc",       12,         0,       -1,      -1,        NULL    },
    {  NULL,                  "term-jabber",    13,         0,       -1,      -1,        NULL    },
    {  NULL,                  "term-mtr",       20,         1,       -1,      -1,        NULL    },
    {  NULL,                  "term-main",      -2,         1,       -1,      -1,        NULL    },
    {  NULL,                  "term-mon",       22,         1,       -1,      -1,        NULL    },
};

/* Have a look at ipc.h for valid values. */
enum LayoutAlgorithm default_layout = LATile;

/* When multiple monitors are connected to your workstation, you might
 * want to select different initial workspaces on each monitor. For
 * example, when 3 monitors are connected, select workspace 20 on
 * monitor 0, workspace 2 on monitor 1, and workspace 12 on monitor 3.
 * If none of these configurations matches, use default_workspace. */
int initial_workspaces[] = {
    2,  1, 22,  /* 2 monitors connected */
};
int default_workspace = 2;

#endif /* _WM_CONFIG_H */
