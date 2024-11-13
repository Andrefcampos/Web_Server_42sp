/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:32:48 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/13 17:32:01 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Directive.hpp"
#include "Server.hpp"

using namespace std;

ServerDirective::ServerDirective() : _servers() {
	_servers["localhost:8080"]= new Server(8080, 5, "localhost:8080", "127.0.0.1");
	_servers["localhost:8080"]->setPathIndex("index/index.html");
	_servers["localhost:8080"]->setPathImage("image/images.png");
	_servers["localhost:8081"] = new Server(8081, 5, "localhost:8081", "127.0.0.2");
	_servers["localhost:8081"]->setPathIndex("index/index2.html");
	_servers["localhost:8081"]->setPathImage("image/img.png");
}

ServerDirective::~ServerDirective() {
    for (map<std::string, Server *>::iterator it=_servers.begin(); it != _servers.end(); ++it)
        delete it->second;
    _servers.clear();
}

const Server *ServerDirective::getServer(const string &host) {
	return (_servers[host]);
}

// void    ServerDirective::appendServer(const Server *server) {
//     _servers.push_back(server);
// }

// Server  *ServerDirective::back(void) {
//     return(_servers.back());
// }

// ListenDirective::ListenDirective(const std::string &value) {
//     _value = value;
// }

// ListenDirective::~ListenDirective() {}