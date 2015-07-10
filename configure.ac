AC_INIT(Meteo,0)
AC_CONFIG_SRCDIR([configure.ac])
#AC_CONFIG_HEADERS([config.h])     # not even really needed
AC_PROG_CC                        # or AC_PROG_CXX

PKG_CHECK_MODULES([JSON],[json-c],json=1,json=0)
PKG_CHECK_MODULES([JSON],[json],json=1,json=0) 
PKG_CHECK_MODULES([CURL],[libcurl])

AC_CHECK_LIB([curl], [curl_easy_perform])

AC_CHECK_HEADERS([stddef.h stdlib.h string.h unistd.h])
AC_CHECK_FUNC(sleep)
AC_FUNC_MALLOC
AC_TYPE_SIZE_T
#PKG_CHECK_MODULES([CURL],[curl])
AC_CONFIG_FILES([Makefile])
AC_SUBST(JSON_CFLAGS)
AC_SUBST(JSON_LIBS)
AC_SUBST(CURL_LIBS)
AC_OUTPUT

