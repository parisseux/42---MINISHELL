/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:01:33 by parissachat       #+#    #+#             */
/*   Updated: 2025/02/25 12:21:32 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cd_command(char *line)
{
	int	i;

	i = 0;
	while (*line == ' ')
		line++;
	if (!*line)
	{
		i = chdir(getenv("HOME"));
		if (i == -1)
			printf("cd: HOME not set\n");
		return ;
	}
	i = chdir((const char *)line);
	if (i == -1)
		printf("cd: %s: No such file or directory\n", line);
}
