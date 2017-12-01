/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 04:47:06 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 23:21:30 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	make_sort(t_path **path, t_arg_opt *opt)
{
	if ((opt->sort & FT_SORT_NAME) == FT_SORT_NAME)
		ft_sort_subpath(path, ((opt->sort & FT_SORT_REV) == FT_SORT_REV ?
					ft_strcmp_rev : ft_strcmp));
	else if ((opt->sort & FT_SORT_ATIME) == FT_SORT_ATIME)
		ft_sort_subpath_atime(path, (opt->sort & FT_SORT_REV) == FT_SORT_REV);
	else if ((opt->sort & FT_SORT_MTIME) == FT_SORT_MTIME)
		ft_sort_subpath_mtime(path, (opt->sort & FT_SORT_REV) == FT_SORT_REV);
	else if ((opt->sort & FT_SORT_CTIME) == FT_SORT_CTIME)
		ft_sort_subpath_ctime(path, (opt->sort & FT_SORT_REV) == FT_SORT_REV);
}

void	list_files(t_path **path, t_arg_opt *opt)
{
	size_t	idx;

	if (path == 0)
		return ;
	make_sort(path, opt);
	if (opt->long_format)
		print_list_format(path, opt);
	else if (opt->one_entry)
	{
		idx = 0;
		while (path[idx])
			ft_putendl(path[idx++]->name);
	}
}
