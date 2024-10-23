/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/23 17:58:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"

int main(){

	Server	web1(8080, 5, "Um nome", "127.0.0.1");
	Server	web2(8081, 5, "Dois nome", "127.0.0.1");

	std::cout << web.getHostName() << " " << web.getSocketFd() << "\n";
	std::cout << "WebService\n";
}