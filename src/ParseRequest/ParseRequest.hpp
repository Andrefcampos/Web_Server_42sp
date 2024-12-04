/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:00:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/04 18:53:33 by myokogaw         ###   ########.fr       */
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
		void	isNewSocket(int fd);
		void	setBuffer(int fd);
		int		setBody(int fd);
		int		findBody(int fd);
		int		setRequestLine(int fd);
		int		setHeaders(int fd);
		int		parseRequest(int fd);
	
	protected:
		std::map<int, ctrlFD> _socket;

	public:
		int		setBufferSocketFd(int fd);
};