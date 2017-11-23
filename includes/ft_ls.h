/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:34 by briviere          #+#    #+#             */
/*   Updated: 2017/11/23 17:08:11 by briviere         ###   ########.fr       */
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
}				t_arg_opt;

int		parse_arg(t_arg_opt *arg_opt, char *arg);
int		usage(int code);

int		ft_ls(char **av, t_arg_opt *opt);
char	*gather_permissions(const int mode);

typedef struct	s_formatted {
	char	**tab;
	int		*padding;
	size_t	idx;
	size_t	len;
}				t_formatted;

int		init_formatted(t_formatted **formatted, size_t len);
void	add_formatted_str(t_formatted *formatted, char *str, int next_padding);
void	print_formatted(t_formatted *formatted);
void	calibrate_formatted(t_formatted **formatteds, size_t tab_idx, size_t diff_idx);

#endif
