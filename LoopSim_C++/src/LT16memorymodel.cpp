/*
 * LT16memorymodel.cpp
 *
 *  Created on: 28 Sep 2018
 *      Author: fehmel
 */

#include "LT16memorymodel.h"

namespace LT16_v0_1 {

const uint8_t LT16_memory_model::get8(const uint32_t& address) {
	return this->mem[address];
}

const uint8_t LT16_memory_model::get8(const uint32_t& address) const {
	uint8_t tmp=0;
	{
		auto it = mem.find(address);
		if(it!=mem.end()) {
			tmp = it->second;
		}
	}
	return tmp;
}

void LT16_memory_model::set8(const uint32_t& address, const uint8_t& data) {
	this->mem[address] = data;
}

const uint16_t LT16_memory_model::get16(const uint32_t& address) {
	uint16_t tmp=0;
	tmp |= this->mem[address];
	tmp <<= 8;
	tmp |= this->mem[address+1];
	return tmp;
}

const uint16_t LT16_memory_model::get16(const uint32_t& address) const {
	uint32_t tmp0=0,tmp1=0;
	{
		auto it = mem.find(address);
		if(it!=mem.end()) {
			tmp0 |= it->second<<8;
		}
	}
	{
		auto it = mem.find(address+1);
		if(it!=mem.end()) {
			tmp1 |= it->second;
		}
	}
	return tmp0 | tmp1;
}

void LT16_memory_model::set16(const uint32_t& address, const uint16_t& data) {
	this->mem[address]  = 0x00ff & (data>>8);
	this->mem[address+1]= 0x00ff & data;
}

uint32_t LT16_memory_model::get32(const uint32_t& address) {
	uint32_t tmp=0;
	tmp |= this->mem[address];
	tmp <<= 8;
	tmp |= this->mem[address+1];
	tmp <<= 8;
	tmp |= this->mem[address+2];
	tmp <<= 8;
	tmp |= this->mem[address+3];
	return tmp;
}

const uint32_t LT16_memory_model::get32(const uint32_t& address) const {
	uint32_t tmp0=0,tmp1=0,tmp2=0,tmp3=0;
	{
		auto it = mem.find(address);
		if(it!=mem.end()) {
			tmp0 |= it->second<<24;
		}
	}
	{
		auto it = mem.find(address+1);
		if(it!=mem.end()) {
			tmp1 |= it->second<<16;
		}
	}
	{
		auto it = mem.find(address+2);
		if(it!=mem.end()) {
			tmp2 |= it->second<<8;
		}
	}
	{
		auto it = mem.find(address+3);
		if(it!=mem.end()) {
			tmp3 |= it->second;
		}
	}
	return tmp0 | tmp1 | tmp2 | tmp3;
}

void LT16_memory_model::set32(const uint32_t& address, const uint32_t& data) {
	this->mem[address] = 0x000000ff & (data>>24);
	this->mem[address+1] = 0x000000ff & (data>>16);
	this->mem[address+2] = 0x000000ff & (data>>8);
	this->mem[address+3] = 0x000000ff & data;
}

} /* namespace LT16_v0_1 */
