/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/06 13:23:01 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_sort_subpath_btime(t_path **paths, int rev)
{
	size_t		idx;
	size_t		sub_idx;

	if (paths == 0)
		return ;
	idx = 0;
	while (paths[idx] && paths[idx + 1])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (!rev && paths[idx]->stat->st_birthtime <=
					paths[sub_idx]->stat->st_birthtime)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_BTIME, rev);
			else if (rev && paths[idx]->stat->st_birthtime >=
					paths[sub_idx]->stat->st_birthtime)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_BTIME, rev);
			sub_idx++;
		}
		idx++;
	}
}

void			ft_sort_subpath_size(t_path **paths, int rev)
{
	size_t		idx;
	size_t		sub_idx;

	if (paths == 0)
		return ;
	idx = 0;
	while (paths[idx] && paths[idx + 1])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (!rev && paths[idx]->stat->st_size <=
					paths[sub_idx]->stat->st_size)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_SORT_SIZE, rev);
			else if (rev && paths[idx]->stat->st_size >=
					paths[sub_idx]->stat->st_size)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_SORT_SIZE, rev);
			sub_idx++;
		}
		idx++;
	}
}
