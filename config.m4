dnl  Copyright (C) 2007 Piotr Pokora <piotrek.pokora@gmail.com>
dnl  Copyright (C) 2010 Alexey Zakhlestin <indeyets@gmail.com>
dnl 
dnl  This program is free software; you can redistribute it and/or modify it
dnl  under the terms of the GNU Lesser General Public License as published
dnl  by the Free Software Foundation; either version 2 of the License, or
dnl  (at your option) any later version.
dnl 
dnl  This program is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl  GNU General Public License for more details.
dnl 
dnl  You should have received a copy of the GNU General Public License
dnl  along with this program; if not, write to the Free Software
dnl  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

PHP_ARG_WITH(gir, for introspection support,
[  --with-gir        Enable gir support], yes)

if test "$PHP_GIR" != "no"; then
    if test -z "$PKG_CONFIG"; then
        AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
    fi

    if test -f "$PKG_CONFIG"; then
        if $PKG_CONFIG --atleast-version=1.32 gobject-introspection-1.0; then
            GIR_INCLINE=`$PKG_CONFIG --cflags gobject-introspection-1.0`
            GIR_LIBLINE=`$PKG_CONFIG --libs gobject-introspection-1.0`
        else
            AC_MSG_ERROR([GObject Introspection version 1.32 or greater required.])
        fi

        PHP_EVAL_INCLINE($GIR_INCLINE)
        PHP_EVAL_LIBLINE($GIR_LIBLINE, GIR_SHARED_LIBADD)

        CFLAGS="$CFLAGS -Wall -fno-strict-aliasing"

        if test "$php_always_shared" = "yes"; then
            AC_DEFINE(MGD_INCLUDE_PHP_CONFIG, 1, [ ])
        fi

        PHP_SUBST(GIR_SHARED_LIBADD)
        AC_DEFINE(HAVE_GIR, 1, [ ])

        PHP_NEW_EXTENSION(gir, \
	    php_gir.c, $ext_shared)
        PHP_ADD_EXTENSION_DEP(gir, spl)
    else
        AC_MSG_ERROR(Ooops ! no pkg-config found .... )
    fi
fi
