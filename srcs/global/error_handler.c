#include "shell21.h"

/*
** Enum structure for exxors is defined in exit_status.h
** status that comes is always a value from enum structure
** with binary shift to define the error type
**
** For example: error_handler(OPTIONS_REQUIRED | (ERR_EBASH_C << 9), "21sh");
** where OPTIONS_REQUIRED is equal 2, if we after check exit status
** with echo $?, there will be 2
** But there are many errors that exit with 2, so we define error type
** by making shift << 9 and activating bits according to the mask defined in
** exit_status.h
** We decided that status always shifts by 9
**
** @status is an int with activated "exit" and error type bits
** @str is a name that is put after "21sh: [NAME]: [TEXT]"
*/

int				error_handler(int status, char *str)
{
	ft_putstr_fd("21sh: ", STDERR_FILENO);
	if ((status & 0x1FF) == VARIABLE_ERROR)
		variable_errors(status, str);
	else if ((status & 0x1FF) == OPTIONS_REQUIRED)
		options_errors(status, str);
	else if ((status & 0x1FF) == TERMINAL_EXISTS)
		ft_putendl_fd("terminal does not exist", STDERR_FILENO);
	else if ((status & 0x1FF) == TERMINAL_TO_NON)
		ft_putendl_fd("terminal can't be changed", STDERR_FILENO);
	else if ((status & 0x1FF) == TERMINAL_TO_CAN)
		ft_putendl_fd("terminal can't be changed, reset the terminal",
			STDERR_FILENO); //TODO check
	else if ((status & 0xFF) == TMPFILE)
		ft_putendl_fd("can't open a temporal file", STDERR_FILENO); //TODO check
	else if ((status & 0x1FF) == SUCCESS)
		ft_putstr_fd(str, STDERR_FILENO);
	else
		error_handler_continuation(status, str);
	return (exit_status_variable(status & 0x7F));
}

int				error_handler_continuation(int status, char *str)
{
	if ((status & 0x1FF) == COMMAND_NON_EXECUTABLE ||
		(status >> 9 & ERR_NO_ACC))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else if ((status & 0x1FF) == COMMAND_NOT_FOUND &&
		(status >> 9 & ERR_COMMAND))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (((status & 0x1FF) == COMMAND_NOT_FOUND ||
		(status & 0x1FF) == SYNTAX_ERROR) &&
		status >> 9 & ERR_NO_FILE)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else if ((status & 0x1FF) == SYNTAX_ERROR)
		syntax_errors(status, str);
	return (0);
}

/*
** Variable errors are errors that exit with 1
*/

int				variable_errors(int status, char *str)
{
	if ((status >> 9 & ERR_SET) || (status >> 9 & ERR_CD))
	{
		ft_putendl_fd(str, STDERR_FILENO);
		return (0);
	}
	ft_putstr_fd(str, STDERR_FILENO);
	if (status >> 9 & ERR_RDONLY)
		ft_putendl_fd(": readonly variable", STDERR_FILENO);
	else if (status >> 9 & ERR_HISTORY_EXEC)
		ft_putendl_fd(": no command found", STDERR_FILENO);
	else if (status >> 9 & ERR_UNSET)
		ft_putendl_fd(": parameter null or not set", STDERR_FILENO);
	return (0);
}

/*
** Option errors are errors that exit with 2
*/

int				options_errors(int status, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (status >> 9 & ERR_BTIN_INVALID)
		ft_putendl_fd(": invalid option", STDERR_FILENO);
	else if (status >> 9 & ERR_BTIN_ARG)
		ft_putendl_fd(": option requires an argument", STDERR_FILENO);
	return (0);
}

/*
** Syntax errors are errors that exit with 258
*/

int				syntax_errors(int status, char *str)
{
	if (status >> 9 & ERR_SQUOTE)
	{
		ft_putstr_fd("unexpected EOF while looking for matching `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		ft_putstr_fd("21sh: ", STDERR_FILENO);
		ft_putstr_fd("syntax error: ", STDERR_FILENO);
		ft_putendl_fd("unexpected end of file", STDERR_FILENO);
	}
	if (status >> 9 & ERR_REDIR)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	if (status >> 9 & ERR_BAD_FD)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": Bad file descriptor", STDERR_FILENO);
	}
	if (status >> 9 & ERR_NUMERIC)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	return (0);
}

/*
** Errors possible in NON-INTERACTIVE MODE:
** bash --posix -c "."
bash: line 0: .: filename argument required
.: usage: . filename [arguments]
echo $?
2


** bash --posix -c "/"
bash: /: is a directory
bash-3.2$ echo $?
126


** bash --posix -c "!"
bash: !: event not found
bash-3.2$ echo $?
0


** bash --posix -c "hallo"
bash: hallo: command not found
bash-3.2$ echo $?
127


** bash --posix -c "\""
bash: -c: line 0: unexpected EOF while looking for matching `"'
bash: -c: line 1: syntax error: unexpected end of file
bash-3.2$ echo $?
2


** bash --posix -c "{"
bash: -c: line 1: syntax error: unexpected end of file
bash-3.2$ echo $?
2


** bash --posix -c "; ; "
bash: -c: line 0: syntax error near unexpected token `;'
bash: -c: line 0: `; ; '
bash-3.2$ echo $?
2
*/

/*bash-3.2$ bash --posix -c "fg"
bash: line 0: fg: no job control
bash-3.2$ bash --posix -c "bg"
bash: line 0: bg: no job control
*/

/*
** Errors possible in INTERACTIVE MODE:
**
*/
