/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:00:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/08 16:08:58 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include <map>
#include "defines.hpp"

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
		int		setBody(int fd);
		int		setRequestLine(int fd);
		int		setHeaders(int fd);
		int		parseRequest(int fd);
	
	protected:
		std::map<int, ctrlFD> _socket;

	public:
		Request *setBufferSocketFd(int fd);
};