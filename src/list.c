/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 04:47:06 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 06:59:45 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	make_sort(t_path **path, t_arg_opt *opt)
{
	if ((opt->sort & FT_SORT_NAME) == FT_SORT_NAME)
		ft_sort_subpath(path, ((opt->sort & FT_SORT_REV) == FT_SORT_REV ?
					ft_strcmp_rev : ft_strcmp));
}

void	list_files(t_path **path, t_arg_opt *opt)
{
	(void)opt;
	size_t	idx;
	if (path == 0)
		return ;
	make_sort(path, opt);
	if (opt->one_entry)
	{
		idx = 0;
		while (path[idx])
			ft_putendl(path[idx++]->name);
	}
}
