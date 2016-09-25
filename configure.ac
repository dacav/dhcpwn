#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([dhcpwn], [0.0.1], [dacav@openmailbox.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([dhcpwn/dhcpwn.c])
AC_CONFIG_HEADERS([dhcpwn/config.h])
AC_CONFIG_FILES([
    Makefile
    dhcpwn/Makefile
    tests/Makefile
])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([pcap], [pcap_create])

# Checks for header files.
AC_CHECK_HEADERS([pcap/pcap.h], [],
    AC_MSG_ERROR([Cannot find libpcap headers])
)

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
