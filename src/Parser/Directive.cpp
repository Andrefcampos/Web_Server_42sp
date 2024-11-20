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

Server  *ServerDirective::back(void) {
	return(_servers.back());
}

ListenDirective::ListenDirective(const std::string &value) : _value(value) {}

ListenDirective::~ListenDirective() {}

ServerNameDirective::ServerNameDirective(const std::string &value) : _value(value) {}

ServerNameDirective::~ServerNameDirective() {}

ClientMaxBodySizeDirective::ClientMaxBodySizeDirective(const std::string &value) : _value(value) {}

ClientMaxBodySizeDirective::~ClientMaxBodySizeDirective() {}

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
