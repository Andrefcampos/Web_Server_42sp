/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:56:03 by myokogaw          #+#    #+#             */
/*   Updated: 2024/10/16 16:03:22 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/epoll.h>

# define MAX_EVENTS 50

class	EventManager {
	public:
		void	addEpollFd();
		void	modEpollFd();
		void	delEpollFd();
		void	setNonBlockingFd();
		void	InitLoopEvent();
	private:
		struct epoll_event _events[MAX_EVENTS], _efd;
};
