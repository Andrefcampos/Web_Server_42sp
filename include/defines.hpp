/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:20:47 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/10 16:21:46 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# define MAX_EVENTS 10
# define SIZE 10024
# define BUFFER_SIZE 4096
# define MAIN_CONF		0x02000000
# define SRV_CONF		0x04000000
# define LOC_CONF 		0x08000000
# define CONF_BLOCK		0x00000100
# define CONF_NOARGS	0x00000001
# define CONF_TAKE1		0x00000002
# define CONF_TAKE2		0x00000004
# define CONF_TAKE3		0x00000008
# define CONF_TAKE4		0x00000010
# define CONF_TAKE5		0x00000020
# define CONF_TAKE6		0x00000040
# define CONF_TAKE7		0x00000080
# define CONF_1MORE		0x00000800
# define CONF_2MORE		0x00001000
# define CONF_OK 1
# define CONF_BLOCK_START 2
# define CONF_BLOCK_DONE 3
# define CONF_FILE_DONE 4

enum e_exit {
	SUCCESS,
	FAIL
};
