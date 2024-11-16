/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:25:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 20:16:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <vector>
#include <iostream>

void	Request::setHeader(string headers){
	cout << headers << '\n';
}

void	Request::setBody(string body){
	cout << body << '\n';
}

void	setRequestLine(string requestLine){
	cout << requestLine << '\n';
}
