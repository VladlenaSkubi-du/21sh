#include "shell21.h"
#include "parser.h"

int		    ft_tmpfile(void)
{
	char	*path;
	char	*tmp;
	int		fd;
	int		time_out;

	path = getcwd(NULL, MAXDIR);
	path = ft_strrejoin(path, "/");
	path = ft_strrejoin(path, "tmp_file");
	time_out = 0;
	fd = -1;
	while (fd < 0)
	{
		time_out++;
		fd = open(path, O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC, 0666);
		if (fd < 0 && time_out > 10)
			return (fd);
		else if (fd < 0)
		{
			tmp = ft_itoa(time_out);
			path = ft_strrejoin(path, tmp);
			free(tmp);
		}
	}
	unlink(path);
	free(path);
	return (fd);
}
