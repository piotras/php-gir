
#include "php_gir.h"

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

}

PHP_MINIT_FUNCTION(gobject)
{
	g_type_init();
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
