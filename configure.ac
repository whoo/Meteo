AC_INIT(Meteo,0)
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_HEADERS([config.h])     # not even really needed
AC_PROG_CC                        # or AC_PROG_CXX
PKG_CHECK_MODULES([JSON],[json-c])
AC_CONFIG_FILES([Makefile])
AC_SUBST(JSON_CFLAGS)
AC_SUBST(JSON_LIBS)
AC_OUTPUT
