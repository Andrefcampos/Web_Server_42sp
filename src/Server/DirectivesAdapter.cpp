/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectivesAdapter.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:38:12 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 16:57:36 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DirectiveAdapter.hpp"
#include "Directive.hpp"
#include <iostream>

std::string	DirectiveAdapter::getHost() const{
	if (not _directives.count("listen"))
		return "";

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("listen");
	return dynamic_cast<ListenDirective*>(it->second)->getHost();
}

std::string	DirectiveAdapter::getIP() const{
	if (not _directives.count("listen"))
		return "";

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("listen");
	return dynamic_cast<ListenDirective*>(it->second)->getIP();
}

std::string	DirectiveAdapter::getPort() const{
	if (not _directives.count("listen"))
		return "";

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("listen");
	return dynamic_cast<ListenDirective*>(it->second)->getPort();
}

std::string	DirectiveAdapter::getServerName() const{
	if (not _directives.count("server_name"))
		return "";

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("server_name");
	return dynamic_cast<ServerNameDirective*>(it->second)->getServerName();
}

long long int	DirectiveAdapter::getSizeMax() const{
	if (not _directives.count("client_max_body_size"))
		return 0;

	std::map<std::string, Directive *>::const_iterator it;
	it = _directives.find("client_max_body_size");
	return dynamic_cast<ClientMaxBodySizeDirective*>(it->second)->getSizeMax();
}

