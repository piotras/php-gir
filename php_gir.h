
#ifndef PHP_GIR_H
#define PHP_GIR_H

#define GIR_NAMESPACE "Gir"

#include <php.h>
#include <glib-object.h>
#include <girepository.h>
#include <girffi.h>

#include <zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

extern zend_module_entry gir_module_entry;
#define phpext_gir_ptr &gir_module_entry

#ifdef ZTS
# include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(gir);
PHP_MSHUTDOWN_FUNCTION(gir);
PHP_RINIT_FUNCTION(gir);
PHP_RSHUTDOWN_FUNCTION(gir);
PHP_MINFO_FUNCTION(gir);

ZEND_BEGIN_MODULE_GLOBALS(gir)
	GIRepository *repository;
ZEND_END_MODULE_GLOBALS(gir)

ZEND_EXTERN_MODULE_GLOBALS(gir)

#ifdef ZTS
# define GIR_G(v) TSRMG(gir_globals_id, zend_gobject_globals *, v)
#else
# define GIR_G(v) (gir_globals.v)
#endif

#endif /* PHP_GIR_H */

