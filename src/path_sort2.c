/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/07 13:13:49 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_path_cmp_name(const t_path *p1, const t_path *p2)
{
	return (ft_strcmp(p1->name, p2->name));
}

int			ft_path_cmp_atime(const t_path *p1, const t_path *p2)
{
	if (p1->atime == p2->atime)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->atime - p1->atime);
}

int			ft_path_cmp_btime(const t_path *p1, const t_path *p2)
{
	if (p1->btime == p2->btime)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->btime - p1->btime);
}

int			ft_path_cmp_ctime(const t_path *p1, const t_path *p2)
{
	if (p1->ctime == p2->ctime)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->ctime - p1->ctime);
}

int			ft_path_cmp_mtime(const t_path *p1, const t_path *p2)
{
	if (p1->mtime == p2->mtime)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->mtime - p1->mtime);
}
