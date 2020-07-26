#ifndef CD_H
# define CD_H

typedef struct		s_cd
{
	int				p;
	int				l;
}					t_cd;

/*
** File cd.c
*/

int         ft_error(char *name, int en);
char        *ft_join(char *path, char *src_path);

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

char        *ft_new_path(char *path, char *src_path);

/*
**  File cd_static.c
*/

char        *get_oldpwd_value(void);
char        *get_pwd_value(void);
int         change_oldpwd_value(char *str);
int         change_pwd_value(char *str);
int         cd_free_static(void);

#endif
