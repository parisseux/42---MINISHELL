#include "../inc/minishell.h"

//Cette fonction permet d'aller chercher dans
//la copie de notre environnement (char **)
//le contenue d'une variable 
//exemple si key = PATH alors la fonction retourne /usr/bin....
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
