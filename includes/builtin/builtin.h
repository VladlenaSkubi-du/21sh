
#ifndef BUILTIN_H
# define BUILTIN_H

# include "cd.h"

# define SUBOPTION_STARTS			16

typedef struct  s_ec
{
	int         e;
	int         n;
	int         up_e;
}               t_ec;

char			**g_builtins;

/*
** File exit.c
*/

int				btin_exit(t_exec *exec);
int				btin_exit_arguments(char **ar_v);

/*
** Folder cd, file cd.c
*/

int				btin_cd(t_exec *exec);

/*
** File builtin_processing.c
*/

void            init_builtins(void);
int				builtins_call_void(int call_num);
int				builtins_call(int call_num, t_exec *exec);
int				usage_btin(char *str);
int				btin_return_exit_status(void);

/*
** File setenv.c
*/

int				btin_setenv(t_exec *exec);
int				setenv_error(char **tmp, int i);

/*
** File unsetenv.c
*/

int				btin_unsetenv(t_exec *exec);

/*
** File history.c
*/

int				btin_history(void);

/*
** File echo.c
*/

int             btin_echo(t_exec *exec);

/*
** File pwd.c
*/

int             btin_pwd(t_exec *exec);

/*
** File env.c
*/

int			    btin_env(void);
 
#endif
