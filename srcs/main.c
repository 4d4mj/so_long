/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:35:35 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/14 16:35:35 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_filename_valid(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strnstr(filename + (len - 4), ".ber", 4) != NULL);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		message(NULL, "Invalid number of parameters.\n");
	if (!is_filename_valid(argv[1]))
		message(NULL, "Filename must end in \".ber\".\n");
	srand(time(NULL));
	init(argv[1]);
}
