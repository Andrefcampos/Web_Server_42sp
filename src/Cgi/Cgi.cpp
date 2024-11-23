/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:09:53 by andrefil          #+#    #+#             */
/*   Updated: 2024/11/23 17:18:51 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"


Cgi::Cgi(void) {}

Cgi::Cgi(Cgi const &obj) {
	*this = obj;
}

Cgi	&Cgi::operator=(Cgi const &obj) {
	if (this == &obj) {
		_path = obj._path;
		_extensions = obj._extensions;
	}
	return (*this);
}

Cgi::~Cgi(void) {}

Cgi::Cgi(std::string const &Path, std::map<std::string, std::string> const &Extensions) : _path(Path), _extensions(Extensions){

}
