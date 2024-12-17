/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerAdapter.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:11:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/16 00:22:35 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>
#include <map>

class Directive;
class ListenDirective;
class ServerNameDirective;
class ClientMaxBodySizeDirective;
class LocationDirective;
class ErrorPageDirective;

class ServerAdapter {
	protected:
		std::map<std::string, Directive *>	_directives;

	public:
		std::string					getHost() const;
		std::string					getIP() const;
		std::string					getPort() const;
		std::string					getServerName(void) const;
		long long int				getSizeMax(void) const;

		ListenDirective 			*getListen(void);
		ServerNameDirective			*getServerName(void);
		ClientMaxBodySizeDirective	*getClientMaxBodySize(void);
		LocationDirective			*getLocation(void);
		ErrorPageDirective			*getErrorPage(void);
};
