/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/10/31 15:50:51 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include "WebServer.hpp"
#include <map>

int main(){
	std::map<std::string, Server> Services; 
	Server	web1(8080, 5, "PombosHear", "127.0.0.1");
	Server	web2(8081, 5, "Livros sem nada", "127.0.0.1");
	Services["Service one"] = web1;
	Services["Service two"] = web2;
	WebService Web(Services); 
	Web.loopingEvent();
}