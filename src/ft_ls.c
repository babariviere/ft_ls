/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:38:52 by briviere          #+#    #+#             */
/*   Updated: 2017/11/24 10:55:33 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
			ft_strdup(getgrgid(path_stat.st_gid)->gr_name), 2);
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
	formatted->tab = ft_memalloc(sizeof(t_formatted) * formatted->len);
	formatted->padding = ft_memalloc(sizeof(int) * (formatted->len - 1));
	if (opt->long_format)
		gather_file_info_long_format(formatted, path, opt);
	ft_add_formatted_str(formatted, ft_strdup(file), 0);
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
		ft_calibrate_formatted_range(formatteds, 1, 5, -1);
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
	return (1);
}
