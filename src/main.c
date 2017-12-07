/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:41:22 by briviere          #+#    #+#             */
/*   Updated: 2017/12/07 17:26:21 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_dir(char *dir, t_arg arg)
{
	t_path	*path;
	t_list	*spath;

	path = ft_init_path(0, dir, -1);
	ft_path_readstat(path, HAS_FLAG(arg, ARG_FOLLOW_LNK));
	if (path == 0)
	{
		print_last_err(dir);
		return ;
	}
	if (!FT_ISDIR(path->mode))
		spath = ft_lstnew(ft_init_path(0, dir, DT_REG), sizeof(t_path));
	else
		spath = ft_get_subpath(path->path, HAS_FLAG(arg, ARG_FOLLOW_LNK),
				HAS_FLAG(arg, ARG_HIDDEN),
				HAS_FLAG(arg, ARG_LIST_FMT) || HAS_FLAG(arg, ARG_SORT));
	if (spath == 0)
	{
		ft_putstr("ls: ");
		perror(dir);
		return ;
	}
	list_files(spath, arg);
	ft_lstdel(&spath, free_spath);
	ft_free_path(&path);
}

int			path_is_file(t_list *elem)
{
	t_path		*p;

	p = elem->content;
	return (!FT_ISDIR(p->mode));
}

void		print_files(t_list *list, t_arg arg)
{
	t_list		*files;

	files = ft_lstfilter(list, path_is_file);
	list_files(files, arg);
}


void		list_av(char **av, t_arg arg)
{
	t_list	*paths;
	t_list	*path;
	size_t	idx;
	int		print;
	int		has_file;

	if (*av == 0)
		list_dir(".", arg);
	print = av[0] && av[1];
	idx = 0;
	has_file = 0;
	paths = 0;
	while (av[idx])
	{
		path = ft_lstnew(ft_init_path(0, av[idx++], -1), sizeof(t_path));
		ft_path_readstat(path->content, HAS_FLAG(arg, ARG_FOLLOW_LNK));
		if (path->content && !FT_ISDIR(((t_path *)path->content)->mode))
			has_file = 1;
		if (path)
			ft_lstpush(&paths, path);
	}
	if (!HAS_FLAG(arg, ARG_SORT_TIME) && HAS_FLAG(arg, ARG_SORT))
		ft_make_sort_paths(paths, arg);
	print_files(paths, arg);
	if (!HAS_FLAG(arg, ARG_SORT_TIME) && HAS_FLAG(arg, ARG_SORT))
		ft_make_sort_paths(paths, arg);
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
	free(paths);
}

int			main(int ac, char **av)
{
	t_arg		arg;
	int			idx;

	arg = ARG_ONE_ENT | ARG_SORT;
	idx = 1;
	while (idx < ac)
	{
		if (av[idx][0] == '-' && av[idx][1] == '-' && av[idx][2] == 0)
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
