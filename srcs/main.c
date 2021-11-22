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

#include <stdlib.h>

#include "errors.h"
#include "execution/execute_syntax_tree.h"
#include "ftsh.h"
#include "history/builtin/history.h"
#include "history/substitution/history_substitutions.h"
#include "init/init.h"
#include "parse_input/print_syntax_tree.h"
#include "sig_handler.h"
#include "utils.h"

static void main_loop(void)
{
    t_shell_env *shell_env;

    shell_env = get_shell_env();
    set_error(NO_ERROR);
    read_input();
    break_input();
    if (get_error() != NO_ERROR)
        return;
    if (shell_env->input_string)
        add_to_history_list(&shell_env->history.list,
                            create_history_entry(shell_env->input_string));
    parse_input();
    if (get_error() == NO_ERROR)
    {
        execute_command_list(get_shell_env()->syntax_tree);
        ft_strdel(&get_shell_env()->input_string);
    }
    delete_command_list(&get_shell_env()->syntax_tree);
}

int convert_error_to_status(t_error_id id)
{
    if (id == UNEXPECTED_SEMI)
        return (2);
    return (1);
}

int main(int ac, char **av)
{
    signal(SIGINT, sig_int);
    signal(SIGTSTP, SIG_IGN);
    init(ac, av);
    while (get_shell_env()->should_run)
        main_loop();
    if (get_error() == CHILD_FAILURE || get_last_exit_status())
        return (get_last_exit_status());
    else if (get_error() == NO_ERROR)
        return (EXIT_SUCCESS);
    else
    {
        print_name_and_error(get_error());
        return (convert_error_to_status(get_error()));
    }
}
