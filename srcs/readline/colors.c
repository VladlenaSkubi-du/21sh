#include "shell21.h"
#include "readline.h"

#define COLOR_NUM 6

char			*colors_process(int sequence_num)
{
	char	    *seq_action[COLOR_NUM];

	seq_action[0] = RED;
	seq_action[1] = ORANGE;
	seq_action[2] = YELLOW;
	seq_action[3] = GREEN;
	seq_action[4] = BLUE;
	seq_action[5] = PURPLE;
	return (seq_action[sequence_num]);
}
