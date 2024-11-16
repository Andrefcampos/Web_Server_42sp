/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:13:34 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 18:27:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Body.hpp"

void			Body::addNewElement(string key, string value){
	_body[key].push_back(value);
}

list<string>	Body::getHeader(string key){
	return _body[key];
}
