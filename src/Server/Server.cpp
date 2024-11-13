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

Server::Server() : _directives() {
	// _directives["listen"] = new ListenDirective();
	// _directives["server_name"] = new ServerNameDirective();
	// _directives["client_max_body_size"] = new ClientMaxBodySizeDirective();
    // _directives["location"] = new LocationDirective();
	// _directives["allow_methods"] = new AllowMethodsDirective();
    // _directives["redirect"] = new RedirectDirective();
	// _directives["root"] = new RootDirective();
    // _directives["autoindex"] = new AutoIndexDirective();
	// _directives["index"] = new IndexDirective();
    // _directives["cgi"] = new CgiDirective();
	// _directives["upload_dir"] = new UploadDirDirective();
    // _directives["error_page"] = new ListenDirective();
};

Server::~Server() {};

void    Server::setDirective(const std::string &directive, const std::string &value) {
    _directives[directive] = DirectiveLocation;
}