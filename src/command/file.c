#include "../inc/minishell.h"

//je suis pas sur qu'on ait besoins de ca si on utiliser dup et dup2() c'est plus simple car on utilsier 
//juste fd = open() qui est un int qu'on envoit --> pas de strucutre 
// mais garder ay cas ou pour plus tard 
char	*filename(t_token *lst_token)
{
	t_token	*tmp;

	tmp = lst_token;
	while (tmp)
	{	
		if (tmp->type == APPEND || tmp->type == REDIR_OUT)
			return (tmp->next->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_file	*open_file(t_token *lst_token, int type)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->file_name = filename(lst_token);
	file->type = type;
	if (file->file_name == NULL)
	{
		free(file);
		return (NULL);
	}
	if (type == APPEND)
		file->file = fopen(file->file_name, "a");
	else
		file->file = fopen(file->file_name, "w");
	if (file->file == NULL)
	{
		printf("fopen failed\n");
		free(file);
		return (NULL);
	}
	file->fd = fileno(file->file);
	if (file->fd == -1)
	{
		printf("fileno failed\n");
		fclose(file->file);
		free(file);
		return (NULL);
	}
	return (file);
}
