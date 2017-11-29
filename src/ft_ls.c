/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:38:52 by briviere          #+#    #+#             */
/*   Updated: 2017/11/29 20:09:08 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_files_rec(char *path, t_arg_opt *opt, size_t len);

void		gather_file_info_long_format(t_formatted *formatted, t_path *path,
		t_arg_opt *opt)
{
	ft_add_formatted_str(formatted,
			ft_strdup(path->permissions), 2);
	ft_add_formatted_str(formatted, ft_itoa(path->nlink), 1);
	ft_add_formatted_str(formatted,
			ft_strdup(path->pw_name), 2);
	ft_add_formatted_str(formatted,
			ft_strdup(path->gr_name), (opt->human == 0 ? 2 : 3));
	if (opt->human == 0)
		ft_add_formatted_str(formatted, ft_itoa(path->size), 1);
	else
		ft_add_formatted_str(formatted,
				ft_stoa_human_dec(path->size), 1);
	ft_add_formatted_str(formatted, ft_strdup(path->mtime), 1);
}

t_formatted	*gather_file_info(t_path *path, t_arg_opt *opt)
{
	t_formatted		*formatted;

	if ((formatted = ft_init_formatted((opt->long_format ? 7 : 1))) == 0)
		return (0);
	if (opt->long_format)
		gather_file_info_long_format(formatted, path, opt);
	ft_add_formatted_str(formatted, ft_strdup(path->name), 0);
	return (formatted);
}

void	list_files(t_path *path, t_arg_opt *opt)
{
	char			*dir_path;
	t_formatted		**formatteds;
	size_t			len;
	size_t			total_blocks;

	if (path == 0)
		return ;
	if (path->path[ft_strlen(path->path) - 1] != '/')
		dir_path = ft_strjoin(path->path, "/");
	else
		dir_path = path->path;
	formatteds = ft_memalloc(sizeof(t_formatted) * (path->sub_path_len + 1 + opt->hidden * 2));
	formatteds[path->sub_path_len] = 0;
	total_blocks = 0;
	len = 0;
	while (len < path->sub_path_len)
	{
		formatteds[len] = gather_file_info(path->sub_path[len], opt);
		if (opt->long_format)
			total_blocks += path->sub_path[len]->blocks;
		len++;
	}
	if (opt->long_format)
	{
		ft_putstr("total ");
		ft_putnbr(total_blocks);
		ft_putchar('\n');
		ft_calibrate_formatted_range(formatteds, 1, 5, -1);
		ft_sort_formatteds(formatteds, 6, (opt->reverse ? ft_strcmp_rev : ft_strcmp));
	}
	else
		ft_sort_formatteds(formatteds, 0, (opt->reverse ? ft_strcmp_rev : ft_strcmp));
	len = 0;
	while (formatteds[len])
	{
		ft_print_formatted(formatteds[len]);
		ft_free_formatted(formatteds + len);
		len++;
		if (opt->one_entry == 1)
			ft_putchar('\n');
	}
	free(formatteds);
}

void	list_dir(t_path *path, t_arg_opt *opt, int start, int is_printed)
{
	size_t		idx;

	if (path == 0)
	{
		return ;
	}
	if (!check_file_exists(path->path))
	{
		print_error2(path->path, ": No such file or directory");
		return ;
	}
	if (opt->long_format)
		ft_set_path_info(path);
	if (ft_set_dir_subfiles(path, opt->recursive, opt->long_format,
				opt->hidden, 1) == -1)
	{
		print_error3(path->path, ": ", strerror(errno));
		return ;
	}
	ft_sort_subpath(path, (opt->reverse ? ft_strcmp_rev : ft_strcmp));
	if (!path->is_dir)
	{
		path->sub_path = malloc(sizeof(t_path *) * 2);
		path->sub_path[0] = path;
		path->sub_path[1] = 0;
		path->sub_path_len = 1;
		list_files(path, opt);
		return ;
	}
	if (is_printed)
		ft_putchar('\n');
	if (!start)
		ft_putendl(ft_strjoin(path->path, ":"));
	list_files(path, opt);
	idx = 0;
	if (opt->recursive)
	{
		while (idx < path->sub_path_len)
		{
			if (!(ft_strequ(path->sub_path[idx]->name, ".") || ft_strequ(path->sub_path[idx]->name, "..")))
				list_dir(path->sub_path[idx], opt, 0, 1);
			idx++;
		}
	}
	free(path);
}

void	list_dirs_av(char **av, t_arg_opt *opt)
{
	if (*av == 0)
	{
		list_dir(ft_init_path("", "."), opt, 1, 0);
		return ;
	}
	if (av[0] && av[1])
	{
		ft_putstr(*av);
		ft_putstr(":\n");
	}
	list_dir(ft_init_path("", *av), opt, 1, 0);
	av++;
	while (*av)
	{
		ft_putchar('\n');
		ft_putstr(*av);
		ft_putstr(":\n");
		list_dir(ft_init_path("", *av), opt, 1, 0);
		av++;
	}
}
