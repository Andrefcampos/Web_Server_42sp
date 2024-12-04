/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:37:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/04 18:57:07 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Socket.hpp"
# include "Response.hpp"
# include "Directive.hpp"
# include <string>
# include <map>

class Location;
class Request;

class Server : public Socket, public Response {
	private:
		int									_socketFd;
		std::map<std::string, Directive *>	_directives;

	public:
		Server();
		virtual ~Server();

		Directive	*getDirective(const std::string &directive);
		int			getSocketFd(void) const;
		void		setSocketFd(const int socketFd);
		void		sendResponse(int fd, Request *request);

		friend class ServerNameHandler;
		friend class ClientMaxBodySizeHandler;
		friend class LocationHandler;
		friend class ListenHandler;
		friend class ErrorPageHandler;
};
