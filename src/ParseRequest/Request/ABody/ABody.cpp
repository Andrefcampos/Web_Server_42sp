/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABody.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:13:34 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/18 10:19:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABody.hpp"

list<DataBody>	ABody::getDataBody(){
	return _data;
}

void	ABody::setDataBody(DataBody &data){
	_data.push_back(data);
}

void	ABody::setLengthBody(size_t length){
	_lengthBody = length;
}
size_t	ABody::getLengthBody(){
	return _lengthBody;	
}