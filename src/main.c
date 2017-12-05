/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:41:22 by briviere          #+#    #+#             */
/*   Updated: 2017/12/05 09:23:55 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_dir(char *dir, t_arg arg)
{
	t_path	*path;
	t_path	**spath;
	int		idx;

	path = ft_init_path(0, dir, HAS_FLAG(arg, ARG_FOLLOW_LNK));
	if (path == 0)
		return ;
	spath = ft_get_subpath(path->path, HAS_FLAG(arg, ARG_FOLLOW_LNK),
			HAS_FLAG(arg, ARG_HIDDEN));
	if (spath == 0)
	{
		spath = ft_memalloc(sizeof(t_path *) * 2);
		spath[0] = ft_init_path(0, dir, HAS_FLAG(arg, ARG_FOLLOW_LNK));
		spath[1] = 0;
	}
	list_files(spath, arg);
	idx = 0;
	while (spath[idx])
	{
		ft_free_path(spath + idx);
		idx++;
	}
	free(spath);
	ft_free_path(&path);
}

void		list_av(char **av, t_arg arg)
{
	if (*av == 0)
		list_dir(".", arg);
	while (*av)
	{
		list_dir(*av, arg);
		av++;
	}
}

int			main(int ac, char **av)
{
	t_arg		arg;
	int			idx;

	arg = ARG_ONE_ENT | ARG_SORT;
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
			if (parse_arg(&arg, av[idx++]) == 0)
				return (usage(1));
		}
		else
			break ;
	}
	list_av(av + idx, arg);
	return (0);
}
