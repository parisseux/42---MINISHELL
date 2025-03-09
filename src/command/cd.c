#include "../inc/minishell.h"

//deja modification de printf en write 
// remplacmeent de getenv car faut utilsier notre copy de env
//j'ai pas fait tous les tests mais semble marcher correctement 
// environ mais je pense qu'il faut rajouter un check pour verifier 
//que line est bien largument de cd et pas une pipe ou redireectoin 
// car c'est manquant? pt mettre le token en arg et char*
void	cd_command(char *line, t_shell *shell)
{
	int		i;
	char	*home;

	while (*line == ' ' || *line == '\t')
		line++;
	if (!*line)
	{
		home = get_env_value(shell->var_env, "HOME");
		if (!home)
		{
			write(STDOUT_FILENO, "cd: HOME not set\n", 17);
			return ;
		}
		i = chdir(home);
	}
	else
		chdir(line);
	if (i == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, line, ft_strlen(line));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
}
