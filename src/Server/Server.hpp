/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:37:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 23:56:17 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "ServerAdapter.hpp"
# include "Socket.hpp"
# include "Response.hpp"
# include <string>
# include <map>

class Request;
class Directive;

class Server : public Socket, public ServerAdapter {
	private:
		std::map<int, Request *>			fdClient;
		int									_socketFd;

	public:
		Server();
		virtual ~Server();

		const Directive	*getDirective(const std::string &directive);
		int				getSocketFd(void) const;
		void			setSocketFd(const int socketFd);
		void			sendResponse(int fd, Request *request);
		void			setDirective(Directive *directive);
		void			print(void) const;
};
