#include <shell21.h>
#include <builtin.h>

void	ft_del_prev(char **arr, int i)
{
	while (i > 0)
	{
		if (ft_strcmp(arr[i], ".") && ft_strcmp(arr[i], ".."))
		{
			free(arr[i]);
			arr[i] = ft_strdup(".");
			break ;
		}
		i--;
	}
}

void	ft_del_dots(char **arr)
{
    int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], "..") == 0)
			ft_del_prev(arr, i);
		i++;
	}
}

char	*ft_new_from_arr(char **arr)
{
    int		i;
    char	*tmp;

	i = 0;
	tmp = ft_memalloc(1);
	ft_del_dots(arr);
	while (arr[i])
	{
		if (ft_strcmp(arr[i], ".") && ft_strcmp(arr[i], ".."))
		{
			tmp = ft_strrejoin(tmp, "/");
			tmp = ft_strrejoin(tmp, arr[i]);
		}
		i++;
	}
	return (tmp);
}

char	*ft_join(char *path, char **env)
{
	int	i;
	int	j;
	char	*tmp;

	i = find_in_variables(env, &j, "PWD");
	tmp = ft_strjoin(env[i] + j, "/");
	tmp = ft_strrejoin(tmp, path);
	return (tmp);
}

char	*ft_new_path(char *path, char **env)
{
	char	*new_path;
	char	*tmp;
	char	**arr;

	tmp = ft_join(path, env);
	arr = ft_strsplit(tmp, '/');
	free(tmp);
	new_path = ft_new_from_arr(arr);
	//printf("RES = %s\n", new_path);
	ft_arrdel(arr);
	return (new_path);
}
