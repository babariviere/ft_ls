/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:41:22 by briviere          #+#    #+#             */
/*   Updated: 2017/11/28 10:49:39 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_arg_opt	*arg_opt;
	int			idx;

	if ((arg_opt = ft_memalloc(sizeof(t_arg_opt))) == 0)
		return (1);
	arg_opt->one_entry = 1;
	idx = 1;
	while (idx < ac)
	{
		if (av[idx][0] == '-' && av[idx][1] != 0)
		{
			if (parse_arg(arg_opt, av[idx++]) == 0)
				return (usage(1));
		}
		else
			break ;
	}
	list_dirs_av(av + idx, arg_opt);
	//free(arg_opt);
	return (0);
}
