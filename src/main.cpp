/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/13 16:01:01 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include "WebServer.hpp"
#include <map>

int main(){
	std::map<std::string, Server> Services;
	Server	web1(8080, 5, "localhost:8080", "127.0.0.1");
	web1.setPathIndex("index/index.html");
	web1.setPathImage("image/images.png");
	Server	web2(8081, 5, "localhost:8081", "127.0.0.2");
	web2.setPathIndex("index/index2.html");
	web2.setPathImage("image/img.png");
	Services["127.0.0.1:8080"] = web1;
	Services["127.0.0.2:8081"] = web2;

	
	WebService Web(Services);
	Web.loopingEvent();
}