/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:38:52 by briviere          #+#    #+#             */
/*   Updated: 2017/11/24 14:39:31 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_files_rec(char *path, t_arg_opt *opt, size_t len);

void		gather_file_info_long_format(t_formatted *formatted, char *path,
		t_arg_opt *opt)
{
	struct stat		path_stat;
	time_t			file_time;
	char			*time_str;

	stat(path, &path_stat);
	ft_add_formatted_str(formatted,
			gather_permissions(path_stat.st_mode), 2);
	ft_add_formatted_str(formatted, ft_itoa(path_stat.st_nlink), 1);
	ft_add_formatted_str(formatted,
			ft_strdup(getpwuid(path_stat.st_uid)->pw_name), 2);
	ft_add_formatted_str(formatted,
			ft_strdup(getgrgid(path_stat.st_gid)->gr_name), (opt->human == 0 ? 2 : 3));
	if (opt->human == 0)
		ft_add_formatted_str(formatted, ft_itoa(path_stat.st_size), 1);
	else
		ft_add_formatted_str(formatted,
				ft_stoa_human_dec(path_stat.st_size), 1);
	file_time = path_stat.st_mtimespec.tv_sec;
	time_str = ft_strsub(ctime(&file_time), 4, 13);
	time_str[ft_strlen(time_str) - 1] = 0;
	ft_add_formatted_str(formatted, time_str, 1);
}

t_formatted	*gather_file_info(char *path, char *file, t_arg_opt *opt)
{
	t_formatted		*formatted;

	if ((formatted = ft_init_formatted((opt->long_format ? 7 : 1))) == 0)
		return (0);
	if (opt->long_format)
		gather_file_info_long_format(formatted, path, opt);
	ft_add_formatted_str(formatted, ft_strdup(file), 0);
	return (formatted);
}

void	list_files(char *path, t_arg_opt *opt)
{
	char			*dir_path;
	DIR				*dir;
	struct dirent	*ent;
	t_formatted		**formatteds;
	size_t			len;
	struct stat		path_stat;
	size_t			total_blocks;

	if (path == 0)
		path = ".";
	if (path[ft_strlen(path) - 1] != '/')
		dir_path = ft_strjoin(path, "/");
	else
		dir_path = path;
	len = count_files(dir_path);
	dir = opendir(path);
	if (dir == 0)
	{
		ft_puterr(0, "TODO: ls file");
		return ;
	}
	formatteds = ft_memalloc(sizeof(t_formatted) * len + 1);
	formatteds[len] = 0;
	len = 0;
	total_blocks = 0;
	while ((ent = readdir(dir)) != 0)
	{
		if ((ent->d_name[0] == '.' && opt->hidden) ||
			(ent->d_name[0] != '.'))
		{
			// TODO: stock path instead of two strjoin, lazy man
			formatteds[len++] = gather_file_info(ft_strjoin(dir_path, ent->d_name), ent->d_name, opt);
			if (opt->long_format)
			{
				stat(ft_strjoin(dir_path, ent->d_name), &path_stat);
				total_blocks += path_stat.st_blocks;
			}
		}
	}
	closedir(dir);
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
	if (opt->recursive)
		list_files_rec(dir_path, opt, len);
}

void	list_files_rec(char *path, t_arg_opt *opt, size_t len)
{
	DIR				*dir;
	struct stat		path_stat;
	struct dirent	*ent;
	char			**paths;
	size_t			idx;

	dir = opendir(path);
	idx = 0;
	paths = ft_memalloc(sizeof(char *) * (len + 1));
	while ((ent = readdir(dir)) != 0)
	{
		if (ft_strcmp(ent->d_name, ".") == 0 ||
				ft_strcmp(ent->d_name, "..") == 0)
			continue ;
		if (ent->d_name[0] == '.' && opt->hidden == 0)
			continue ;
		stat(ft_strjoin(path, ent->d_name), &path_stat);
		// TODO: idem than above
		if ((path_stat.st_mode & S_IFDIR) == S_IFDIR)
			paths[idx++] = ft_strjoin(path, ent->d_name);
	}
	closedir(dir);
	list_dirs(paths, opt);
}

void	list_dirs(char **paths, t_arg_opt *opt)
{
	if (paths == 0 || *paths == 0)
		return ;
	while (*paths)
	{
		ft_putchar('\n');
		ft_putstr(*paths);
		ft_putstr(":\n");
		list_files(*paths, opt);
		paths++;
	}
}

void	list_dirs_av(char **av, t_arg_opt *opt)
{
	if (av == 0 || *av == 0)
	{
		list_files(".", opt);
		return ;
	}
	if (av[0] && av[1])
	{
		ft_putstr(*av);
		ft_putstr(":\n");
	}
	list_files(*av, opt);
	av++;
	while (*av)
	{
		ft_putchar('\n');
		ft_putstr(*av);
		ft_putstr(":\n");
		list_files(*av, opt);
		av++;
	}
}
