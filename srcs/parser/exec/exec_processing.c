/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:52:41 by sschmele          #+#    #+#             */
/*   Updated: 2020/08/01 18:12:46 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "parser.h"

int		save_streams(int mode)
{
	static int		save[3];

	if (!mode)
	{
		save[0] = dup(STDIN_FILENO);
		save[1] = dup(STDOUT_FILENO);
		save[2] = dup(STDERR_FILENO);
	}
	else
	{
		dup2(save[0], STDIN_FILENO);
		dup2(save[1], STDOUT_FILENO);
		dup2(save[2], STDERR_FILENO);
	}
	return (0);
}

int		cmd_fork_and_exec(t_exec *exec, char *path, pid_t *child_pid)
{
	char			**local_envir;
	
	local_envir = form_envir_for_cmd();
	*child_pid = fork();
	if (!*child_pid)
	{
		if (execve(path, exec->argv, local_envir) == -1)
		{
			ft_arrdel(local_envir);
			exit(-1);
		}
	}
	else if (*child_pid < 0)
	{
		ft_arrdel(local_envir);
		return (-1);
	}
	pipe_asynchronous_work_exec(exec, child_pid);
	ft_arrdel(local_envir);
	return (0);
}

int		pipe_asynchronous_work_exec(t_exec *exec, pid_t *child_pid)
{
	static t_stack	*stack;
	int				status;
	pid_t			pid_answer;

	status = 0;
	if (!(exec->flag & PIPED_OUT))
	{
		pid_answer = waitpid(*child_pid, &status, 0);
		if (pid_answer != *child_pid)
			status = -1;
	}
	else
	{
		if (!stack)
			stack = ft_init_stack();
		ft_push_stack(&stack, *child_pid);
	}
	kill_pipe_processes(exec, &stack, &status);
	*child_pid = status;
	return (0);
}

int		kill_pipe_processes(t_exec *exec, t_stack **stack, int *status)
{
	if (!(exec->flag & PIPED_OUT) && (exec->flag & PIPED_IN))
	{
		if (*stack)
		{
			while ((*stack)->data != 0)
			{
				kill((*stack)->data, SIGKILL);
				waitpid((*stack)->data, status, 0);
				ft_pop_stack(stack);
			}
			ft_clear_stack(stack);
		}
	}
	return (0);
}
