#include <CUnit/CUnit.h>
#include "ftsh.h"
#include "errors.h"

void	init_sets_error_ptr(void)
{
	char	*argv[] = {
		"42sh",
		NULL
	};
	init(1, argv);
	CU_ASSERT_EQUAL(get_error(), NO_ERROR);
}
