# ----------------------------
# Makefile Options
# ----------------------------

NAME = ALCHEMY
DESCRIPTION = "Little Alchemy"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

SRCDIR = src/project
EXTRA_C_SOURCES = $(wildcard src/*.c src/gfx/*.c \
	src/oxygen/widget/*.c src/oxygen/widget/elements/*.c \
	src/oxygen/gfx/cursor*.c src/oxygen/gfx/charge.c) \
	src/oxygen/oxy_cursor.c src/oxygen/oxy_files.c src/oxygen/oxy_gfx.c \
	src/oxygen/oxy_gtk.c src/oxygen/oxy_gui.c src/oxygen/oxy_mouse.c src/oxygen/oxy_notify.c \
	src/oxygen/oxy_save.c src/oxygen/oxy_users.c

# ----------------------------

include $(shell cedev-config --makefile)