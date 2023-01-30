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

	if (init(argc, argv, &scene))
		return (ERROR);
	printf("%sSUCCESS!%s\n", BOLD_GREEN, RESET_COLOR);
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
