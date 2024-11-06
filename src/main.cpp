/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 16:28:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include "WebServer.hpp"
#include <map>

int main(){
	std::map<std::string, Server> Services; 
	Server	web1(8080, 5, "localhost:8080", "0.0.0.0");
	web1.setPathIndex("index/index.html");
	web1.setPathImage("image/images.png");
	Server	web2(8081, 5, "localhost:8081", "0.0.0.0");
	web2.setPathIndex("index/index2.html");
	web2.setPathImage("image/img.png");
	Services["localhost:8080"] = web1;
	Services["localhost:8081"] = web2;
	WebService Web(Services); 
	Web.loopingEvent();
}