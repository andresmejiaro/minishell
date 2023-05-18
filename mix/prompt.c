/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/05/18 18:48:49 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt_chooser(void)
{
	static int	mode;

	if (g_state.last_return == 0)
	{
		mode++;
		if (mode % 5 == 1)
			return ("\033[0;35m(>^.^)> \033[0;37m");
		if (mode % 5 == 2)
			return ("\033[0;35m<(^.^<) \033[0;37m");
		if (mode % 5 == 3)
			return ("\033[0;35m<(^.^)> \033[0;37m");
		if (mode % 5 == 4)
			return ("\033[0;35m^(^.^)^ \033[0;37m");
		if (mode % 5 == 0)
			return ("\033[0;35mv(^.^)v \033[0;37m");
	}
	return ("\033[0;31m(>x.x)> \033[0;37m");
}

void	prompt(void)
{
	char	*command;
	t_token	*tokens;
	t_token	*last;
	char	*prompt;

	command = (char *)1;
	while (command != NULL)
	{
		if (g_state.signal == 1)
		{
			g_state.signal = 0;
			continue;
		}
		command = readline(prompt_chooser());
		if (command == NULL)
			break ;
		tokens = parsing(command);
		if (tokens)
		{
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
		free(command);
	}
}

void	prompt_debug(void)
{
	char	*command;
	t_token	*tokens;
	t_token	*last;
	char	*prompt;
	int		w;

	w = 0;
	command = (char *)1;
	while (command != NULL)
	{
		command = ft_strdup("/bin/echo \"\"$?\"\"");
		if (command == NULL)
			break ;
		tokens = parsing(command);
		if (tokens)
		{
			ft_print_tkns(tokens);
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
		free(command);
		command = NULL;
		w++;
	}
}

void	prompt_linux(void)
{
	char	*command;
	t_token	*tokens;
	t_token	*last;
	char	*prompt;

    //signal(SIGINT, sig_hnd);
    //signal(SIGQUIT, sig_hnd);
	command = (char *)1;
	while (command != NULL)
	{
		command = get_next_line(STDIN_FILENO);
		if (command == NULL)
			break ;
		if (ft_strlen(command) == 0)
			continue ;
		if (ft_strchr(command, '\n') > 0)
			ft_delete_char(ft_strchr(command, '\n'));
		if (!command)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			exit (g_state.last_return);
		}
		if (command == NULL)
			break ;
		tokens = parsing(command);
		if (tokens)
		{
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
		free(command);
	}
}
