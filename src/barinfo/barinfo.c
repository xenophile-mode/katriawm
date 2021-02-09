#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>

#include "util.h"
#include "ipc.h"

#include "config.h"

enum OutputFormat
{
    OutputBevelbar,

    OutputLAST,
};

static bool
check_size(unsigned char *state, unsigned long nitems, unsigned long *size,
           int *size_monws)
{
    int monitors_num;

    *size_monws = STATE_BYTES_PER_WORKSPACE;

    if (nitems < 1)
    {
        D fprintf(stderr, __NAME_BI__": Not a single byte read from property\n");
        return false;
    }

    monitors_num = state[0];

    /* This must match publish_state() in wm.c */
    *size = 1 + 1 + 1 + 1 + monitors_num * 2 + monitors_num * *size_monws * 2;

    if (nitems != *size)
    {
        fprintf(stderr, __NAME_BI__": Expected %lu bytes, got %lu\n", *size,
                nitems);
        return false;
    }

    return true;
}

static char *
resolve_ws_name(int ws_num)
{
    size_t l = 64;
    char *out;

    out = ecalloc(l, sizeof (char));

    if (ws_num >= WORKSPACE_MIN && ws_num <= WORKSPACE_MAX && ws_names[ws_num])
        snprintf(out, l - 1, "%d:%s", ws_num, ws_names[ws_num]);
    else
        snprintf(out, l - 1, "%d", ws_num);

    return out;
}

static unsigned char *
state_read(Display *dpy, Window root, Atom atom, unsigned long *nitems)
{
    Atom da;
    unsigned char *prop_ret = NULL;
    int di;
    unsigned long dl;

    /* Reading at most 4096 is kind of arbitrary, but large enough to
     * hold information for over 100 monitors */
    if (XGetWindowProperty(dpy, root, atom, 0, 4096, False,
                           XA_INTEGER, &da, &di, nitems, &dl, &prop_ret)
        == Success)
    {
        if (prop_ret)
        {
            return prop_ret;
        }
    }

    return NULL;
}

static void
state_to_bevelbar(unsigned char *state, unsigned long nitems)
{
    /* This function depends on the format used in publish_state() in
     * core/wm.c, which is also documented in doc/DOCUMENTATION.md */

    int monitors_num, selmon_i, size_monws, mute_urgency, i;
    int offset_ws, ws_num, byte_i, bit, active_workspace;
    unsigned long size;
    unsigned char byte, ubyte, slots_mask, mask;
    char *ws_num_display = NULL;
    size_t num_static_flags;

    /* First check if nitems matches what we expect. Also sets "size"
     * and "size_monws". */
    if (!check_size(state, nitems, &size, &size_monws))
        return;

    /* We're good to go, so decode the beast */
    monitors_num = state[0];
    selmon_i = state[1];
    slots_mask = state[2];
    mute_urgency = state[3];
    num_static_flags = 4;

    for (i = 0; i < monitors_num; i++)
    {
        active_workspace = state[num_static_flags + i];

        /* Layout icon and monitor selection */
        printf("%d\n", i);
        printf("%d%s\n", i == selmon_i ? 1 : 0,
               layout_names[state[num_static_flags + i + monitors_num]]);
        printf("-\n");

        /* Occupied tags, urgency hints */
        offset_ws = num_static_flags + monitors_num + monitors_num + i * size_monws;
        ws_num = 0;
        for (byte_i = 0; byte_i < size_monws; byte_i++)
        {
            byte = state[offset_ws + byte_i];
            ubyte = state[offset_ws + byte_i + monitors_num * size_monws];
            mask = 1;
            for (bit = 0; bit < 8; bit++)
            {
                if (ws_num_display)
                    free(ws_num_display);
                ws_num_display = resolve_ws_name(ws_num);

                if (ubyte & mask)
                    printf("%d%s\n", ws_num == active_workspace ? 5 : 4,
                           ws_num_display);
                else
                {
                    if (ws_num == active_workspace)
                        printf("%d%s\n", 3, ws_num_display);
                    else if (byte & mask)
                        printf("%d%s\n", 2, ws_num_display);
                }

                ws_num++;
                mask <<= 1;
            }
        }

        /* Save slots */
        if (i == selmon_i && slots_mask)
        {
            printf("-\n");
            mask = 1;
            for (bit = 0; bit < 8; bit++)
            {
                if (slots_mask & mask)
                    printf("%d%d\n", 2, bit);
                mask <<= 1;
            }
        }

        /* Urgency muted? */
        if (i == selmon_i && mute_urgency)
        {
            printf("-\n");
            printf("%dmute\n", 2);
        }

        printf("e\n");
    }
    printf("f\n");
    fflush(stdout);
}

int
main(int argc, char **argv)
{
    Display *dpy;
    Window root;
    XEvent e;
    XPropertyEvent *ev;
    Atom atom_state;
    unsigned char *state = NULL;
    unsigned long state_nitems, i;
    enum OutputFormat of = OutputBevelbar;
    void (*formatter[OutputLAST])(unsigned char *state, unsigned long nitems) = {
        [OutputBevelbar] = state_to_bevelbar,
    };

    /* Currently, there is no formatter other than the one for bevelbar,
     * so we don't evaluate argv at all */
    (void)argc;
    (void)argv;

    if (!(dpy = XOpenDisplay(NULL)))
        return 1;

    root = DefaultRootWindow(dpy);
    atom_state = XInternAtom(dpy, IPC_ATOM_STATE, False);

    XSelectInput(dpy, root, PropertyChangeMask);

    state = state_read(dpy, root, atom_state, &state_nitems);
    if (state)
        formatter[of](state, state_nitems);

    /* All we do is sit here and wait for the property to change */
    for (;;)
    {
        XNextEvent(dpy, &e);
        if (e.type == PropertyNotify)
        {
            ev = &e.xproperty;
            if (ev->atom == atom_state)
            {
                D fprintf(stderr, __NAME_BI__": State atom changed!\n");

                if (state)
                    XFree(state);
                state = state_read(dpy, root, atom_state, &state_nitems);

                D
                {
                    fprintf(stderr, __NAME_BI__": Bytes read: ");
                    for (i = 0; i < state_nitems; i++)
                        fprintf(stderr, "%02X ", state[i]);
                    fprintf(stderr, "\n");
                }

                if (state)
                    formatter[of](state, state_nitems);
            }
        }
    }
}
