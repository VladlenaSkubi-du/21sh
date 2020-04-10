#include "shell21.h"
#include "readline.h"
#define ESC_NUM 12

/*
** Function pointer array, should return function call
*/

int				sequence_process(int sequence_num)
{
	int		(*seq_action[ESC_NUM])(void);

	seq_action[0] = key_right_proc;
	seq_action[1] = key_up_proc;
	seq_action[2] = key_left_proc;
	seq_action[3] = key_down_proc;
	seq_action[4] = esc_r;
	seq_action[5] = delete_process;
	seq_action[6] = word_left_proc;
	seq_action[7] = word_right_proc;
	seq_action[8] = esc_d;
	seq_action[9] = esc_t;
	seq_action[10] = jump_up;
	seq_action[11] = jump_down;
	return ((*seq_action[sequence_num])());
}

/*
** Should beep and do nothing - bell
*/

int				incorrect_sequence(void)
{
	putcap("bl");
	return (1);
}

int				escape_check(char **seq_base)
{
	size_t	i;
	char	buff[ESC_NUM];
	int		stage;

	i = 0;
	ft_bzero(buff, ESC_NUM);
	while (read(1, buff + i, 1))
	{
		stage = 0;
		while (stage < ESC_NUM)
		{
			if (!ft_strncmp(buff, seq_base[stage], i + 1))
				break ;
			stage++;
		}
		if (stage == ESC_NUM)
			return (incorrect_sequence());
		if (!ft_strncmp(buff, seq_base[stage], ft_strlen(seq_base[stage]) + 1))
			return (sequence_process(stage));
		i++;
	}
	return (0);
}

int				escape_init(void)
{
	char	*seq_base[ESC_NUM];

	seq_base[0] = "[C";
	seq_base[1] = "[A";
	seq_base[2] = "[D";
	seq_base[3] = "[B";
	seq_base[4] = "r";
	seq_base[5] = "[3~";
	seq_base[6] = "b";
	seq_base[7] = "f";
	seq_base[8] = "d";
	seq_base[9] = "t";
	seq_base[10] = "[1;5A";
	seq_base[11] = "[1;5B";
	return (escape_check(seq_base));
}
