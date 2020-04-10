
#include <shell21.h>
#include <builtin.h>

int		pwd_error(char c, int en)
{
	char	*tmp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strdup("pwd: -");
	if (en == 1)
	{
		tmp = ft_strrejoin(tmp, str);
		tmp = ft_strrejoin(tmp, " :invalid parameter\npwd: usage: pwd [-LP]");
	}
	error_handler(VARIABLE_ERROR | (ERR_CD << 9), tmp);
	free(tmp);
	return (1);
}

int		valid(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 1;
		if (argv[i][0] == '-')
			while (argv[i][j])
			{
				if (argv[i][j] != 'L' && argv[i][j] != 'P')
					return (pwd_error(argv[i][j], 1));
				j++;
			}
		i++;
	}
	return (0);
}

int     btin_pwd(t_ltree *pos)
{
	t_cd	*flags;
	char	dir[MAXDIR];

	if (valid(pos->ar_v))
		return (1);
	flags = ft_xmalloc(sizeof(t_cd *));
	ft_cd_flags(pos->ar_v, flags); //there was return i comp - where is used?
	if (flags->l)
		ft_putstr(g_rdovar[5] + 4);
	else
	{
		getcwd(dir, MAXDIR);
		ft_putstr(dir);
	}
    ft_putchar('\n');
	free(flags->curpath);
	free(flags);
    return (0);
}
