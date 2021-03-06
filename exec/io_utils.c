/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:47:31 by selhanda          #+#    #+#             */
/*   Updated: 2022/05/16 17:55:00 by selhanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	outfile_len(t_comp *head)
{
	int	len;

	len = 0;
	while (head)
	{
		if (head->whatisthis == 4)
			len++;
		head = head->next;
	}
	return (len);
}

char	*opens_files(char **files, int len)
{
	int	i;
	int	fd;

	i = 0;
	while (i < len)
	{
		if (files[i + 1] == NULL)
			return (ft_strdup(files[i]));
		else
		{
			fd = open(files[i], O_WRONLY | O_CREAT, 0666);
			if (fd == -1)
			{
				perror(files[i]);
				g_status = 1;
			}
			close(fd);
		}
		i++;
	}
	return (NULL);
}

void	ft_put_error_fd(char *str)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	g_status = 1;
}

char	*try_open_file(int fd, char *file)
{
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_put_error_fd(file);
		return (NULL);
	}
	close(fd);
	return (ft_strdup(file));
}

char	*infile_files(char **files, int len)
{
	int	i;
	int	fd;

	i = 0;
	while (i < len)
	{
		if (files[i + 1] == NULL)
			return (try_open_file(fd, files[i]));
		else
		{
			fd = open(files[i], O_RDONLY);
			if (fd == -1)
			{
				ft_put_error_fd(files[i]);
				break ;
			}
			close(fd);
		}
		i++;
	}
	return (NULL);
}
