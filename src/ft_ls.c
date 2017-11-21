/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:38:52 by briviere          #+#    #+#             */
/*   Updated: 2017/11/21 14:18:25 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls(char **av, t_arg_opt *opt)
{
	struct stat		path_stat;
	DIR				*dir;
	struct dirent	*ent;


	(void)opt;
	if (av[0] == 0)
		return (ft_puterr(0, "TODO: Read current directory"));
	stat(av[0], &path_stat);
	ft_putnbr(path_stat.st_mode);
	ft_putendl("");
	dir = opendir(av[0]);
	if (dir == 0)
		return (ft_puterr(0, "TODO: ls file"));
	while ((ent = readdir(dir)) != 0)
		ft_putendl(ent->d_name);
	closedir(dir);
	return (1);
}
