#include "shell21.h"
#include "builtin.h"

static int	sorting_vars(t_pathtree **root, int *len)
{
	int		i;
	int		li;
	int		sy;

	i = -1;
	while (g_env[++i])
		insert_to_path_tree(g_env[i], root, len);
	i = -1;
	while (g_shvar[++i])
		insert_to_path_tree(g_shvar[i], root, len);
	i = -1;
	while (g_lovar[++i])
		insert_to_path_tree(g_lovar[i], root, len);
	li = find_in_variables(g_rdovar, &sy, "42SH=");
	i = li - 1;
	while (g_rdovar[++i])
		insert_to_path_tree(g_rdovar[i], root, len);
	return (0);	
}

int			btin_set(void)
{
	t_pathtree	*root;
	char		**list;
	int			len;
	int 		max;

	root = NULL;
	list = NULL;
	len = 0;
	sorting_vars(&root, &len);
	list = form_result_array(&root, len, &max);
	free_path_tree(&root);
	max = -1;
	while(list[++max])
		ft_putendl(list[max]);
	ft_arrdel(list);
	return (0);	
}