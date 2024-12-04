/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:38:16 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/14 12:01:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

#define REQUESTLINE	"requestLine"
#define HEADERS 	"Headers"

typedef std::map<int, std::map<std::string, std::map<std::string, std::string> > > httpRequest;
typedef std::map<std::string, std::string> mapHeader;