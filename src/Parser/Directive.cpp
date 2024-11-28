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

ListenDirective::ListenDirective() : _host("0.0.0.0"), _port("8080"), _ip(0), _port_value(8080) {}

ListenDirective::~ListenDirective() {}

ServerNameDirective::ServerNameDirective() {}

ServerNameDirective::~ServerNameDirective() {}

void	ServerNameDirective::setServerName(const std::string &server_name) {
	this->_server_name = server_name;
}

const std::string &ServerNameDirective::getServerName(void) const {
	return (this->_server_name);
}

ClientMaxBodySizeDirective::ClientMaxBodySizeDirective() : _size_max(1 * (1 << 20)) {}

ClientMaxBodySizeDirective::~ClientMaxBodySizeDirective() {}

void	ClientMaxBodySizeDirective::setSizeMax(const long long int size_max) {
	this->_size_max = size_max;
}

long long int ClientMaxBodySizeDirective::getSizeMax(void) const {
	return (this->_size_max);
}

LocationDirective::LocationDirective() {}

LocationDirective::~LocationDirective() {}

void	LocationDirective::setDirective(Conf &cf) {
	const std::string	directive = *cf.args.begin();
    Directive *directive_obj = _directives[directive];
	if (not directive_obj) {
		if (directive.compare("allow_methods") != 0) {
			_directives[directive] = new AllowMethodsDirective(cf.args.back());
			return ;
		}
		else if (directive.compare("redirect") != 0) {
			_directives[directive] = new RedirectDirective(cf.args.back());
			return ;
		}
		else if (directive.compare("root") != 0) {
			_directives[directive] = new RootDirective(cf.args.back());
			return ;
		}
		else if (directive.compare("autoindex") != 0) {
			_directives[directive] = new AutoIndexDirective(cf.args.back());
			return ;
		}
		else if (directive.compare("index") != 0) {
			_directives[directive] = new IndexDirective(cf.args.back());
			return ;
		}
		else if (directive.compare("cgi") != 0) {
			_directives[directive] = new CgiDirective(cf.args.back());
			return ;
		}
		else if (directive.compare("upload_dir") != 0) {
			_directives[directive] = new UploadDirDirective(cf.args.back());
			return ;
		}
	}
	if (directive.compare("allow_methods") != 0 || directive.compare("redirect") != 0
	|| directive.compare("root") != 0 || directive.compare("autoindex") != 0
	|| directive.compare("index") != 0 || directive.compare("cgi") != 0
	|| directive.compare("upload_dir") != 0)
		throw (std::runtime_error(Logger::log_error(cf, "duplicated directive %s not allowed", directive.c_str())));
}

AllowMethodsDirective::AllowMethodsDirective(const std::string &value) : _value(value) {}

AllowMethodsDirective::~AllowMethodsDirective() {}

RedirectDirective::RedirectDirective(const std::string &value) : _value(value) {}

RedirectDirective::~RedirectDirective() {}

RootDirective::RootDirective(const std::string &value) : _value(value) {}

RootDirective::~RootDirective() {}

AutoIndexDirective::AutoIndexDirective(const std::string &value) : _value(value) {}

AutoIndexDirective::~AutoIndexDirective() {}

IndexDirective::IndexDirective(const std::string &value) : _value(value) {}

IndexDirective::~IndexDirective() {}

CgiDirective::CgiDirective(const std::string &value) : _value(value) {}

CgiDirective::~CgiDirective() {}

UploadDirDirective::UploadDirDirective(const std::string &value) : _value(value) {}

UploadDirDirective::~UploadDirDirective() {}

ErrorPageDirective::ErrorPageDirective(const std::string &value) : _value(value) {}

ErrorPageDirective::~ErrorPageDirective() {}
