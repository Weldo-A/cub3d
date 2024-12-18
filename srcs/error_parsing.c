/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:34:12 by aduriez           #+#    #+#             */
/*   Updated: 2024/12/18 11:50:08 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	handle_errors(int error_code, t_insert_data *data)
{
	free_insert_data(data, error_code);
	if (error_code == 1)
		ft_putstr_fd("1Error\nNot correct arguments\n", 2);
	else if (error_code == 2)
		ft_putstr_fd("2Error\nFile not valid\n", 2);
	else if (error_code == 3)
		ft_putstr_fd("3Error\nCalculate size file failed\n", 2);
	else if (error_code == 4)
		ft_putstr_fd("4Error\nMap not valid\n", 2);
	else if (error_code == 5)
		ft_putstr_fd("5Error\nColors not valid\n", 2);
	else if (error_code == 6)
		ft_putstr_fd("6Error\nTexture not valid\n", 2);
	else if (error_code == 7)
		ft_putstr_fd("7Error\nNot good organisation\n", 2);
	else if (error_code == 8)
		ft_putstr_fd("8Error\nTextures Not good\n", 2);
	return (1);
}

int	handle_error(char *msg, int *visited)
{
	static int	*last_freed;

	(void)msg;
	last_freed = NULL;
	if (visited != NULL && visited != last_freed)
	{
		free(visited);
		last_freed = visited;
	}
	return (0);
}
