/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:03:00 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/07 14:36:44 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void child(char *del, int *pipfd)
{
    char *line;

    close(pipfd[0]);
    while (1)
    {
        ft_putstr_fd("heredoc> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (ft_strncmp(line, del, ft_strlen(del)) == 0 && ft_strlen(line) - 1 == ft_strlen(del))
        {
            free(line);
            close(pipfd[1]);
            get_next_line(-1);
            exit(g_exit_status);
        }
        write(pipfd[1], line, ft_strlen(line));
        free(line);
    }
}

void here_doc(char *del)
{
<<<<<<< HEAD
	int	pipfd[2];
	int	pid;

	if (pipe(pipfd) == -1)
		perror("Error: ");
	pid = fork();
	if (pid == -1)
		perror("Error: ");
	if (pid == 0)
		child(del, pipfd);
	else
	{
		close(pipfd[1]);
		dup2(pipfd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	is_builtin_command(char *command)
=======
    int pipfd[2];
    int pid;
    if (pipe(pipfd) == -1)
        perror("Error: ");
    pid = fork();
    if (pid == -1)
        perror("Error: ");
    if (pid == 0)
        child(del, pipfd);
    else
    {
        close(pipfd[1]);
        dup2(pipfd[0], STDIN_FILENO);
        waitpid(pid, NULL, 0);
    }
}

int is_builtin_command(char *command)
>>>>>>> 464fc4b7d25ca247f4503ad3331a029baceec3da
{
	if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "echo") || !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset"))
	{
		return (1);
	}
	return (0);
}

<<<<<<< HEAD
int	execute_builtins(t_cmd *cmd, t_shell *shell, t_env *env)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(env, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd(&cmd->args[0]));
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(&cmd->args[0]));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(env, shell, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export1(&shell, &cmd->args[0], env));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(&shell, env, cmd->args));
	return (0);
}

int	run_builtins(t_cmd *cmd, t_shell *shell, t_env *env, t_context *ctx)
=======
int execute_builtins(t_cmd *cmd, t_shell *shell, t_env *env)
{
    if (!ft_strcmp(cmd->args[0], "cd"))
        return ft_cd(env, cmd->args);
    else if (!ft_strcmp(cmd->args[0], "pwd"))
        return ft_pwd(&cmd->args[0]);
    else if (!ft_strcmp(cmd->args[0], "echo"))
        return ft_echo(&cmd->args[0]);
    else if (!ft_strcmp(cmd->args[0], "env"))
        return ft_env(env, shell, cmd->args);
    else if (!ft_strcmp(cmd->args[0], "export"))
        return ft_export1(&shell, &cmd->args[0], env);
    else if (!ft_strcmp(cmd->args[0], "unset"))
        return ft_unset(&shell, env, cmd->args);
    return 0;
}

int run_builtins(t_cmd *cmd, t_shell *shell, t_env *env, t_context *ctx)
>>>>>>> 464fc4b7d25ca247f4503ad3331a029baceec3da
{
	int	save_stdin;
	int	save_stdout;

<<<<<<< HEAD
	(void)ctx;
	save_stdin = -1;
	save_stdout = -1;
	if (is_builtin_command(cmd->args[0]))
	{
		save_stdin = dup(STDIN_FILENO);
		save_stdout = dup(STDOUT_FILENO);
		execute_builtins(cmd, shell, env);
		if (save_stdin != -1)
		{
			dup2(save_stdin, STDIN_FILENO);
			close(save_stdin);
		}
		if (save_stdout != -1)
		{
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdout);
		}
	}
	return (g_exit_status);
}
void	child_process(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
	if (!cmd->args[0])
	{
		if (cmd->infile)
		{
			redir_infile(cmd);
		}
		else if (cmd->outfile)
			redir_outfile(cmd);
		exit(g_exit_status);
	}
	if (cmd->heredoc == 1)
	{
		here_doc(cmd->save_del);
	}
	else if (cmd->infile)
	{
		if (redir_infile(cmd) < 0)
		{
			g_exit_status = 1;
			exit(g_exit_status);
		}
	}
	else if (ctx->prev_pipe != -1)
	{
		dup2(ctx->prev_pipe, STDIN_FILENO);
		close(ctx->prev_pipe);
	}
	if (cmd->outfile)
	{
		if (redir_outfile(cmd) < 0)
		{
			g_exit_status = 1;
			exit(g_exit_status);
		}
	}
	else if (cmd->next && !is_builtin_command(cmd->args[0]))
	{
		close(ctx->fdpipe[0]);
		dup2(ctx->fdpipe[1], STDOUT_FILENO);
		close(ctx->fdpipe[1]);
	}
	if (is_builtin_command(cmd->args[0]))
	{
		run_builtins(cmd, shell, env, ctx);
		if (cmd->next || cmd->outfile)
			exit(g_exit_status);
	}
	else
		exec(cmd->args, shell, env);
}

void	parent_process(t_cmd *cmd, t_context *ctx)
{
	if (ctx->prev_pipe != -1)
		close(ctx->prev_pipe);
	if (cmd->next)
		close(ctx->fdpipe[1]);
	ctx->last_pid = ctx->pids;
}

int	execute_commands(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
	ctx->prev_pipe = -1;
	ctx->pids = -1;
	while (cmd)
	{
		if (cmd->next)
			pipe(ctx->fdpipe);
		ctx->pids = fork();
		if (ctx->pids == 0)
			child_process(cmd, ctx, shell, env);
		else
			parent_process(cmd, ctx);
		if (cmd->next)
			ctx->prev_pipe = ctx->fdpipe[0];
		else
			ctx->prev_pipe = -1;
		cmd = cmd->next;
	}
	if (ctx->pids != -1)
		waitpid(ctx->last_pid, &g_exit_status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	return (g_exit_status);
}
=======
    pid = fork();
    if (pid == 0)
    {
        if (is_builtin_command(cmd->args[0]))
        {
            save_stdin = dup(STDIN_FILENO);
            save_stdout = dup(STDOUT_FILENO);
            if (cmd->next)
            {
                close(ctx->fdpipe[0]);
                dup2(ctx->fdpipe[1], STDOUT_FILENO);
                close(ctx->fdpipe[1]);
            }
            execute_builtins(cmd, shell, env);
            dup2(save_stdin, STDIN_FILENO);
            dup2(save_stdout, STDOUT_FILENO);
            close(save_stdin);
            close(save_stdout);
            if (cmd->next)
                exit(g_exit_status);
        }
    }
    else
    {
        wait(NULL);
        waitpid(pid, &g_exit_status, 0);
    }
    return (WEXITSTATUS(g_exit_status));
}

int child_process(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
    if (!cmd->args[0] || cmd->args[0][0] == '\0')
    {
        g_exit_status = 127;
        exit(g_exit_status);
    }
    if (!cmd->args[0])
    {
        if (cmd->infile)
        {
            redir_infile(cmd);
        }
        else if (cmd->outfile)
            redir_outfile(cmd);
        exit(g_exit_status);
    }
    if (cmd->heredoc == 1)
    {
        here_doc(cmd->save_del);
    }
    else if (cmd->infile)
    {
        if (redir_infile(cmd) < 0)
        {
            g_exit_status = 1;
            exit(g_exit_status);
        }
    }
    else if (ctx->prev_pipe != -1)
    {
        dup2(ctx->prev_pipe, STDIN_FILENO);
        close(ctx->prev_pipe);
    }
    if (cmd->outfile)
    {
        if (redir_outfile(cmd) < 0)
        {
            g_exit_status = 1;
            exit(g_exit_status);
        }
    }
    else if (cmd->next && !is_builtin_command(cmd->args[0]))
    {
        close(ctx->fdpipe[0]);
        dup2(ctx->fdpipe[1], STDOUT_FILENO);
        close(ctx->fdpipe[1]);
    }
    if (is_builtin_command(cmd->args[0]))
    {
        run_builtins(cmd, shell, env, ctx);
        if (cmd->next)
            exit(g_exit_status);
    }
    else
    {
        exec(cmd->args, shell, env);
    }
    return (0);
}

void parent_process(t_cmd *cmd, t_context *ctx)
{
    ctx->last_pid = ctx->pids;
    if (ctx->prev_pipe != -1)
        close(ctx->prev_pipe);
    if (cmd->next)
        close(ctx->fdpipe[1]);
}

int execute_commands(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
    int status;

    ctx->prev_pipe = -1;

    while (cmd)
    {
        if (cmd->next)
            pipe(ctx->fdpipe);
        ctx->pids = fork();
        if (ctx->pids == 0)
            child_process(cmd, ctx, shell, env);
        else
            parent_process(cmd, ctx);
        ctx->prev_pipe = ctx->fdpipe[0];
        cmd = cmd->next;
    }
    waitpid(ctx->last_pid, &status, 0);
    while (wait(NULL) > 0)
        ;
    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_exit_status = 128 + WTERMSIG(status);
    return (g_exit_status);
}
>>>>>>> 464fc4b7d25ca247f4503ad3331a029baceec3da
