/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:38:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/12 20:14:10 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// Server::~Server(){};

// Server::Server(int port, int events, std::string hostName, std::string ip)
// :Socket(), _port(port), _maxEvents(events), _ip(ip){
// 	if (hostName.empty())
// 		_hostName = "";
// 	else
// 		_hostName = hostName;
// 	initTCP(_socketFd, _port, _maxEvents, _ip.c_str());
// };

// int		Server::getSocketFd() const{
// 	return _socketFd;
// }

// std::string Server::getHostName() const{
// 	return _hostName;
// }

// int			Server::getMaxEvent() const{
// 	return _maxEvents;
// }

Server::Server() : _directives() {};

Server::~Server() {};

void    Server::setDirective(const std::string &directive, const std::string &value) {
    Directive *directive_obj = _directives[directive];
	if (not directive_obj) {
		if (directive.compare("listen") != 0) {
			_directives[directive] = new ListenDirective(value);
			return ;
		}
		else if (directive.compare("server_name") != 0) {
			_directives[directive] = new ServerNameDirective(value);
			return ;
		}
		else if (directive.compare("client_max_body_size") != 0) {
			_directives[directive] = new ClientMaxBodySizeDirective(value);
			return ;
		}
		else if (directive.compare("error_page") != 0) {
			_directives = new ErrorPageDirective(value);
			return ;
		}
		else if (directive.compare("location") != 0)
			_directives[directive] = new LocationDirective();
	}
	if (directive.compare("listen") != 0 || directive.compare("server_name") != 0
	|| directive.compare("client_max_body_size") != 0 || directive.compare("error_page") != 0)
		throw (std::runtime_error(Logger::log_error("duplicated directive %s not allowed", directive.c_str())));
	directive_obj->setDirective(directive, value);
}