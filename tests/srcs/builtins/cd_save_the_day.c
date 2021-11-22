#include "test_utils.h"
#include <limits.h>

void	save_the_day(char **curpath_addr, char const *directory, char const *pwd);

void	cd_save_the_day()
{
	char	curpath[PATH_MAX + 1]; //longer than PATH_MAX including nul
	char	directory[PATH_MAX]; //not longer than PATH_MAX including nul
	char	pwd[] = "/some/pwd";
	size_t	offset = ft_strlen(pwd) + 1;
	char	*new_curpath;

	ft_memcpy(curpath, pwd, offset - 1);
	curpath[offset - 1] = '/';
	ft_memset(curpath + offset, 'a', PATH_MAX - offset);
	curpath[PATH_MAX] = '\0';
	ft_memset(directory, 'b', PATH_MAX - 1);
	directory[PATH_MAX - 1] = '\0';
	new_curpath = ft_strdup(curpath);
	save_the_day(&new_curpath, directory, pwd);
	CU_ASSERT_STRING_EQUAL(new_curpath, curpath + offset);
}
