/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:49:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 13:46:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Body.hpp"

void	Body::setBody(std::string body){
	_body = body;
}

std::string		Body::getBody() const{
	return _body;	
}

std::ostream &operator<<(std::ostream &os, const Body &body){
	os << body.getBody();
	return os;
}