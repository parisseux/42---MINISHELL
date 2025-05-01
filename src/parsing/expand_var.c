/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:25:19 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:20:08 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*dolar_sign(char *line, int index)
{
	char		*name;
	size_t		i;

	i = 0;
	name = NULL;
	if (line[index] == '?' || line[index] == '$'
		|| line[index] == '0' || line[index] == '\0')
		return (NULL);
	i = alphanum_len(line + index);
	if (i > 0)
		name = ft_substr(line, index, i);
	else
		return (NULL);
	return (name);
}

void	dol_spec_cases(char **value, int index,
	char *line, t_shell *shell)
{
	char	*name;
	char	*tmp;
	char	*cpy;

	name = NULL;
	tmp = NULL;
	if (line[index] != '?' && line[index] != '$' && line[index] != '0')
		return ;
	cpy = ft_strdup(*value);
	if (!cpy)
		return ;
	if (line[index] == '?')
		name = ft_itoa(shell->exit);
	else if (line[index] == '$')
		name = find_pid();
	else if (line[index] == '0')
		name = ft_strdup("minishell");
	if (name)
	{
		free(*value);
		tmp = add_special_case(name, cpy);
		*value = tmp;
		free(cpy);
		free(name);
	}
}

void	find_var(t_shell *shell, char *name, char **value, int len)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = *value;
	if (found_in_tab(shell->venv, name, len) > 0)
	{
		i = found_in_tab(shell->venv, name, len);
		tmp2 = add(shell->venv[i], tmp, len + 1);
		free(*value);
		*value = tmp2;
		return ;
	}
	if (found_in_tab(shell->shell_env, name, len) > 0)
	{
		i = found_in_tab(shell->shell_env, name, len);
		tmp2 = add(shell->shell_env[i], tmp, len + 1);
		free(*value);
		*value = tmp2;
		return ;
	}
	tmp2 = rm_var(tmp, len + 1);
	free(*value);
	*value = tmp2;
}

void	which(char **value, t_shell *shell)
{
	char	*name;
	char	*dup;
	int		i;

	init(&i, &name, &dup, *value);
	while (dup[i] != '\0')
	{
		if (dup[i] == '$' && dup[i + 1] != ' ' && dup[i + 1] != '\0')
		{
			name = dolar_sign(dup, i + 1);
			if (name)
			{
				find_var(shell, name, value, ft_strlen(name));
				free(name);
				if (!*value || !ft_strncmp(*value, dup, ft_strlen(*value)))
					return ;
			}
			else
				dol_spec_cases(value, i + 1, dup, shell);
			init(&i, &name, &dup, *value);
		}
		if (dup[i] != '\0')
			i++;
	}
}

void	look_for_dolls(t_token *lst, t_shell *shell)
{
	while (lst != NULL && lst->type != END)
	{
		if (spe_case(lst->value, lst->next->type, lst->next->space))
		{
			free(lst->value);
			lst->value = ft_strdup("");
			lst = lst->next;
		}
		else if (isvalid(lst->type, lst->value) > 0)
			handle_valid_token(lst, shell);
		else
			lst = lst->next;
	}
}
