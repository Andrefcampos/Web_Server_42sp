/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:38:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/03 17:35:16 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conf.hpp"
#include "Logger.hpp"
#include "Server.hpp"

using namespace std;

// Server::~Server(){};

// Server::Server(int port, int events, string hostName, string ip)
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

// string Server::getHostName() const{
// 	return _hostName;
// }

// int			Server::getMaxEvent() const{
// 	return _maxEvents;
// }

Server::Server() {
	this->_directives["listen"] = new ListenDirective();
	this->_directives["location"] = new LocationDirective();
	this->_directives["client_max_body_size"] = new ClientMaxBodySizeDirective();
	this->_directives["error_page"] = new ErrorPageDirective();
}

Server::~Server() {
	for (map<string, Directive *>::iterator it = _directives.begin(); it != _directives.end(); ++it)
		delete it->second;
	_directives.clear();
}

Directive	*Server::getDirective(const std::string &directive) {
	return (_directives[directive]);
}

// void    Server::setDirective(Conf &cf) {
// 	const string	directive = *cf.args.begin();
//     Directive *directive_obj = _directives[directive];
// 	if (not directive_obj) {
// 		if (directive.compare("listen") != 0) {
// 			_directives[directive] = new ListenDirective();
// 			return ;
// 		}
// 		else if (directive.compare("server_name") != 0) {
// 			_directives[directive] = new ServerNameDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("client_max_body_size") != 0) {
// 			_directives[directive] = new ClientMaxBodySizeDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("error_page") != 0) {
// 			_directives[directive] = new ErrorPageDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("location") != 0)
// 			_directives[directive] = new LocationDirective();
// 	}
// 	if (directive.compare("listen") != 0 || directive.compare("server_name") != 0
// 	|| directive.compare("client_max_body_size") != 0 || directive.compare("error_page") != 0)
// 		throw (runtime_error(Logger::log_error(cf, "duplicated directive %s not allowed", directive.c_str())));
// 	(static_cast<LocationDirective *>(directive_obj))->setDirective(cf);
// }