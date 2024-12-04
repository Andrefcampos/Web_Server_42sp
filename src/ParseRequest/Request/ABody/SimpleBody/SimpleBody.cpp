/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleBody.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:50:12 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/19 11:33:02 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleBody.hpp"
#include "utils.hpp"
#include <iostream>

void	SimpleBody::parseBody(string &buffer){
	DataBody	data;

	data.setContentApend(buffer, getLengthBody());
	setDataBody(data);
}