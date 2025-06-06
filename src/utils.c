/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:34 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/05 14:58:34 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmd_err(char *msg, char *cmd, int exit, t_shell *shell)
{
	write (STDERR_FILENO, "minishell: ", 11);
	write (STDERR_FILENO, cmd, ft_strlen(cmd));
	write (STDERR_FILENO, msg, ft_strlen(msg));
	write (STDERR_FILENO, "\n", 1);
	shell->exit = exit;
}

void	ft_free_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_varcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n && (s2[i] || s1[i]))
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
			i++;
		else
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	}
	if (s1[i] != '=')
		return (1);
	return (0);
}

void	clean_exit(int exit_status, t_token *lst_token,
	char **env, char **shell)
{
	clear_history();
	if (env)
		ft_free_char_tab(env);
	if (shell)
		ft_free_char_tab(shell);
	if (lst_token)
		free_token_list(lst_token);
	cleanup_readline();
	if (g_last_signal != 0)
		exit(g_last_signal);
	exit(exit_status);
}

void	change_fd(int fd_out, int fd_in)
{
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close (fd_in);
	}
}
