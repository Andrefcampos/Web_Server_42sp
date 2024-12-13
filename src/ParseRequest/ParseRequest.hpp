/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:00:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/12 16:18:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include <map>
#include "defines.hpp"

class Client;

struct ctrlFD{
	Request		*request;
	bool		parsedBody;
	int			lentgh;
	std::string	buffer;
};

class ParseRequest{
	private:
		void	isNewClient(int fd);
		void	setBuffer(int fd);
		int		setRequestLine(int fd);
		int		setHeaders(int fd);
		int		parseRequest(int fd, Client *client);

	
	protected:
		std::map<int, ctrlFD> _socket;

	public:
		Request *setBufferSocketFd(Client *client);
		void	removeFD(int fd);
};