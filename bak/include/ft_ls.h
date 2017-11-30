/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:34 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 01:50:54 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include "libft.h"
# include <pwd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <uuid/uuid.h>

# define FT_ISDIR(mode) ((mode & S_IFDIR) == S_IFDIR)
# define FT_ISLNK(mode) ((mode & S_IFLNK) == S_IFLNK)

typedef struct	s_arg_opt {
	int		long_format;
	int		recursive;
	int		hidden;
	int		reverse;
	int		sort_time;
	int		one_entry;
	int		human;
}				t_arg_opt;

typedef struct	s_path {
	char			*path;
	char			*name;
	struct s_path	**sub_path;
	size_t			sub_path_len;
	int				is_dir;
	int				is_file;
	int				is_link;
	char			*permissions;
	size_t			nlink;
	char			*pw_name;
	char			*gr_name;
	size_t			size;
	char			*mtime;
	long			blocks;
}				t_path;

int		parse_arg(t_arg_opt *arg_opt, char *arg);
int		usage(int code);

void	print_error(char *err);
void	print_error2(char *err_s, char *err_e);
void	print_error3(char *err_s, char *err_m, char *err_e);

void	list_dirs_av(char **av, t_arg_opt *opt);
void	list_dirs(t_path **paths, t_arg_opt *opt);
void	list_files(t_path *path, t_arg_opt *opt);
char	*gather_permissions(const int mode);

int		count_files(size_t *dst, char *path, int hidden);
int		check_file_exists(char *path);
int		check_if_is_dir(char *path);

t_path	*ft_init_path(char *dir_path, char *name);
void	ft_set_path_info(t_path *path);
int		ft_set_dir_subfiles(t_path *path, int set_info, int hidden);
void	ft_sort_subpath(t_path *path, int (*cmp)(const char *, const char *));

#endif
