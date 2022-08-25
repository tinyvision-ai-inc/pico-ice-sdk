#include "pico.h"

/*
 * Function called by "assert" when it fails.
 */
void
__assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
	(void)file;
	(void)line;
	(void)func;
	(void)failedexpr;
	for (volatile int i = 0;; i++);
}
