/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:10:02 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 06:12:05 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	set_arg_opt_from_arg(t_arg_opt *opt, const char arg)
{
	if (arg == 'l')
		return (opt->long_format = 1);
	else if (arg == 'R')
		return (opt->recursive = 1);
	else if (arg == 'a')
		return (opt->hidden = 1);
	else if (arg == 'r')
		return ((opt->sort = FT_SORT_REV) == FT_SORT_REV);
	else if (arg == 't')
		return (opt->sort = (opt->sort & FT_SORT_REV) | FT_SORT_TTIME);
	else if (arg == '1')
		return (opt->one_entry = 1);
	else if (arg == 'h')
		return (opt->human = 1);
	else if (arg == 'L')
		return (opt->follow_lnk = 1);
	else if (arg == 'f')
		return ((opt->sort = FT_NO_SORT) == FT_NO_SORT);
	return (0);
}

int			parse_arg(t_arg_opt *opt, const char *arg)
{
	size_t		idx;

	if (arg[0] != '-' || arg[1] == 0)
		return (0);
	idx = 1;
	while (arg[idx])
	{
		if (set_arg_opt_from_arg(opt, arg[idx]) == 0)
			exit(ft_puterr(1, ft_strjoin("ls: illegal option -- ",
							ft_strsub(arg, idx, 1))));
		idx++;
	}
	return (1);
}
