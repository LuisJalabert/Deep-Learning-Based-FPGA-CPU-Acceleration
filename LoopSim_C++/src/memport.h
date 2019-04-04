/*!
 * @file memport_test.h
 *
 * This file contains the idea for a memory model access structure.
 * Memory accesses are modeled as "ports"
 *
 * Ports model the instructions access via one of its Memory/IO interfaces to a specific address;
 * A port in our instruction cell methodology currently contains 3 elements:
 *	- Active	: a one-bit flag that determines if the port is active
 *	- Address	: a signal determining which address the port is Reading/Writing
 *	- DATA		: the data that can be read/written at the target Address
 *
 * The direction of these sub-signals depends wheter the instructions reads or writes with the given port.
 * When modeled in a Hardware decription language, Instruction cells are components,
 * and ports are a collection of, well, ports.
 * Active and Address are always "out" from the instruction cell, DATA may be "in" XOR "out".
 *
 * Modeled in C/C++/SystemC, an instruction cell is a function.
 * Calling that function represents "executing" it.
 * Ports can be modeled as function arguments, either as pointers, pass-by-value or references.
 *
 * The problem with Ports is:
 * reading/writing DATA is dependent in the current value of Address (and Active).
 *
 * To resolve this, the DATA element could be designed as one of data types contained in this file:
 * data_access_model::access and data_access_model::access_wActive
 * Accessing them with either
 * - assignment operator
 * - sc_uint() cast operator (can happen implicitly (?) )
 *
 *
 * data_access_model::Model is the Memory model used for this port.
 * The constructor of a port data type should properly initialize its DATA member with
 * references to its Active and Address members, as well as a pointer to the used memory model,
 * e.g. by accessing a singleton.
 *
 * Example
 *
 * \w [ static data_access_model::Model* MemoryModel::getDataAccessModel(); ] somewhere...
 *
 * struct Port_t {
 * 		sc_uint<1> Active;
 * 		sc_uint<32> Address;
 * 		data_access_model::access_wActive<32,32> DATA;
 * 		Port_t() : Active(0), Address(0), DATA(MemoryModel::getDataAccessModel(),Address,Active) {}
 * }
 *
 *
 * @date 2018-09-27
 * @author fehmel
 */

#ifndef MEMPORT_H_
#define MEMPORT_H_

#include <systemc>

namespace data_access_model {

	using sc_dt::sc_int;
	using sc_dt::sc_uint;

	/*!
	 * The Model its the underlying Memory Model used by the Port
	 * This could also use a template for its implementation, but that would be rather complicated...
	 */
	template<unsigned address_bitwidth, unsigned data_bitwidth>
	class Model {
	public:
		virtual ~Model() {}

		virtual void put(const sc_uint<address_bitwidth>& address, const sc_uint<data_bitwidth>&) =0;

		virtual const sc_uint<data_bitwidth> get(const sc_uint<address_bitwidth>& address) const =0;
	};

	template<unsigned data_bitwidth, unsigned address_bitwidth>
	class access {
		Model<address_bitwidth,data_bitwidth>* dm;
		const sc_uint<address_bitwidth>& address;
	public:
		access(Model<address_bitwidth,data_bitwidth>* dm,const sc_uint<address_bitwidth>& address) : dm(dm), address(address) {}

		access& operator=(const sc_uint<data_bitwidth>& t) {
			dm->put(address,t);
			return *this;
		}
		access& operator=(const sc_int<data_bitwidth>& t) {
			dm->put(address,sc_uint<data_bitwidth>(t));
			return *this;
		}
		access& operator=(const sc_dt::sc_int_subref& rhs) {
			dm->put(address,sc_uint<data_bitwidth>(rhs));
			return *this;
		}

		operator sc_uint<data_bitwidth>() const {
			return dm->get(address);
		}
		operator sc_int<data_bitwidth>() const {
			return dm->get(address);
		}

		sc_uint<data_bitwidth> operator+(
			const sc_uint<data_bitwidth>& rhs
		) {
			return static_cast< sc_uint<data_bitwidth> >(*this) + rhs;
		}

		bool operator==(const access<data_bitwidth,address_bitwidth>& rhs) const {
			return sc_uint<data_bitwidth>(*this) == sc_uint<data_bitwidth>(rhs);
		}
	};

	template<unsigned data_bitwidth, unsigned address_bitwidth>
	class access_wActive {
		Model<address_bitwidth,data_bitwidth>* dm;
		const sc_uint<address_bitwidth>& address;
		const sc_uint<1>& active;
	public:
		access_wActive(Model<address_bitwidth,data_bitwidth>* dm,const sc_uint<address_bitwidth>& address,const sc_uint<1>& active) : dm(dm), address(address), active(active) {}

		bool is_active() {return active==sc_uint<1>(1);}

		access_wActive& operator=(const sc_uint<data_bitwidth>& t) {
			if(is_active())
				dm->put(address,t);
			return *this;
		}
		access_wActive& operator=(const sc_int<data_bitwidth>& t) {
			if(is_active())
				dm->put(address,sc_uint<data_bitwidth>(t));
			return *this;
		}
		access_wActive& operator=(const sc_dt::sc_int_subref& rhs) {
			if(is_active())
				dm->put(address,sc_uint<data_bitwidth>(rhs));
			return *this;
		}

		operator sc_uint<data_bitwidth>() const {
			return dm->get(address);
		}

		sc_uint<data_bitwidth> operator+(
			const sc_uint<data_bitwidth>& rhs
		) {
			return static_cast< sc_uint<data_bitwidth> >(*this) + rhs;
		}

		bool operator==(const access_wActive<data_bitwidth,address_bitwidth>& rhs) const {
			return sc_uint<data_bitwidth>(*this) == sc_uint<data_bitwidth>(rhs);
		}


	};

};

template<unsigned data_bitwidth, unsigned address_bitwidth>
sc_dt::sc_uint<data_bitwidth> operator+(
	const sc_dt::sc_uint<data_bitwidth>& lhs,
	const data_access_model::access<data_bitwidth,address_bitwidth>& rhs
) {
	return lhs + rhs.resolve();
}

template<unsigned data_bitwidth, unsigned address_bitwidth>
sc_dt::sc_uint<data_bitwidth> operator+(
	const sc_dt::sc_uint<data_bitwidth>& lhs,
	const data_access_model::access_wActive<data_bitwidth,address_bitwidth>& rhs
) {
	return lhs + rhs.resolve();
}

#endif /* MEMPORT_H_ */
