/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calion <calion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:19:54 by calion            #+#    #+#             */
/*   Updated: 2022/09/26 18:23:28 by calion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void read_map(t_map call_map)
{
    int fd;
    fd = open(call_map.map_path,O_RDONLY);
}