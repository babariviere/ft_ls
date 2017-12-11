/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:35:37 by briviere          #+#    #+#             */
/*   Updated: 2017/12/11 10:37:55 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			path_is_file(t_lst *elem)
{
	t_path		*p;

	p = elem->content;
	return (!FT_ISDIR(p->mode));
}

void		print_files(t_lst *list, t_arg arg)
{
	t_lst		*files;

	files = ft_lstfilter(list, path_is_file);
	if (!(arg & ARG_SORT_TIME) && (arg & ARG_SORT))
		ft_make_sort_paths(files, arg);
	list_files(files, arg);
	ft_lstdel(&files, free_spath);
}

void		print_dirs(t_lst *paths, t_arg arg, int print, int has_file)
{
	t_lst		*path;

	path = paths;
	while (path)
	{
		if (!FT_ISDIR(((t_path *)path->content)->mode))
		{
			path = path->next;
			continue ;
		}
		if (print)
		{
			if (path != paths || has_file)
				ft_putchar('\n');
			ft_putstr(((t_path *)path->content)->name);
			ft_putendl(":");
		}
		list_dir(((t_path *)path->content)->name, arg);
		path = path->next;
	}
}
