/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:09:53 by andrefil          #+#    #+#             */
/*   Updated: 2024/11/26 11:00:07 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"


Cgi::Cgi(void) {}

Cgi::Cgi(Cgi const &obj) {
	*this = obj;
}

// Cgi	&Cgi::operator=(Cgi const &obj) {
// 	if (this == &obj) {
// 		_path = obj._path;
// 		_extensions = obj._extensions;
// 	}
// 	return (*this);
// }

Cgi::~Cgi(void) {}

Cgi::Cgi(std::string const &ScriptPath, std::map<std::string, std::string> const &Envp, std::string const &Body) : \
	_scriptpath(ScriptPath), _envp(Envp), _request(Body) {}

std::string Cgi::executeCgi(void) {

	//config Envp:
	
}
