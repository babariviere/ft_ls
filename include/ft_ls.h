/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:34 by briviere          #+#    #+#             */
/*   Updated: 2017/12/06 16:39:27 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include "libft.h"
# include <pwd.h>
# include <stdio.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <uuid/uuid.h>

# define FT_ISIFO(mode) ((mode & S_IFIFO) == S_IFIFO)
# define FT_ISCHR(mode) ((mode & S_IFCHR) == S_IFCHR)
# define FT_ISDIR(mode) ((mode & S_IFDIR) == S_IFDIR)
# define FT_ISBLK(mode) ((mode & S_IFBLK) == S_IFBLK)
# define FT_ISREG(mode) ((mode & S_IFREG) == S_IFREG)
# define FT_ISLNK(mode) ((mode & S_IFLNK) == S_IFLNK)
# define FT_ISSOCK(mode) ((mode & S_IFSOCK) == S_IFSOCK)
# define FT_ISWHT(mode) ((mode & S_IFWHT) == S_IFWHT)
# define FT_ISUID(mode) ((mode & S_IFUID) == S_IFUID)
# define FT_ISGID(mode) ((mode & S_IFGID) == S_IFGID)
# define FT_ISVTX(mode) ((mode & S_IFVTX) == S_IFVTX)
# define FT_IRWXU(mode) ((mode & S_IRWXU) == S_IRWXU)
# define FT_IRUSR(mode) ((mode & S_IRUSR) == S_IRUSR)
# define FT_IWUSR(mode) ((mode & S_IWUSR) == S_IWUSR)
# define FT_IXUSR(mode) ((mode & S_IXUSR) == S_IXUSR)
# define FT_IRWXG(mode) ((mode & S_IRWXG) == S_IRWXG)
# define FT_IRGRP(mode) ((mode & S_IRGRP) == S_IRGRP)
# define FT_IWGRP(mode) ((mode & S_IWGRP) == S_IWGRP)
# define FT_IXGRP(mode) ((mode & S_IXGRP) == S_IXGRP)
# define FT_IRWXO(mode) ((mode & S_IRWXO) == S_IRWXO)
# define FT_IROTH(mode) ((mode & S_IROTH) == S_IROTH)
# define FT_IWOTH(mode) ((mode & S_IWOTH) == S_IWOTH)
# define FT_IXOTH(mode) ((mode & S_IXOTH) == S_IXOTH)

# define HAS_FLAG(a, flag) ((a & flag) == flag)

typedef enum	e_arg {
	ARG_LIST_FMT	=	(1 <<  1),
	ARG_REC			=	(1 <<  2),
	ARG_HIDDEN		=	(1 <<  3),
	ARG_SORT		=	(1 <<  4),
	ARG_SORT_SIZE	=	(1 <<  5),
	ARG_SORT_TIME	=	(1 <<  6),
	ARG_REV			=	(1 <<  7),
	ARG_ONE_ENT		=	(1 <<  8),
	ARG_HUMAN		=	(1 <<  9),
	ARG_FOLLOW_LNK	=	(1 << 10),
	ARG_MTIME		=	(1 << 11),
	ARG_CTIME		=	(1 << 12),
	ARG_ATIME		=	(1 << 13),
	ARG_BTIME		=	(1 << 14)
}				t_arg;

typedef struct	s_path {
	char			*path;
	char			*name;
	struct stat		*stat;
	struct stat		*fstat;
}				t_path;

int			parse_arg(t_arg *opt, const char *arg);
int			usage(int code);
void		print_error(int err, const char *path);

char		*get_permissions(const int mode);
char		*get_pw_name(uid_t uid);
char		*get_gr_name(uid_t uid);
char		*get_file_time(long time);
char		*get_xattr_symbol(const char *path, int follow_lnk);

int			count_files(const char *path, int hidden);

t_path		*ft_init_path(const char *d_path, const char *name,
		int follow_lnk);
t_path		**ft_get_subpath(const char *path, int follow_lnk, int hidden);
void		ft_free_path(t_path **path);
void		ft_swap_if_not_gr(t_path **path1, t_path **path2, t_arg opt,
		int rev);
void		ft_make_sort_paths(t_path **paths, t_arg opt);
void		ft_sort_subpath(t_path **path, int (*cmp)
		(const char *, const char *));
void		ft_sort_subpath_size(t_path **path, int rev);
void		ft_sort_subpath_atime(t_path **path, int rev);
void		ft_sort_subpath_mtime(t_path **path, int rev);
void		ft_sort_subpath_ctime(t_path **path, int rev);
void		ft_sort_subpath_btime(t_path **path, int rev);

void		list_files(t_path **path, t_arg arg);

void		print_list_format(t_path **path, t_arg arg);
void		print_total_blocks(t_path **path, size_t total_blk,
		size_t tab_len);

#endif
