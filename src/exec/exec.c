/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:03:00 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/30 19:29:58 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_builtin_command(char *command)
{
    if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "pwd") ||
        !ft_strcmp(command, "echo") || !ft_strcmp(command, "exit") ||
        !ft_strcmp(command, "env") || !ft_strcmp(command, "export") ||
        !ft_strcmp(command, "unset"))
    {
        return 1;
    }
    return 0;
}

int execute_builtins(t_cmd *cmd, t_shell *shell,t_env *env)
{
    if (!ft_strcmp(cmd->args[0], "cd"))
        return ft_cd(env, cmd->args);
    else if (!ft_strcmp(cmd->args[0], "pwd"))
        return ft_pwd(&cmd->args[0]);
    else if (!ft_strcmp(cmd->args[0], "echo"))
        return ft_echo(&cmd->args[0]);
    else if (!ft_strcmp(cmd->args[0], "env"))
        return ft_env(env,shell,cmd->args);
    else if (!ft_strcmp(cmd->args[0], "export"))
        return ft_export1(&shell,&cmd->args[0],env);
    else if (!ft_strcmp(cmd->args[0], "unset"))
        return ft_unset(&shell,env,cmd->args);
    return 0;
}

int  run_builtins(t_cmd *cmd,t_shell *shell,t_env *env,t_context *ctx)
{
    int save_stdin;
    int save_stdout;
    if (fork() == 0)
    {
        if (is_builtin_command(cmd->args[0])) 
        {
            save_stdin = dup(STDIN_FILENO);
            save_stdout = dup(STDOUT_FILENO);
            if (cmd->infile || cmd->outfile)
            {
                if (redirection(cmd) == -1)
                {
                    dup2(save_stdin, STDIN_FILENO);
                    dup2(save_stdout, STDOUT_FILENO);
                    close(save_stdin);
                    close(save_stdout);
                    exit(0);
                }
            }
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
        }
    }
    else
        wait(NULL);
    return (0);
}


int child_process(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
    
    if (!cmd->args[0])
    {
        if (cmd->infile || cmd->outfile)
        {
            redirection(cmd);
        }
        exit(0);
    }
    if (ctx->prev_pipe != -1) 
    {
        dup2(ctx->prev_pipe, STDIN_FILENO);
        close(ctx->prev_pipe);
    }
    else if(cmd->infile)
            redirection(cmd);
    if (cmd->next)
    {
        close(ctx->fdpipe[0]);
        dup2(ctx->fdpipe[1],STDOUT_FILENO);
        close(ctx->fdpipe[1]);
    }
    if (is_builtin_command(cmd->args[0]))
    {
        run_builtins(cmd,shell,env,ctx);
        if (cmd->next)
            exit(0);
    }
    else
        exec(cmd->args,shell,env);
    
    return (0);
}

void parent_process(t_cmd *cmd , t_context *ctx)
{
    ctx->last_pid = ctx->pids;
    if (ctx->prev_pipe != -1)
        close(ctx->prev_pipe);
    if (cmd->next)
         close(ctx->fdpipe[1]);
}

int execute_commands(t_cmd *cmd,t_context *ctx,t_shell *shell,t_env *env)
{
    int status;

    ctx->prev_pipe = -1;

    while (cmd)
    {
        if (cmd->next)
            pipe(ctx->fdpipe);
        ctx->pids = fork();
        if (ctx->pids == 0)
            child_process(cmd,ctx,shell,env);
        else
            parent_process(cmd,ctx);
        ctx->prev_pipe = ctx->fdpipe[0];
        cmd = cmd->next;
    }
    waitpid(ctx->last_pid,&status,0);
    while (wait(NULL) > 0);
    return (status);
}

// test code 

// void exec_command(char **args, char **env) {
//     char *full_path;
    
//     // Check for absolute path
//     if (strchr(args[0], '/')) {
//         execve(args[0], args, env);
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }
    
//     // Search in PATH
//     char *path = getenv("PATH");
//     if (!path) {
//         fprintf(stderr, "minishell: PATH not set\n");
//         exit(EXIT_FAILURE);
//     }

//     char *path_copy = strdup(path);
//     char *dir = strtok(path_copy, ":");
//     while (dir) {
//         full_path = malloc(strlen(dir) + strlen(args[0]) + 2);
//         sprintf(full_path, "%s/%s", dir, args[0]);
        
//         if (access(full_path, X_OK) == 0) {
//             execve(full_path, args, env);
//             // If execve returns, it failed
//             perror("execve");
//             free(full_path);
//             free(path_copy);
//             exit(EXIT_FAILURE);
//         }
        
//         free(full_path);
//         dir = strtok(NULL, ":");
//     }
    
//     free(path_copy);
//     fprintf(stderr, "minishell: command not found: %s\n", args[0]);
//     exit(127);  // Standard "command not found" exit code
// }

// void parent_process(t_context *ctx) {
//     // Close previous pipe if exists
//     if (ctx->prev_pipe != -1) {
//         close(ctx->prev_pipe);
//     }
    
//     // Save current pipe for next command
//     if (ctx->fdpipe[1] != -1) {
//         close(ctx->fdpipe[1]);  // Close write end in parent
//         ctx->prev_pipe = ctx->fdpipe[0];  // Save read end for next
//     } else {
//         ctx->prev_pipe = -1;
//     }
// }

// void child_process(t_cmd *cmd, t_context *ctx) {
//     // Handle input redirection from previous command
//     if (ctx->prev_pipe != -1) {
//         dup2(ctx->prev_pipe, STDIN_FILENO);
//         close(ctx->prev_pipe);
//     }
    
//     // Handle output redirection to next command
//     if (cmd->next) {
//         close(ctx->fdpipe[0]);  // Close read end first
//         dup2(ctx->fdpipe[1], STDOUT_FILENO);
//         close(ctx->fdpipe[1]);
//     }
    
//     // Handle file redirections (if implemented)
//     // if (cmd->infile || cmd->outfile)
//     //     handle_redirection(cmd);
    
//     // Execute the command
//     exec_command(cmd->args, ctx->env);
    
//     // If we get here, exec failed
//     exit(EXIT_FAILURE);
// }
// int execute_commands(t_cmd *cmd, t_context *ctx) {
//     t_cmd *cmd = cmd;
//     int status;
//     int last_status = 0;

//     ctx->prev_pipe = -1;
//     ctx->pids = NULL;
//     int num_commands = 0;

//     // Count commands
//     for (t_cmd *t = cmd; t; t = t->next)
//         num_commands++;
    
//     // Allocate PID array
//     ctx->pids = malloc(sizeof(pid_t) * num_commands);
//     if (!ctx->pids)
//         return -1;

//     int i = 0;
//     while (cmd) {
//         if (cmd->next) 
//         {
//             if (pipe(ctx->fdpipe))
//             {
//                 perror("pipe");
//                 return -1;
//             }
//         } else {
//             ctx->fdpipe[0] = -1;
//             ctx->fdpipe[1] = -1;
//         }

//         pid_t pid = fork();
//         if (pid == 0) {
//             // Child process
//             child_process(cmd, ctx);
//         } else if (pid < 0) {
//             perror("fork");
//         } else {
//             // Parent process
//             ctx->pids[i++] = pid;
//             parent_process(ctx);
//         }
        
//         cmd = cmd->next;
//     }

//     // Wait for all child processes
//     for (int j = 0; j < num_commands; j++) {
//         waitpid(ctx->pids[j], &status, 0);
//         if (WIFEXITED(status)) {
//             last_status = WEXITSTATUS(status);
//         }
//     }

//     free(ctx->pids);
//     return last_status;
// }
