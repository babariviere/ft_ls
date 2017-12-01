/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:41:22 by briviere          #+#    #+#             */
/*   Updated: 2017/12/01 02:09:16 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_dir(char *dir, t_arg_opt *opt)
{
	t_path	*path;
	t_path	**spath;
	int		idx;

	path = ft_init_path(0, dir, opt->follow_lnk);
	if (path == 0)
		return ;
	spath = ft_get_subpath(path->path, opt->follow_lnk, opt->hidden);
	list_files(spath, opt);
	idx = 0;
	while (spath[idx])
	{
		ft_free_path(spath + idx);
		idx++;
	}
	free(spath);
	ft_free_path(&path);
}

void	list_av(char **av, t_arg_opt *opt)
{
	if (*av == 0)
		list_dir(".", opt);
	while (*av)
	{
		list_dir(*av, opt);
		av++;
	}
}

int		main(int ac, char **av)
{
	t_arg_opt	*opt;
	int			idx;

	if ((opt = ft_memalloc(sizeof(t_arg_opt))) == 0)
		return (1);
	opt->one_entry = 1;
	opt->sort = FT_SORT_NAME;
	idx = 1;
	while (idx < ac)
	{
		if (av[idx][0] == '-' && av[idx][1] == '-')
		{
			idx++;
			break ;
		}
		else if (av[idx][0] == '-' && av[idx][1] != 0)
		{
			if (parse_arg(opt, av[idx++]) == 0)
				return (usage(1));
		}
		else
			break ;
	}
	list_av(av + idx, opt);
	free(opt);
	return (0);
}
