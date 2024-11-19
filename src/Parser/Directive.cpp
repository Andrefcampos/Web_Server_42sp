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

#include "Directive.hpp"

using namespace std;

initConf;

ServerDirective::ServerDirective() : _servers() {}
ServerDirective::~ServerDirective() {
    for (vector<Server *>::iterator it=_servers.begin(); it != _servers.end(); ++it)
        delete it;
    _servers.clear();
}

void    ServerDirective::appendServer(const Server *server) {
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
