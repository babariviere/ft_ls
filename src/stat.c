/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 19:16:25 by briviere          #+#    #+#             */
/*   Updated: 2017/12/06 11:53:48 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_pw_name(uid_t uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(uid);
	if (pwd)
		return (ft_strdup(pwd->pw_name));
	else
		return (ft_itoa(uid));
}

char	*get_gr_name(uid_t uid)
{
	struct group	*grp;

	grp = getgrgid(uid);
	if (grp)
		return (ft_strdup(grp->gr_name));
	else
		return (ft_itoa(uid));
}

char	*get_file_time(long tm)
{
	time_t		nw;
	time_t		ftime;
	char		**splitted;
	char		*time_str;
	char		*tmp;

	ftime = tm;
	nw = time(0);
	splitted = ft_strsplit(ctime(&ftime), ' ');
	free(splitted[0]);
	if (splitted[2][1] != 0)
		time_str = ft_strjoin_sep(splitted[1], " ", splitted[2]);
	else
		time_str = ft_strjoin_sep(splitted[1], "  ", splitted[2]);
	free(splitted[1]);
	free(splitted[2]);
	if (ftime > nw || ftime < (nw - 16070400))
	{
		tmp = time_str;
		time_str = ft_strjoin_sep(tmp, "  ", splitted[4]);
		free(tmp);
		tmp = time_str;
		time_str = ft_strtrim(tmp);
		free(tmp);
	}
	else
	{
		tmp = time_str;
		time_str = ft_strnew(ft_strlen(tmp) + 6);
		ft_strcpy(time_str, tmp);
		ft_strcat(time_str, " ");
		ft_strncat(time_str, splitted[3], 5);
		free(tmp);
	}
	free(splitted[3]);
	free(splitted[4]);
	free(splitted);
	if (time_str == 0)
		return (0);
	return (time_str);
}
