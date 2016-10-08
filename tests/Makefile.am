AM_CFLAGS = -Wall -Werror
check_PROGRAMS = test-repr test-rogueconf

test_repr_SOURCES = \
	../dhcpwn/repr.c \
	test-repr.c

test_rogueconf_SOURCES = \
	../dhcpwn/rogue.c \
	../dhcpwn/util.c \
	../dhcpwn/logging.c \
	test-rogueconf.c

TESTS = $(check_PROGRAMS)
