#include "test_utils.h"

void	unclosed_quote()
{
	int status = call_42sh("-c \"'\"");
	CU_ASSERT(status != EXIT_SUCCESS);
}

void	unclosed_double_quote()
{
	int status = call_42sh("-c \"\\\"\"");
	CU_ASSERT(status != EXIT_SUCCESS);
}
