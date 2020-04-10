#include "shell21.h"
#include "parser.h"

static const char	g_letters[] =
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

static int  ft_init_tmp(int *len, int *fd, int *buf, char *tmpl)
{
    *len = ft_strlen(tmpl);
	*fd = -1;
	*buf = 0;
	if (*len < 6 || ft_strcmp(&tmpl[*len - 6], "XXXXXX"))
		return (-1);
    return (0);
}

/*
** Generate a temporary file name based on TMPL.  TMPL must match the
** rules for mk[s]temp (i.e. end in "XXXXXX").  The name constructed
** does not exist at the time of the call to mkstemp.  TMPL is
** overwritten with the result. Implementation of mkstemp by POSIX,
** but it removes tmp file after usage like tmpfile()
*/

int		    ft_tmpfile(char *tmpl)
{
	int		len;
	char	*tmp;
	char	*xxx;
	int		fd;
	int		buf;

	if (ft_init_tmp(&len, &fd, &buf, tmpl) == -1)
        return (-1);
	(tmp = ft_strdup(tmpl)) != NULL ? xxx = &tmp[len - 6] : 0;
	while (fd < 0) //make timeout
	{
		len = -1;
		fd = open("/dev/random", O_RDONLY);
		while (++len < 6)
		{
			read(fd, &buf, 1);
			xxx[len] = g_letters[(buf + 300) % 62];
		}
		close(fd);
		fd = open(tmp, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC, 0666);
	}
	unlink(tmp);
	free(tmp); //Question??
	return (fd);
}
