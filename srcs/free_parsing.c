/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:32:24 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/17 15:36:18 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	if (ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}

void	free_insert_data(t_insert_data *data, int i)
{
	(void)i;
	if (!data)
		return ;
	ft_free((void *)&data->no);
	ft_free((void *)&data->ea);
	ft_free((void *)&data->so);
	ft_free((void *)&data->door);
	ft_free((void *)&data->we);
	ft_free((void *)&data->c);
	ft_free((void *)&data->f);
	if (data->map || data->map != NULL)
		ft_free((void *)&data->map);
	ft_free((void *)&data);
}
