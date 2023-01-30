/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 11:01:30 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/29 11:01:32 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#ifndef UNIT

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	sleep(10);
	if (init(argc, argv, &scene))
	{
		ft_alloc(0, 0, NULL, FLUSH);
		sleep(20);
		return (ERROR);
	}
	printf("%sSUCCESS!%s\n", BOLD_GREEN, RESET_COLOR);
	ft_alloc(0, 0, NULL, FLUSH);
	sleep(10);
	return (SUCCESS);
}
#endif

#ifdef UNIT

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	printf("miniRT\n");
	return (0);
}
#endif
