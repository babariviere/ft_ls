/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:39:22 by briviere          #+#    #+#             */
/*   Updated: 2017/11/23 17:09:09 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		init_formatted(t_formatted **formatted, size_t len)
{
	if ((*formatted = ft_memalloc(sizeof(t_formatted))) == 0)
		return (0);
	(*formatted)->len = len;
	if (((*formatted)->tab =
			ft_memalloc(sizeof(char *) * (*formatted)->len)) == 0)
		return (0);
	if (((*formatted)->padding =
			ft_memalloc(sizeof(int) * (*formatted)->len)) == 0)
		return (0);
	(*formatted)->padding[(*formatted)->len - 1] = 0;
	(*formatted)->idx = 0;
	return (1);
}

void	add_formatted_str(t_formatted *formatted, char *str, int next_padding)
{
	formatted->tab[formatted->idx] = str;
	formatted->padding[formatted->idx] = next_padding;
	formatted->idx++;
}

void	print_formatted(t_formatted *formatted)
{
	size_t	idx;

	idx = 0;
	while (idx < formatted->len)
	{
		ft_putstr(formatted->tab[idx]);
		if (idx < formatted->len - 1)
			ft_putchar_mul(' ', formatted->padding[idx]);
		idx++;
	}
}

void	calibrate_formatted(t_formatted **formatteds, size_t tab_idx, size_t diff_idx)
{
	size_t	formatted_idx;
	size_t	longest;
	size_t	curr_len;

	formatted_idx = 0;
	longest = 0;
	while (formatteds[formatted_idx])
	{
		curr_len = ft_strlen(formatteds[formatted_idx]->tab[tab_idx]);
		if (curr_len > longest)
			longest = curr_len;
		formatted_idx++;
	}
	formatted_idx = 0;
	while (formatteds[formatted_idx])
	{
		formatteds[formatted_idx]->padding[tab_idx + diff_idx] +=
			longest - ft_strlen(formatteds[formatted_idx]->tab[tab_idx]);
		formatted_idx++;
	}
}
