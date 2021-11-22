/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:52:57 by asenat            #+#    #+#             */
/*   Updated: 2017/06/29 15:12:37 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_def.h"
#include <libft.h>
#include <signal.h>
#include "shell_env.h"
#include "abstract_list.h"
#include "init/init.h"
#include "utils.h"

static void		export_classic(t_variable **env, char **argv)
{
	char	**tab;
	size_t	i;

	i = 0;
	while (argv[++i])
	{
		if (!is_an_argument(argv, i))
			continue ;
		if (ft_strchr(argv[i], '='))
		{
			tab = ft_strsplit(argv[i], '=');
			if (ft_tablen(tab) >= 1)
			{
				setenv_as(env, tab[0], tab[1], true);
			}
			ft_freetabchar(tab);
		}
		else
		{
			if (variable_exist(*env, argv[i]))
				set_variable_for_export(*env, argv[i]);
			else
				setenv_as(env, argv[i], NULL, true);
		}
	}
}

/*
** When -p is specified, export shall write to
** the standard output the names and
** values of all exported variables.
*/

static void		export_option_p(t_variable *env)
{
	while (env)
	{
		if (env->exported == true)
		{
			if (ft_strlen(env->value))
				ft_printf("export %s=%s\n", env->name, env->value);
			else
				ft_printf("export %s\n", env->name);
		}
		env = env->next;
	}
}

/*
** The shell shall give the export attribute to the variables
** corresponding to the specified names,
** which shall cause them to be in the environment of
** subsequently executed commands.
**
** If the name of a variable is followed by =word,
** then the value of that variable shall be set to word.
*/

int				builtin_export(int argc, char **argv)
{
	t_variable	**env;
	char		*opt;
	bool		allowed;

	env = &get_shell_env()->variables;
	if ((opt = get_options_core(argc, argv)) == (char *)-1)
		return (STATUS_FAILURE);
	allowed = check_only_allowed_option(opt, "p");
	if (ft_strchr(opt, 'p'))
		export_option_p(*env);
	else if (argc == 1 && allowed)
		display_variables(true);
	else if (argc >= 2 && allowed)
		export_classic(env, argv);
	else
	{
		ft_dprintf(STDERR_FILENO, "Usage: export [-p] name[=word]...\n");
		ft_strdel(&opt);
		return (STATUS_FAILURE);
	}
	ft_strdel(&opt);
	return (STATUS_SUCCESS);
}
