////////////////////////////////////////////////////
//Processor: LT16
//Version:   0.1
////////////////////////////////////////////////////

#ifndef LT16_V0_1_HPP
#define LT16_V0_1_HPP

#include <systemc.h>
#include <string>

#include "LT16memorymodel.h"

namespace LT16_v0_1
{
	enum reg
	{
		Active,
		PC,
		BDS,
		REGFILE0,
		REGFILE1,
		REGFILE2,
		REGFILE3,
		REGFILE4,
		REGFILE5,
		REGFILE6,
		REGFILE7,
		REGFILE8,
		REGFILE9,
		REGFILE10,
		REGFILE11,
		REGFILE12,
		REGFILE13,
		REGFILE14,
		REGFILE15
	};

	class architecture_state
	{
		public:
			// Constructor
			explicit architecture_state():
				Active(1),
				BDS(0),
				PC(9223372036854775807),
				REGFILE({9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807, 9223372036854775807})
			{
			}
			architecture_state(const architecture_state&) =default;

			// Destructor
			~architecture_state()
			{
			}

			bool operator!=(const architecture_state& rhs) const
			{
				return (!(*this == rhs));
			}

			bool operator==(const architecture_state& rhs) const
			{
				bool result(true);
				result &= (Active == rhs.Active);
				result &= (PC == rhs.PC);
				result &= (BDS == rhs.BDS);
				result &= (REGFILE[0] == rhs.REGFILE[0]);
				result &= (REGFILE[1] == rhs.REGFILE[1]);
				result &= (REGFILE[2] == rhs.REGFILE[2]);
				result &= (REGFILE[3] == rhs.REGFILE[3]);
				result &= (REGFILE[4] == rhs.REGFILE[4]);
				result &= (REGFILE[5] == rhs.REGFILE[5]);
				result &= (REGFILE[6] == rhs.REGFILE[6]);
				result &= (REGFILE[7] == rhs.REGFILE[7]);
				result &= (REGFILE[8] == rhs.REGFILE[8]);
				result &= (REGFILE[9] == rhs.REGFILE[9]);
				result &= (REGFILE[10] == rhs.REGFILE[10]);
				result &= (REGFILE[11] == rhs.REGFILE[11]);
				result &= (REGFILE[12] == rhs.REGFILE[12]);
				result &= (REGFILE[13] == rhs.REGFILE[13]);
				result &= (REGFILE[14] == rhs.REGFILE[14]);
				result &= (REGFILE[15] == rhs.REGFILE[15]);
				return result;
			}

			bool operator<(const architecture_state& rhs) const
			{
				if(Active != rhs.Active)
					return (Active < rhs.Active);
				if(PC != rhs.PC)
					return (PC < rhs.PC);
				if(BDS != rhs.BDS)
					return (BDS < rhs.BDS);
				if(REGFILE[0] != rhs.REGFILE[0])
					return (REGFILE[0] < rhs.REGFILE[0]);
				if(REGFILE[1] != rhs.REGFILE[1])
					return (REGFILE[1] < rhs.REGFILE[1]);
				if(REGFILE[2] != rhs.REGFILE[2])
					return (REGFILE[2] < rhs.REGFILE[2]);
				if(REGFILE[3] != rhs.REGFILE[3])
					return (REGFILE[3] < rhs.REGFILE[3]);
				if(REGFILE[4] != rhs.REGFILE[4])
					return (REGFILE[4] < rhs.REGFILE[4]);
				if(REGFILE[5] != rhs.REGFILE[5])
					return (REGFILE[5] < rhs.REGFILE[5]);
				if(REGFILE[6] != rhs.REGFILE[6])
					return (REGFILE[6] < rhs.REGFILE[6]);
				if(REGFILE[7] != rhs.REGFILE[7])
					return (REGFILE[7] < rhs.REGFILE[7]);
				if(REGFILE[8] != rhs.REGFILE[8])
					return (REGFILE[8] < rhs.REGFILE[8]);
				if(REGFILE[9] != rhs.REGFILE[9])
					return (REGFILE[9] < rhs.REGFILE[9]);
				if(REGFILE[10] != rhs.REGFILE[10])
					return (REGFILE[10] < rhs.REGFILE[10]);
				if(REGFILE[11] != rhs.REGFILE[11])
					return (REGFILE[11] < rhs.REGFILE[11]);
				if(REGFILE[12] != rhs.REGFILE[12])
					return (REGFILE[12] < rhs.REGFILE[12]);
				if(REGFILE[13] != rhs.REGFILE[13])
					return (REGFILE[13] < rhs.REGFILE[13]);
				if(REGFILE[14] != rhs.REGFILE[14])
					return (REGFILE[14] < rhs.REGFILE[14]);
				if(REGFILE[15] != rhs.REGFILE[15])
					return (REGFILE[15] < rhs.REGFILE[15]);
				return false;
			}

			// Registers
			sc_uint<1> Active;
			sc_uint<32> PC;
			sc_int<32> REGFILE[16];
			sc_uint<1> BDS;

	};

	class AccessProxy8 : public data_access_model::Model<32,8>{
		LT16_memory_model* mem;
	public:
		explicit AccessProxy8(LT16_memory_model* mem) : mem(mem) {}
		virtual void put(const sc_uint<32>& address, const sc_uint<8>& data) {mem->set8(address,data);}
		virtual const sc_uint<8> get(const sc_uint<32>& address) const {return mem->get8(address);}
	};
	class AccessProxy16 : public data_access_model::Model<32,16>{
		LT16_memory_model* mem;
	public:
		explicit AccessProxy16(LT16_memory_model* mem) : mem(mem) {}
		virtual void put(const sc_uint<32>& address, const sc_uint<16>& data) {mem->set16(address,data);}
		virtual const sc_uint<16> get(const sc_uint<32>& address) const {return mem->get16(address);}
	};
	class AccessProxy32 : public data_access_model::Model<32,32>{
		LT16_memory_model* mem;
	public:
		explicit AccessProxy32(LT16_memory_model* mem) : mem(mem) {}
		virtual void put(const sc_uint<32>& address, const sc_uint<32>& data) {mem->set32(address,data);}
		virtual const sc_uint<32> get(const sc_uint<32>& address) const {return mem->get32(address);}

	};

	class Port8
	{
		public:
			// Constructor
			explicit Port8(data_access_model::Model<32,8>* mem):
				Active(0),
				Address(0),
				DATA(mem,Address,Active)
			{
			}

			// Destructor
			~Port8() =default;

			bool operator==(const Port8& rhs) const
			{
				bool result(true);
				result &= (Active == rhs.Active);
				result &= (Address == rhs.Address);
				result &= (DATA == rhs.DATA);
				return result;
			}

			// Registers
			sc_uint<1> Active;
			sc_uint<32> Address;
			data_access_model::access_wActive<8,32> DATA;
	};

	class Port16
	{
		public:
			// Constructor
			explicit Port16(data_access_model::Model<32,16>* mem):
				Active(0),
				Address(0),
				DATA(mem,Address,Active)
			{
			}

			// Destructor
			~Port16() =default;

			bool operator==(const Port16& rhs) const
			{
				bool result(true);
				result &= (Active == rhs.Active);
				result &= (Address == rhs.Address);
				result &= (DATA == rhs.DATA);
				return result;
			}

			// Registers
			sc_uint<1> Active;
			sc_uint<32> Address;
			data_access_model::access_wActive<16,32> DATA;
	};

	class Port32
	{
		public:
			// Constructor
			explicit Port32(data_access_model::Model<32,32>* mem):
				Active(0),
				Address(0),
				DATA(mem,Address,Active)
			{
			}

			// Destructor
			~Port32() =default;

			bool operator==(const Port32& rhs) const
			{
				bool result(true);
				result &= (Active == rhs.Active);
				result &= (Address == rhs.Address);
				result &= (DATA == rhs.DATA);
				return result;
			}

			// Registers
			sc_uint<1> Active;
			sc_uint<32> Address;
			data_access_model::access_wActive<32,32> DATA;
	};

	class processor_state
	{
		public:
			// Constructor
			explicit processor_state():
				arch_state()
			{}

			// Destructor
			~processor_state()
			{
			}

			bool operator!=(const processor_state& rhs) const
			{
				return (!(*this == rhs));
			}

			bool operator==(const processor_state& rhs) const
			{
				bool result(true);
				result &= (arch_state == rhs.arch_state);
				result &= (mem == rhs.mem);
				return result;
			}

			//Arch state
			architecture_state arch_state;

			LT16_memory_model mem;
	};

	class processor
	{
		protected:
		AccessProxy8 proxy8;	//! proxy element for Memory Accesses to the given memory Model
		AccessProxy16 proxy16;	//! proxy element for Memory Accesses to the given memory Model
		AccessProxy32 proxy32;	//! proxy element for Memory Accesses to the given memory Model
		public:
			// Constructor
			explicit processor(LT16_memory_model* mem) :
				proxy8(mem),
				proxy16(mem),
				proxy32(mem),
				architecture("LT16"),
				branch(""),
				S(),
				Z(),
				port8(&proxy8),
				port16(&proxy16),
				port32(&proxy32)
			{}
			explicit processor(processor_state& state) :
				proxy8(&state.mem),
				proxy16(&state.mem),
				proxy32(&state.mem),
				architecture("LT16"),
				branch(""),
				S(state.arch_state),
				Z(),
				port8(&proxy8),
				port16(&proxy16),
				port32(&proxy32)
			{}

			// Destructor
			~processor() = default;

			// Instruction cells
			void ADD(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr);
			void ADDI(sc_int<8> Imm, sc_uint<4> Rd, sc_uint<32> currAddr);
			void SUB(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr);
			void BIMM(sc_uint<1> conditional, sc_int<8> Imm, sc_uint<32> currAddr);
			void BREG(sc_uint<1> conditional, sc_uint<4> Ra, sc_uint<32> currAddr);
			void LDR(sc_uint<4> Rd, sc_int<8> Imm, sc_uint<32> currAddr);
			void LD08(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr);
			void LD16(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr);
			void LD32(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr);
			void ST32(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr);
			void ST16(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr);
			void ST08(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr);
			void AND(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr);
			void OR(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr);
			void XOR(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr);
			void CMP(sc_uint<4> mode, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr);
			void CIMM(sc_uint<1> conditional, sc_int<8> Imm, sc_uint<32> currAddr);
			void TST(sc_uint<4> Ra, sc_uint<4> Rd, sc_uint<32> currAddr);
			void RETI(sc_uint<32> currAddr);

			// Added by Luis J.
			void LSH(sc_uint<4> Rd, sc_uint<4> Ra, sc_int<4> Imm, sc_uint<32> currAddr);
			void RSH(sc_uint<4> Rd, sc_uint<4> Ra, sc_int<4> Imm, sc_uint<32> currAddr);
			void CREG(sc_uint<1> conditional, sc_uint<4> Ra, sc_uint<32> currAddr);
			void TRAP(sc_int<8> Imm, sc_uint<32> currAddr);
			void BRT(sc_uint<1> conditional, sc_uint<4> Ra, sc_uint<32> currAddr);

			// Variables
			std::string architecture;
			std::string branch;

			// States
			architecture_state S;
			architecture_state Z;

			// Ports
			Port8 port8;
			Port16 port16;
			Port32 port32;
	};
}
#endif
