/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:07:09 by selhanda          #+#    #+#             */
/*   Updated: 2022/05/16 18:07:10 by selhanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_built(char *cmd)
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

void	ft_do_built_cmd(t_comp *comp, int outfile, t_env **head)
{
	if (ft_strncmp(comp->data, "echo", 5) == 0)
		ft_echo(comp, outfile);
	if (ft_strncmp(comp->data, "cd", 3) == 0)
		ft_cd(comp, head);
	if (ft_strncmp(comp->data, "pwd", 4) == 0)
		ft_pwd(outfile);
	if (ft_strncmp(comp->data, "exit", 5) == 0)
		ft_exit(comp);
	if (ft_strncmp(comp->data, "env", 4) == 0)
		ft_env(*head, comp, outfile);
	if (ft_strncmp(comp->data, "export", 7) == 0)
		ft_export(comp, head, outfile);
	if (ft_strncmp(comp->data, "unset", 6) == 0)
		ft_unset(comp, head);
}

void	execute_built_cmd(t_comp *comp, int infile, t_env **head, int what)
{
	char	*in;
	char	*out;
	int		outfile;

	g_status = 0;
	out = is_outfile(comp);
	in = is_infile(comp);
	outfile = norm_for_outfile_two(out, what);
	if (outfile == -1)
	{
		perror(out);
		return ;
	}
	if (is_hedoc(comp))
		infile = get_limiter(comp);
	else if (in != NULL)
		infile = open(in, O_RDONLY);
	if (infile == -1)
		return ;
	if (thereis_infile(comp) && in == NULL)
		return ;
	free(out);
	free(in);
	ft_do_built_cmd(comp, outfile, head);
}

int	ft_who_infile(t_comp *comp, char *in)
{
	int	infile;

	infile = 0;
	if (is_hedoc(comp))
		infile = get_limiter(comp);
	else if (in != NULL)
		infile = open(in, O_RDONLY);
	return (infile);
}

int	execute_builtin_cmds(t_comp *comp, int infile, t_env **head, int what)
{
	char	*in;
	char	*out;
	int		outfile;
	int		fd[2];

	pipe(fd);
	g_status = 0;
	out = is_outfile(comp);
	in = is_infile(comp);
	if (out == NULL)
		outfile = fd[1];
	else
		outfile = open_out_file(what, out);
	infile = ft_who_infile(comp, in);
	if (outfile == -1)
	{
		ft_norm_cmd_s_f(out);
		return (0);
	}
	if (thereis_infile(comp) && in == NULL)
		return (0);
	ft_do_built_cmd(comp, outfile, head);
	close(fd[1]);
	clear_files(out, in);
	return (fd[0]);
}
