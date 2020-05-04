
#ifndef BUILTIN42_H
# define BUILTIN42_H

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

/*
** File set.c
*/

int				btin_set(void);
int				btin_return_exit_status(void);

/*
** File unset.c
*/

int				btin_unset(t_exec *exec);

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
