# To enable debug output:
#DEBUG_CPPFLAGS = -DDEBUG
#DEBUG_CFLAGS = -g

INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644

prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
datarootdir = $(prefix)/share
mandir = $(datarootdir)/man
man1dir = $(mandir)/man1

# The source code itself shall include as little verbatim references to
# the project name as possible.
__NAME__ = katria
__NAME_WM__ = katriawm
__NAME_C__ = katriac
__NAME_BI__ = katriabi

__NAME_UPPERCASE__ = KATRIA
__NAME_CAPITALIZED__ = Katria

__NAME_WM_UPPERCASE__ = KATRIAWM
__NAME_WM_CAPITALIZED__ = Katriawm

__NAME_C_UPPERCASE__ = KATRIAC
__NAME_C_CAPITALIZED__ = Katriac

__NAME_BI_UPPERCASE__ = KATRIABI
__NAME_BI_CAPITALIZED__ = Katriabi

NAME_DEFINES = \
		-D__NAME__=\"$(__NAME__)\" \
		-D__NAME_UPPERCASE__=\"$(__NAME_UPPERCASE__)\" \
		-D__NAME_CAPITALIZED__=\"$(__NAME_CAPITALIZED__)\" \
		-D__NAME_WM__=\"$(__NAME_WM__)\" \
		-D__NAME_WM_UPPERCASE__=\"$(__NAME_WM_UPPERCASE__)\" \
		-D__NAME_WM_CAPITALIZED__=\"$(__NAME_WM_CAPITALIZED__)\" \
		-D__NAME_C__=\"$(__NAME_C__)\" \
		-D__NAME_C_UPPERCASE__=\"$(__NAME_C_UPPERCASE__)\" \
		-D__NAME_C_CAPITALIZED__=\"$(__NAME_C_CAPITALIZED__)\" \
		-D__NAME_BI__=\"$(__NAME_BI__)\" \
		-D__NAME_BI_UPPERCASE__=\"$(__NAME_BI_UPPERCASE__)\" \
		-D__NAME_BI_CAPITALIZED__=\"$(__NAME_BI_CAPITALIZED__)\"

# Flags used in rules.
CPPFLAGS += $(NAME_DEFINES) -DSRVR_$$HOSTNAME $(DEBUG_CPPFLAGS)
CFLAGS += -std=c99 -Wall -Wextra -O3 $(DEBUG_CFLAGS)
CFLAGS += -Icore -Iinclude `pkg-config --cflags x11 xrandr xft`
LDFLAGS += `pkg-config --libs x11 xrandr xft`
