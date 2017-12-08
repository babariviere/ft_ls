/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 12:32:48 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 13:47:56 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_path_readstat_sub(t_path *path, struct stat st)
{
	path->mode = st.st_mode;
	path->nlink = st.st_nlink;
	path->uid = st.st_uid;
	path->gid = st.st_gid;
	path->atime = st.st_atime;
	path->mtime = st.st_mtime;
	path->ctime = st.st_ctime;
	path->btime = st.st_birthtime;
	path->size = st.st_size;
	path->blocks = st.st_blocks;
}

int			ft_path_readstat(t_path *path, int follow_lnk)
{
	struct stat		st;
	int				res;

	if (path->ftype == DT_LNK || path->ftype == -1)
		res = lstat(path->path, &st);
	else
		res = stat(path->path, &st);
	if (res < 0)
	{
		print_last_err(path->path);
		return (0);
	}
	path->fatime = st.st_atime;
	path->fbtime = st.st_birthtime;
	path->fctime = st.st_ctime;
	path->fmtime = st.st_mtime;
	path->fsize = st.st_size;
	if ((FT_ISLNK(st.st_mode) && follow_lnk))
		stat(path->path, &st);
	ft_path_readstat_sub(path, st);
	return (1);
}
