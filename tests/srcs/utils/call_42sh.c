#include <libft.h>

int	call_42sh(char const *args)
{
	char const	*ftsh_path = "../42sh ";
	char		*command;
	int			result;

	command = ft_strjoin(ftsh_path, args);
	result = system(command);
	free(command);
	return (result);
}
