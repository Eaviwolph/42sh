/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42shTeam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:35:21 by 42shTeam          #+#    #+#             */
/*   Updated: 2017/05/03 15:35:21 by 42shTeam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_H
# define VARIABLE_H

# include <stdbool.h>

typedef struct			s_variable
{
	struct s_variable	*next;
	char				*name;
	char				*value;
	bool				exported;
	bool				overwrite;
	bool				is_variable;
	bool				is_function;
}						t_variable;

char					*get_variable(char *var);
void					set_variable(char const *var, char const *val,
							bool overwrite);
void					display_variables(bool only_exported);
char					**get_variables_for_execution(t_variable *assignments);
void					set_assignments(t_variable *assignments, bool export);

t_variable				*create_variable(char const *name, char const *value,
											bool exported, bool overwrite);
void					delete_variable(t_variable **var);
void					delete_all_variables(t_variable **var);
t_variable				*copy_variable(t_variable *e);

void					print_variable(t_variable *v);
bool					variable_exist(t_variable *v, char *name);
bool					variable_is_overwritable(t_variable *v, char *name);
void					free_variable(t_variable *list);
int						pop_variable_by_name(t_variable **list, char *name);
bool					set_variable_for_export(t_variable *v, char *name);
bool					is_a_variable(t_variable *v, char *name);
bool					is_a_function(t_variable *v, char *name);

/*
**			set_default_variables.c
*/

void					set_underscore(char **words);
void					set_default_variables(void);
void					add_path_to_env(char *path, char **env);

#endif
