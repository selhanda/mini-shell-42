/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:59:20 by selhanda          #+#    #+#             */
/*   Updated: 2022/05/18 20:51:07 by selhanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execut(int infile, t_comp *comp, char **env, int what)
{
	int		pid;
	int		fd[2];
	int		outfile;
	char	*in;
	char	*out;

	pipe(fd);
	out = is_outfile(comp);
	in = is_infile(comp);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (ft_new_norm_func(out, fd[1], what, env) == -1)
			exit(0);
		outfile = ft_new_norm_func(out, fd[1], what, env);
		infile = func_for_infile_norm(infile, in, comp);
		close(fd[0]);
		if (thereis_infile(comp) && in == NULL)
			exit(1);
		ft_cammand_e(env, comp, infile, outfile);
	}
	ft_dala(pid, out, fd[1], env);
	free(in);
	return (fd[0]);
}

int	infile_for_norm_f(t_comp *comp, char *in)
{
	int	infile;

	infile = -1;
	if (is_hedoc(comp))
			infile = get_limiter(comp);
	else if (in != NULL)
		infile = open(in, O_RDONLY);
	return (infile);
}

void	ft_lst_cmd(int infile, t_comp *comp, char **env, int what)
{
	int		outfile;
	int		pid;
	char	*in;
	char	*out;

	out = is_outfile(comp);
	in = is_infile(comp);
	if (ft_cmd_norm(out, what, env) == -1)
		return ;
	outfile = ft_cmd_norm(out, what, env);
	infile = infile_norminette_func(infile, comp, in);
	if (infile == -1)
	{
		ft_free_machine(env);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (thereis_infile(comp) && in == NULL)
			exit(1);
		ft_cammand_e(env, comp, infile, outfile);
	}
	other_func_for_norm(pid, out, env, in);
}

void	ft_execution(t_list	*lst_comp, t_env **head)
{
	t_comp	*comp;
	int		i;
	int		infile;
	int		size;

	i = 0;
	infile = 0;
	size = ft_lstsize(lst_comp);
	comp = lst_comp->content;
	if (size == 1)
	{
		if (!comp)
			return ;
		ft_execute_one_cmd(comp, head, infile);
	}
	else
		infile = norm_fun_exec(size, infile, lst_comp, head);
	check_for_status(comp);
}

void	clear_files(char *out, char *in)
{
	free(out);
	free(in);
}
