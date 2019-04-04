/*!
 * \file LT16memorymodel.h
 *
 * \date 2018-09-28
 * \author fehmel
 */

#ifndef LT16MEMORYMODEL_H_
#define LT16MEMORYMODEL_H_

#include <map>

#include "memport.h"

namespace LT16_v0_1 {

class LT16_memory_model {
	std::map<uint32_t,uint8_t> mem;
public:
	LT16_memory_model() {};
	LT16_memory_model(const LT16_memory_model&) = default;
	LT16_memory_model(LT16_memory_model&&) = default;
	LT16_memory_model& operator=(const LT16_memory_model&) = default;
	LT16_memory_model& operator=(LT16_memory_model&&) = default;
	virtual ~LT16_memory_model() {};

	virtual const uint8_t get8(const uint32_t& address);
	virtual const uint8_t get8(const uint32_t& address) const;
	virtual void set8(const uint32_t& address, const uint8_t& data);

	virtual const uint16_t get16(const uint32_t& address);
	virtual const uint16_t get16(const uint32_t& address) const;
	virtual void set16(const uint32_t& address, const uint16_t& data);

	virtual uint32_t get32(const uint32_t& address);
	virtual const uint32_t get32(const uint32_t& address) const;
	virtual void set32(const uint32_t& address, const uint32_t& data);

	const decltype(mem)& get_mem() const {return mem;}

	bool operator==(const LT16_memory_model& rhs) const {return mem == rhs.get_mem();}
};

} /* namespace LT16_v0_1 */

#endif /* LT16MEMORYMODEL_H_ */
