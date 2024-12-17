/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerAdapter.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:38:12 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/16 00:45:31 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerAdapter.hpp"
#include "Directive.hpp"
#include <iostream>

std::string	ServerAdapter::getHost() const{
	if (not _directives.count("listen"))
		return "";

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("listen");
	return dynamic_cast<ListenDirective*>(it->second)->getHost();
}

std::string	ServerAdapter::getIP() const{
	if (not _directives.count("listen"))
		return "";

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("listen");
	return dynamic_cast<ListenDirective*>(it->second)->getIP();
}

std::string	ServerAdapter::getPort() const{
	if (not _directives.count("listen"))
		return "";

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("listen");
	return dynamic_cast<ListenDirective*>(it->second)->getPort();
}

std::string	ServerAdapter::getServerName() const{
	if (not _directives.count("server_name"))
		return "";

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("server_name");
	return dynamic_cast<ServerNameDirective*>(it->second)->getServerName();
}

long long int	ServerAdapter::getSizeMax() const{
	if (not _directives.count("client_max_body_size"))
		return 0;

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("client_max_body_size");
	return dynamic_cast<ClientMaxBodySizeDirective*>(it->second)->getSizeMax();
}

ListenDirective 			*ServerAdapter::getListen(void) {
	return (dynamic_cast<ListenDirective *>(_directives["listen"]));
}

ServerNameDirective			*ServerAdapter::getServerName(void) {
	return (dynamic_cast<ServerNameDirective *>(_directives["server_name"]));
}

ClientMaxBodySizeDirective	*ServerAdapter::getClientMaxBodySize(void) {
	return (dynamic_cast<ClientMaxBodySizeDirective *>(_directives["client_max_body_size"]));
}

LocationDirective			*ServerAdapter::getLocation(void) {
	return (dynamic_cast<LocationDirective *>(_directives["location"]));
}

ErrorPageDirective			*ServerAdapter::getErrorPage(void) {
	return (dynamic_cast<ErrorPageDirective *>(_directives["error_page"]));
}
