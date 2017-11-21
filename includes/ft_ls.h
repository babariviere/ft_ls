/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:34 by briviere          #+#    #+#             */
/*   Updated: 2017/11/21 17:09:02 by briviere         ###   ########.fr       */
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
# include <uuid/uuid.h>

typedef struct	s_arg_opt {
	int		long_format;
	int		recursive;
	int		hidden;
	int		reverse;
	int		sort_time;
}				t_arg_opt;

int		parse_arg(t_arg_opt *arg_opt, char *arg);
int		usage(int code);

int		ft_ls(char **av, t_arg_opt *opt);
void	print_permissions(const int mode);

#endif
