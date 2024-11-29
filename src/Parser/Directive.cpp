/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:32:48 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/12 18:32:48 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Logger.hpp"
#include "Directive.hpp"
#include "Server.hpp"

using namespace std;

ServerDirective::ServerDirective() : _servers() {}

ServerDirective::~ServerDirective() {
	for (vector<Server *>::iterator it=_servers.begin(); it != _servers.end(); ++it)
		delete *it;
	_servers.clear();
}

void    ServerDirective::appendServer(Server *server) {
	_servers.push_back(server);
}

Server  *ServerDirective::back(void) const {
	return(_servers.back());
}

ListenDirective::ListenDirective() : _default_conf(true), _host("0.0.0.0"), _port("8080"), _ip(0), _port_value(htons(8080)) {}

ListenDirective::~ListenDirective() {}

void	ListenDirective::setDefaultConfBool(bool state) {
	this->_default_conf = state;
}

void	ListenDirective::setHost(const std::string &host) {
	this->_host = host;
}

void	ListenDirective::setPort(const std::string &port) {
	this->_port = port;
}

void	ListenDirective::setPortValue(in_port_t port_value) {
	this->_port_value = port_value;
}

bool	ListenDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

ServerNameDirective::ServerNameDirective() {}

ServerNameDirective::~ServerNameDirective() {}

void	ServerNameDirective::setServerName(const std::string &server_name) {
	this->_server_name = server_name;
}

const std::string &ServerNameDirective::getServerName(void) const {
	return (this->_server_name);
}

ClientMaxBodySizeDirective::ClientMaxBodySizeDirective() : _default_conf(true), _size_max(1 * (1 << 20)) {}

ClientMaxBodySizeDirective::~ClientMaxBodySizeDirective() {}

void	ClientMaxBodySizeDirective::setSizeMax(const long long int size_max) {
	this->_size_max = size_max;
}

long long int ClientMaxBodySizeDirective::getSizeMax(void) const {
	return (this->_size_max);
}

void	ClientMaxBodySizeDirective::setDefaultConfBool(const bool state) {
	this->_default_conf = state;
}

bool	ClientMaxBodySizeDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

LocationDirective::LocationDirective() : _locations() {}

LocationDirective::~LocationDirective() {
	for (std::vector<Location *>::iterator it = _locations.begin(); it != _locations.end(); ++it)
		delete *it;
	_locations.clear();
}

void    LocationDirective::appendLocation(Location *location) {
	_locations.push_back(location);
}

Location  *LocationDirective::back(void) const {
	return(_locations.back());
}

// void	LocationDirective::setRoute(const std::string &route) {
// 	this->_route = route;
// }

// void	LocationDirective::setDirective(Conf &cf) {
// 	const std::string	directive = *cf.args.begin();
//     Directive *directive_obj = _directives[directive];
// 	if (not directive_obj) {
// 		if (directive.compare("allow_methods") != 0) {
// 			_directives[directive] = new AllowMethodsDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("redirect") != 0) {
// 			_directives[directive] = new RedirectDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("root") != 0) {
// 			_directives[directive] = new RootDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("autoindex") != 0) {
// 			_directives[directive] = new AutoIndexDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("index") != 0) {
// 			_directives[directive] = new IndexDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("cgi") != 0) {
// 			_directives[directive] = new CgiDirective(cf.args.back());
// 			return ;
// 		}
// 		else if (directive.compare("upload_dir") != 0) {
// 			_directives[directive] = new UploadDirDirective(cf.args.back());
// 			return ;
// 		}
// 	}
// 	if (directive.compare("allow_methods") != 0 || directive.compare("redirect") != 0
// 	|| directive.compare("root") != 0 || directive.compare("autoindex") != 0
// 	|| directive.compare("index") != 0 || directive.compare("cgi") != 0
// 	|| directive.compare("upload_dir") != 0)
// 		throw (std::runtime_error(Logger::log_error(cf, "duplicated directive %s not allowed", directive.c_str())));
// }

AllowMethodsDirective::AllowMethodsDirective() : _default_conf(true), _GET(true), _POST(false), _DELETE(false) {}

AllowMethodsDirective::~AllowMethodsDirective() {}

void	AllowMethodsDirective::setDefaultConfBool(const bool state) {
	this->_default_conf = state;
}

void	AllowMethodsDirective::setGetBool(const bool state) {
	this->_GET = state;
}

void	AllowMethodsDirective::setPostBool(const bool state) {
	this->_POST = state;
}

void	AllowMethodsDirective::setDeleteBool(const bool state) {
	this->_DELETE = state;
}

bool	AllowMethodsDirective::getDefaultConfBool(void) const {
	return (this->_default_conf);
}

bool	AllowMethodsDirective::getGetBool(void) const {
	return (this->_GET);
}

bool	AllowMethodsDirective::getPostBool(void) const {
	return (this->_POST);
}

bool	AllowMethodsDirective::getDeleteBool(void) const {
	return (this->_DELETE);
}


bool AllowMethodsDirective::isAllowed(const std::string &method) const {
	if (method.compare("GET") == 0 && _GET == true)
		return (true);
	else if (method.compare("POST") == 0 && _POST == true)
		return (true);
	else if (method.compare("DELETE") == 0 && _DELETE == true)
		return (true);
	return (false);
}

RedirectDirective::RedirectDirective() {}

RedirectDirective::~RedirectDirective() {}

RootDirective::RootDirective() {}

RootDirective::~RootDirective() {}

AutoIndexDirective::AutoIndexDirective() {}

AutoIndexDirective::~AutoIndexDirective() {}

IndexDirective::IndexDirective() {}

IndexDirective::~IndexDirective() {}

CgiDirective::CgiDirective() {}

CgiDirective::~CgiDirective() {}

UploadDirDirective::UploadDirDirective() {}

UploadDirDirective::~UploadDirDirective() {}

ErrorPageDirective::ErrorPageDirective() {}

ErrorPageDirective::~ErrorPageDirective() {}
