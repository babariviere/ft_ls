/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:38:52 by briviere          #+#    #+#             */
/*   Updated: 2017/11/23 17:20:56 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// TODO: print in well formatted column
// TODO: store in struct tab string and tab size_t for len of each strings
// find the longest and print
// read argument and print with format
t_formatted	*gather_file_info(char *path, char *file, t_arg_opt *opt)
{
	t_formatted		*formatted;
	struct stat		path_stat;
	time_t			file_time;
	char			*time_str;

	if (init_formatted(&formatted, (opt->long_format ? 7 : 1)) == 0)
		return (0);
	formatted->tab = ft_memalloc(sizeof(t_formatted) * formatted->len);
	formatted->padding = ft_memalloc(sizeof(int) * (formatted->len - 1));
	stat(path, &path_stat);
	if (opt->long_format)
	{
		add_formatted_str(formatted, gather_permissions(path_stat.st_mode), 2);
		add_formatted_str(formatted, ft_itoa(path_stat.st_nlink), 1);
		add_formatted_str(formatted, getpwuid(path_stat.st_uid)->pw_name, 2);
		add_formatted_str(formatted, getgrgid(path_stat.st_gid)->gr_name, 2);
		add_formatted_str(formatted, ft_itoa(path_stat.st_size), 1);
		file_time = path_stat.st_mtimespec.tv_sec;
		time_str = ft_strdup(ctime(&file_time));
		time_str[ft_strlen(time_str) - 1] = 0;
		add_formatted_str(formatted, time_str, 1);
	}
	add_formatted_str(formatted, file, 0);
	return (formatted);
}

int		ft_ls(char **av, t_arg_opt *opt)
{
	char			*dir_path;
	DIR				*dir;
	struct dirent	*ent;
	t_formatted		**formatteds;
	size_t			len;

	if (av[0] == 0)
		av[0] = ".";
	dir = opendir(av[0]);
	if (av[0][ft_strlen(av[0]) - 1] != '/')
		dir_path = ft_strjoin(av[0], "/");
	else
		dir_path = av[0];
	if (dir == 0)
		return (ft_puterr(0, "TODO: ls file"));
	len = 0;
	while (readdir(dir) != 0)
		len++;
	closedir(dir);
	dir = opendir(av[0]);
	formatteds = ft_memalloc(sizeof(t_formatted) * len + 1);
	formatteds[len] = 0;
	len = 0;
	while ((ent = readdir(dir)) != 0)
	{
		if ((ent->d_name[0] == '.' && opt->hidden) ||
			(ent->d_name[0] != '.'))
			formatteds[len++] = gather_file_info(ft_strjoin(dir_path, ent->d_name), ent->d_name, opt);
	}
	closedir(dir);
	if (opt->long_format)
	{
		calibrate_formatted(formatteds, 1, -1);
		calibrate_formatted(formatteds, 2, -1);
		calibrate_formatted(formatteds, 3, -1);
		calibrate_formatted(formatteds, 4, -1);
		calibrate_formatted(formatteds, 5, -1);
	}
	len = 0;
	while (formatteds[len])
	{
		print_formatted(formatteds[len++]);
		if (opt->one_entry == 1)
			ft_putchar('\n');
	}
	return (1);
}
