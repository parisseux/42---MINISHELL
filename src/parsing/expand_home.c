/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:25:13 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:20:08 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	space(t_token *lst_token)
{
	int	type;

	if (lst_token->type == END)
		return (0);
	type = lst_token->next->type;
	if (type == END || type == PIPE || type == APPEND || type == REDIR_OUT
		|| type == HEREDOC || type == BIN || type == REDIR_IN)
		return (1);
	if (lst_token->space == 1)
		return (0);
	return (0);
}

char	*addh(char *home, char *str)
{
	char	*new;
	int		size;
	int		j;
	int		i;

	i = 0;
	size = ft_strlen(home) + ft_strlen(str);
	new = malloc(sizeof(char) * size + 1);
	if (!new)
		return (NULL);
	while (str[i] != '~')
		i++;
	ft_strlcpy(new, str, i + 1);
	ft_strlcat(new, home, size);
	j = i + ft_strlen(home);
	i++;
	while (str[i] != '\0')
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

void	home_not_set(t_shell *shell)
{
	write(STDOUT_FILENO, "cd: HOME not set\n", 17);
	shell->exit = 1;
}

void	replace_home(t_shell *sh, t_token *l)
{
	char	*t;
	int		i;

	while (l->type != END)
	{
		if (before(l) && space(l->next))
		{
			t = ft_strdup(l->next->value);
			i = 0;
			while (l->next->value[i] != '\0')
			{
				if (l->next->value[i] == '~' && ishome(l->next->value, i))
				{
					free(l->next->value);
					l->next->value = addh(env_value(sh, sh->venv, "HOME"), t);
					t = ft_strdup(l->next->value);
					i = 0;
				}
				else
					i++;
			}
			free(t);
		}
		l = l->next;
	}
}
