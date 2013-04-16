
#include "php_gir.h"

#include <ext/standard/info.h>

ZEND_DECLARE_MODULE_GLOBALS(gir)

zend_function_entry php_gir_functions[] = {
	PHP_NAMED_FE(gir\\load, PHP_FN(php_gir_load), NULL)
	{NULL, NULL, NULL}
};

zend_module_entry gir_module_entry = {
	STANDARD_MODULE_HEADER,
	"gir",
	php_gir_functions,
	PHP_MINIT(gir),
	PHP_MSHUTDOWN(gir),
	PHP_RINIT(gir),
	PHP_RSHUTDOWN(gir),
	PHP_MINFO(gir),
	NULL,
	PHP_MODULE_GLOBALS(gir),
	NULL,
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

PHP_FUNCTION(php_gir_load)
{
	char *namespace = NULL, *version = NULL;
	int namespace_length, version_length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", 
				&namespace, &namespace_length, &version, &version_length) == FAILURE) 
		return;

	if (GIR_G(repository) == NULL)
		GIR_G(repository) = g_irepository_get_default();

	GIRepository *gir = GIR_G(repository);
		
	if (g_irepository_is_registered(gir, namespace, version))
		RETURN_TRUE;

	GError *err = NULL;
	GITypelib *type_lib = g_irepository_require(gir, namespace, version, 0, &err);

	if (err) {
		zend_throw_exception_ex(spl_ce_OutOfBoundsException, 0 TSRMLS_CC, 
				"Failed to load \"%s\" namespace: %s", namespace, 
				err->message ? err->message : "Unknown reason");
		g_error_free(err);
		return;
	}

	int n = g_irepository_get_n_infos(gir, namespace);
	int i;
	for (i = 0; i < n; i++) {
		GIBaseInfo *info = g_irepository_get_info(gir, namespace, i);
		GIInfoType info_type = g_base_info_get_type(info);
		
		switch (info_type) {

		}
		g_base_info_unref(info);
	}
}

PHP_MINIT_FUNCTION(gobject)
{
	g_type_init();

	GIR_G(repository) = NULL;
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(gobject)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(gobject)
{
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(gobject)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(gobject)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "GObject Introspection", "experimental");
	php_info_print_table_end();
}
