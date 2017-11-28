/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:34 by briviere          #+#    #+#             */
/*   Updated: 2017/11/28 12:34:32 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <grp.h>
# include "libft.h"
# include <pwd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <uuid/uuid.h>

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
	int				mode;
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

void	list_dirs_av(char **av, t_arg_opt *opt);
void	list_dirs(t_path **paths, t_arg_opt *opt);
void	list_files(t_path *path, t_arg_opt *opt);
char	*gather_permissions(const int mode);

size_t	count_files(char *path, int hidden);

t_path	*ft_init_path(char *dir_path, char *name);
void	ft_set_path_info(t_path *path);
void	ft_set_dir_subfiles(t_path *path, int rec, int set_info, int hidden);
void	ft_print_path_and_sub(t_path *path, char *parent);
t_formatted **ft_path_to_formatteds(t_path *path, char *str);

#endif
