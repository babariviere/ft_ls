/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:41:22 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 06:09:03 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_arg_opt	*opt;
	int			idx;

	if ((opt = ft_memalloc(sizeof(t_arg_opt))) == 0)
		return (1);
	opt->one_entry = 1;
	opt->sort = FT_SORT_MTIME;
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
	t_path	*path = ft_init_path(0, ".", opt->follow_lnk);
	t_path	**spath = ft_get_subpath(path->path, opt->follow_lnk, opt->hidden);
	idx = 0;
	while (spath[idx])
	{
		ft_putendl(spath[idx]->name);
		ft_free_path(spath + idx++);
	}
	free(spath);
	ft_free_path(&path);
	free(opt);
	return (0);
}
