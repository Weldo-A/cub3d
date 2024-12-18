/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:31:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/17 15:46:49 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	while_color(char *str, int *idx)
{
	int	nbr;
	int	start;

	while (str[*idx] && (str[*idx] == ' ' || str[*idx] == '\t'))
		(*idx)++;
	start = *idx;
	nbr = 0;
	while (str[*idx] && str[*idx] >= '0' && str[*idx] <= '9')
	{
		nbr = (nbr * 10) + (str[*idx] - '0');
		(*idx)++;
	}
	if (nbr > 255 || nbr < 0 || *idx == start)
		return (-1);
	while (str[*idx] && (str[*idx] == ' ' || str[*idx] == '\t'))
		(*idx)++;
	if (str[*idx] == ',')
		(*idx)++;
	return (nbr);
}

int	check_color(t_insert_data *data)
{
	int	i_c;
	int	i_f;
	int	count;

	i_c = 0;
	i_f = 0;
	count = -1;
	if (!data->c || !data->f)
		return (1);
	if (ft_isalpha(data->c[0]) || ft_isalpha(data->f[0]))
		return (1);
	while (++count <= 2)
	{
		data->ctab[count] = while_color(data->c, &i_c);
		data->ftab[count] = while_color(data->f, &i_f);
		if (data->ctab[count] == -1 || data->ftab[count] == -1)
			return (1);
	}
	if (check_remaining_chars(data->c, i_c) || check_remaining_chars(data->f,
			i_f))
		return (1);
	return (0);
}

unsigned int	str_rgb_to_hex(const char *rgb_str)
{
	char			**split;
	int				r;
	int				g;
	int				b;
	unsigned int	color;

	split = ft_split(rgb_str, ',');
	if (!split)
		return (0);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	ft_free_tab(split);
	return (color);
}
