/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_orient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:36:27 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/18 11:11:56 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_insert_c(char *line, t_insert_data *data)
{
	char	*end;
	int		i;

	i = 0;
	if (!line || !data || data->c != NULL)
	{
		data->check = 9999;
		return ;
	}
	end = ft_copy_end(line, 'C');
	if (!(end))
		return ;
	i = dell_space(end, &i);
	if (!end[i])
	{
		free(end);
		return ;
	}
	data->c = ft_strdup_new_line(&end[i]);
	free(end);
	if (!data->c)
		return ;
	data->check++;
}

void	ft_insert_no(char *line, t_insert_data *data)
{
	char	*end;
	int		i;

	i = 0;
	if (!line || !data || data->no != NULL)
	{
		data->check = 9999;
		return ;
	}
	end = ft_copy_end(line, 'O');
	if (!(end))
		return ;
	i = dell_space(end, &i);
	if (!end[i])
	{
		free(end);
		return ;
	}
	data->no = ft_strdup_new_line(&end[i]);
	free(end);
	if (!data->no)
		return ;
	data->check++;
}

void	ft_insert_ea(char *line, t_insert_data *data)
{
	char	*end;
	int		i;

	i = 0;
	if (!line || !data || data->ea != NULL)
	{
		data->check = 9999;
		return ;
	}
	end = ft_copy_end(line, 'A');
	if (!(end))
		return ;
	i = dell_space(end, &i);
	if (!end[i])
	{
		free(end);
		return ;
	}
	data->ea = ft_strdup_new_line(&end[i]);
	free(end);
	if (!data->ea)
		return ;
	data->check++;
}

void	ft_insert_so(char *line, t_insert_data *data)
{
	char	*end;
	int		i;

	i = 0;
	if (!line || !data || data->so != NULL)
	{
		data->check = 9999;
		return ;
	}
	end = ft_copy_end(line, 'O');
	if (!(end))
		return ;
	i = dell_space(end, &i);
	if (!end[i])
	{
		free(end);
		return ;
	}
	data->so = ft_strdup_new_line(&end[i]);
	free(end);
	if (!data->so)
		return ;
	data->check++;
}

void	ft_insert_we(char *line, t_insert_data *data)
{
	char	*end;
	int		i;

	i = 0;
	if (!line || !data || data->we != NULL)
	{
		data->check = 9999;
		return ;
	}
	end = ft_copy_end(line, 'E');
	if (!(end))
		return ;
	i = dell_space(end, &i);
	if (!end[i])
	{
		free(end);
		return ;
	}
	data->we = ft_strdup_new_line(&end[i]);
	free(end);
	if (!data->we)
		return ;
	data->check++;
}
