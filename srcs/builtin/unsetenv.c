#include "shell21.h"
#include "builtin.h"

void	error_unset(char *find)
{
	char	*error;

	error = ft_strjoin("unset: ", find);
	error_handler(VARIABLE_ERROR | (ERR_RDONLY << 9), error);
	free(error);
}

int		btin_unsetenv(t_exec *pos)
{
	int		i;
	int		tmp;
	int		j;
	char	*find;

	i = 0;
	while (++i < pos->ar_c)
	{
		if ((tmp = ft_strchri(pos->ar_v[i], '=')) >= 0)
			find = ft_strndup(pos->ar_v[i], tmp);
		else
			find = ft_strdup(pos->ar_v[i]);
		if ((j = find_in_variable(&tmp, find)) < 0)
		{
			free(find);
			continue ;
		}
		if (g_envi[j][0] && (g_envi[j][0] & READONLY))
			error_unset(find);
        else
			ft_arrshift(g_envi + j + 1, g_var_size - j, -1);
		free(find);
	}
	return (0);
}
