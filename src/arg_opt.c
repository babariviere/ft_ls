/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:10:02 by briviere          #+#    #+#             */
/*   Updated: 2017/11/23 09:34:57 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	set_opt_from_arg(t_arg_opt *arg_opt, char arg)
{
	if (arg == 'l')
		return (arg_opt->long_format = 1);
	else if (arg == 'R')
		return (arg_opt->recursive = 1);
	else if (arg == 'a')
		return (arg_opt->hidden = 1);
	else if (arg == 'r')
		return (arg_opt->reverse = 1);
	else if (arg == 't')
		return (arg_opt->sort_time = 1);
	else if (arg == '1')
		return (arg_opt->one_entry = 1);
	return (0);
}

int			parse_arg(t_arg_opt *arg_opt, char *arg)
{
	size_t		idx;

	if (arg[0] != '-' || arg[1] == 0)
		return (0);
	idx = 1;
	while (arg[idx])
	{
		if (set_opt_from_arg(arg_opt, arg[idx]) == 0)
			return (ft_puterr(0, ft_strjoin("ft_ls: illegal option -- ",
							ft_strsub(arg, idx, 1))));
		idx++;
	}
	return (1);
}
