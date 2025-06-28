/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:03:00 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 10:07:10 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_execute(t_cmd *cmd) {
    // TEMPORARY DEBUG
    // fprintf(stderr, "Executing: %s\n", cmd->path);
    for (int i = 0; cmd->args[i]; i++) {
        fprintf(stderr, "  argv[%d] = %s\n", i, cmd->args[i]);
    }
}

void child_process(t_cmd *tmp,t_context *ctx)
{
    
        if (ctx->prev_pipe != -1)
        {
                dup2(ctx->prev_pipe,STDIN_FILENO);
                close(ctx->prev_pipe);
    	}
        if (tmp->next)
        {
                dup2(ctx->fdpipe[1],STDOUT_FILENO);
                close(ctx->fdpipe[0]);
        	    close(ctx->fdpipe[1]);
        }
        // if (tmp->outfile || tmp->infile)
        //     redirection(tmp);
        print_execute(tmp);
        exec(tmp->args,ctx->env);
}

void parent_process(t_cmd *tmp , t_context *ctx)
{
    ctx->last_pid = ctx->pids;
    if (ctx->prev_pipe != -1)
        close(ctx->prev_pipe);
    if (tmp->next)
         close(ctx->fdpipe[1]);
}

int execute_commands(t_cmd *cmd,t_context *ctx)
{
    t_cmd *tmp;
    int status;

    ctx->prev_pipe = -1;
    tmp = cmd;

    while (tmp)
    {
        if (tmp->next)
            pipe(ctx->fdpipe);
        ctx->pids = fork();
        if (ctx->pids == 0)
            child_process(tmp,ctx);
        else
            parent_process(tmp,ctx);
        ctx->prev_pipe = ctx->fdpipe[0];
        tmp = tmp->next;
    }
    waitpid(ctx->last_pid,&status,0);
    while (wait(NULL) > 0);
    return (status);
}



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

// void child_process(t_cmd *tmp, t_context *ctx) {
//     // Handle input redirection from previous command
//     if (ctx->prev_pipe != -1) {
//         dup2(ctx->prev_pipe, STDIN_FILENO);
//         close(ctx->prev_pipe);
//     }
    
//     // Handle output redirection to next command
//     if (tmp->next) {
//         close(ctx->fdpipe[0]);  // Close read end first
//         dup2(ctx->fdpipe[1], STDOUT_FILENO);
//         close(ctx->fdpipe[1]);
//     }
    
//     // Handle file redirections (if implemented)
//     // if (tmp->infile || tmp->outfile)
//     //     handle_redirection(tmp);
    
//     // Execute the command
//     exec_command(tmp->args, ctx->env);
    
//     // If we get here, exec failed
//     exit(EXIT_FAILURE);
// }
// int execute_commands(t_cmd *cmd, t_context *ctx) {
//     t_cmd *tmp = cmd;
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
//     while (tmp) {
//         if (tmp->next) 
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
//             child_process(tmp, ctx);
//         } else if (pid < 0) {
//             perror("fork");
//         } else {
//             // Parent process
//             ctx->pids[i++] = pid;
//             parent_process(ctx);
//         }
        
//         tmp = tmp->next;
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
