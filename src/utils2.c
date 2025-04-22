#include "../inc/minishell.h"

void	free_token_list(t_token *lst_token)
{
	t_token	*tmp;

	while (lst_token)
	{
		tmp = lst_token;
		lst_token = lst_token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	msg_error(char *msg, t_token *lst_token)
{
	printf("Error: %s\n", msg);
	free_token_list(lst_token);
}

char	*get_env_value(char **env, char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], key, len) == 0 && env[i][len] == '='))
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

void    cleanup_readline(void)
{
    rl_free_line_state();   /* libère les buffers de la ligne courante      */
    rl_clear_history();     /* vide la liste d’historique                   */
    rl_deprep_terminal();   /* libère les structures propres au terminal    */
}