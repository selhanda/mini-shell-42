/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:07:09 by selhanda          #+#    #+#             */
/*   Updated: 2022/04/06 15:07:12 by selhanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_cmd_built(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

void		execute_built_cmd(t_comp *comp, int infile)
{
	char *in;
	char *out;
	int outfile;

	out = is_outfile(comp);
	in	= is_infile(comp);
	if (out == NULL)
		outfile = 1;
	else
		outfile = open(out, O_WRONLY | O_CREAT, 0666);
	if (in != NULL)
		infile = open(in, O_RDONLY);
	if (ft_strncmp(comp->data, "echo", 5) == 0)
		ft_echo(comp, outfile);
	if (ft_strncmp(comp->data, "cd", 3) == 0)
		ft_cd(comp);
	if (ft_strncmp(comp->data, "pwd", 4) == 0)
		ft_pwd(outfile);
	if (ft_strncmp(comp->data, "exit", 5) == 0)
		ft_exit(comp);
	// if (ft_strncmp(comp->data, "env", 4) == 0)
	// 	 ft_env();
	// if (ft_strncmp(comp->data, "export", 7) == 0)
	// 	ft_export()
	// if (ft_strcmp(comp->data, "unset", 6) == 0)
	// 	ft_unset(comp, env);
}
