/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:12:43 by myokogaw          #+#    #+#             */
/*   Updated: 2024/10/16 18:08:25 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <vector>
# include <string>
# include <netinet/in.h>

class Location;
class ErrorPage;

class Server {
	public:
		Server(void);
		~Server(void);
		Server(int const &port);
		void	bindSocket(void);
		void	setOptSocket(void);
		void	listenSocket(void);
		int		getSocketFd(void) const;
		int		initServer(void);
		void	setPort(int const &Port);
		void	addErrorPage(const ErrorPage &ErrorPage);
		void	addLocations(const Location &Locations);
		void	addDirectives(const std::string &Key, const std::string &Value);
		
	private:
		std::map<std::string, std::string> _directives;
		std::map<std::string, Location> _locations;
		std::vector<ErrorPage> _errorPages;
		struct sockaddr_in	_peer_addr;
		int _port, _socketFd, _ip;
};