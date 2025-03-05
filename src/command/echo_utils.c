#include "../inc/minishell.h"

int	echo_check_n_flag(char **line)
{
	int	n_flag;

	n_flag = 0;
	while (**line == '-' && *((*line) + 1) == 'n')
	{
		(*line) += 2;
		n_flag = 1;
	}
	return (n_flag);
}
