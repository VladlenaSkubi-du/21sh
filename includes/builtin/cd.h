#ifndef CD_H
# define CD_H

typedef struct		s_cd
{
	size_t			p;
	size_t			l;
    char            *curpath;
}					t_cd;

/*
** File cd.c
*/

int         ft_error(char *name, int en);
void        ft_change_curpath(char *path, t_cd *flags);

/*
** File cd_flags.c
*/

int         ft_cd_flags(char **argv, t_cd *flags);

/*
** File cd_valid.c
*/

int         ft_valid_cd(char **argv, int i);

/*
** File cd_parser.c
*/

int         ft_cd_pars(char *path, char **env, t_cd *flags);

/*
** File cd_change_path.c
*/

int         ft_change_path(char *path, char **env, t_cd *flags);

/*
** File cd_new_path.c
*/

char        *ft_new_path(char *path, char **env);
#endif
