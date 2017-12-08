/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:10:02 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 15:26:17 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	set_arg_opt_time(t_arg *opt, const char arg)
{
	*opt = *opt & ~ARG_MTIME & ~ARG_CTIME & ~ARG_BTIME & ~ARG_ATIME;
	if (arg == 't')
		return (*opt |= ARG_SORT | ARG_SORT_TIME | ARG_MTIME);
	else if (arg == 'u')
		return (*opt |= ARG_ATIME);
	else if (arg == 'c')
		return (*opt |= ARG_CTIME);
	else if (arg == 'U')
		return (*opt |= ARG_BTIME);
	return (0);
}

static int	set_arg_opt_from_arg(t_arg *opt, const char arg)
{
	if (arg == 'l')
		return (*opt |= ARG_LIST_FMT);
	else if (arg == 'R')
		return (*opt |= ARG_REC);
	else if (arg == 'a')
		return (*opt |= ARG_HIDDEN);
	else if (arg == 'r')
		return (*opt |= ARG_REV);
	else if (arg == '1')
		return (*opt |= ARG_ONE_ENT);
	else if (arg == 'h')
		return (*opt |= ARG_HUMAN);
	else if (arg == 'L')
		return (*opt |= ARG_FOLLOW_LNK);
	else if (arg == 'f')
		return (*opt = (*opt | ARG_HIDDEN) & ~ARG_SORT &
				~ARG_SORT_TIME & ~ARG_SORT_SIZE);
	else if (arg == 'S')
		return (*opt |= ARG_SORT_SIZE);
	return (set_arg_opt_time(opt, arg));
}

int			parse_arg(t_arg *opt, const char *arg)
{
	size_t		idx;

	if (arg[0] != '-' || arg[1] == 0)
		return (0);
	idx = 1;
	while (arg[idx])
	{
		if (set_arg_opt_from_arg(opt, arg[idx]) == 0)
		{
			ft_putstr_fd("ls: illegal option -- ", 2);
			ft_putchar_fd(arg[idx], 2);
			ft_putchar_fd('\n', 2);
			exit(usage(1));
		}
		idx++;
	}
	return (1);
}
