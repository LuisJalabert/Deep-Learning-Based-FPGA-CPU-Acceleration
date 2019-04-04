////////////////////////////////////////////////////
//Processor: LT16
//Version:   0.1
////////////////////////////////////////////////////

#include "./instruction_cells.hpp"

void LT16_v0_1::processor::ADD(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	sc_int<32> result;
	Z = S;
	result = S.REGFILE[Ra] + S.REGFILE[Rb];
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = result;
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = result.range(7,4);
	}
	Z.REGFILE[14].bit(0) = (result.bit(31) ^ S.REGFILE[Ra].bit(31)) & (result.bit(31) ^ S.REGFILE[Rb].bit(31));
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::ADDI(sc_int<8> Imm, sc_uint<4> Rd, sc_uint<32> currAddr)
{
	sc_int<32> result;
	Z = S;
	result = S.REGFILE[Rd] + sc_int<32>(Imm);
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = result;
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = result.range(7,4);
	}
	Z.REGFILE[14].bit(0) = (result.bit(31) ^ S.REGFILE[Rd].bit(31)) & (result.bit(31) ^ Imm.bit(7));
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::SUB(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	sc_int<32> result;
	Z = S;
	result = S.REGFILE[Ra] - S.REGFILE[Rb];
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = result;
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = result.range(7,4);
	}
	Z.REGFILE[14].bit(0) = (S.REGFILE[Ra].bit(31) ^ result.bit(31)) & (S.REGFILE[Ra].bit(31) ^ S.REGFILE[Rb].bit(31));
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::BIMM(sc_uint<1> conditional, sc_int<8> Imm, sc_uint<32> currAddr)
{
	Z = S;
	if(conditional)
	{
		if(S.REGFILE[14].bit(1) == sc_uint<1>(1))
		{
			Z.PC = currAddr + (sc_int<32>(Imm) << sc_int<2>(1));
			Z.REGFILE[15] = currAddr+2;
		}
		else
		{
			Z.PC = currAddr+2;
			Z.REGFILE[15] = currAddr + sc_uint<2>(2);
		}
	}
	else
	{
		Z.PC = currAddr + (sc_int<32>(Imm) << sc_int<2>(1));
		Z.REGFILE[15] = currAddr+2;
	}
}

void LT16_v0_1::processor::BREG(sc_uint<1> conditional, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	Z = S;
	if(conditional)
	{
		if(S.REGFILE[14].bit(1) == sc_uint<1>(1))
		{
			Z.PC.range(31,1) = S.REGFILE[Ra].range(31,1);
			Z.PC.bit(0) = sc_uint<1>(0);
			Z.REGFILE[15] = currAddr+2;
		}
		else
		{
			Z.PC = currAddr+2;
			Z.REGFILE[15] = currAddr + sc_uint<2>(2);
		}
	}
	else
	{
		Z.PC.range(31,1) = S.REGFILE[Ra].range(31,1);
		Z.PC.bit(0) = sc_uint<1>(0);
		Z.REGFILE[15] = currAddr+2;
	}
}

void LT16_v0_1::processor::LDR(sc_uint<4> Rd, sc_int<8> Imm, sc_uint<32> currAddr)
{
	Z = S;
	port32.Address = S.REGFILE[15] + (sc_int<32>(Imm) << sc_int<2>(1));
	port32.Active = S.Active;
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = sc_uint<32>(port32.DATA);
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = sc_uint<32>(port32.DATA).range(7,4);
	}
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::LD08(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr)
{
	Z = S;
	port8.Address = S.REGFILE[Rb];
	port8.Active = S.Active;
	if(Ra < sc_uint<4>(14))
	{
		Z.REGFILE[Ra].range(31,8) = sc_uint<1>(0);
		Z.REGFILE[Ra].range(7,0) = sc_uint<8>(port8.DATA);
	}
	if(Ra == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = sc_uint<32>(port8.DATA).range(7,4);
	}
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::LD16(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr)
{
	Z = S;
	port16.Address.range(31,1) = S.REGFILE[Rb].range(31,1);
	port16.Address.bit(0) = sc_uint<1>(0);
	port16.Active = S.Active;
	if(Ra < sc_uint<4>(14))
	{
		Z.REGFILE[Ra].range(31,16) = sc_uint<1>(0);
		Z.REGFILE[Ra].range(15,0) = sc_uint<16>(port16.DATA);
	}
	if(Ra == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = sc_uint<32>(port16.DATA).range(7,4);
	}
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::LD32(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr)
{
	Z = S;
	port32.Address.range(31,2) = S.REGFILE[Rb].range(31,2);
	port32.Address.range(1,0) = sc_uint<1>(0);
	port32.Active = S.Active;
	if(Ra < sc_uint<4>(14))
	{
		Z.REGFILE[Ra] = sc_uint<32>(port32.DATA);
	}
	if(Ra == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = sc_uint<32>(port32.DATA).range(7,4);
	}
	Z.PC = currAddr + 2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::ST32(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr)
{
	Z = S;
	port32.Active = S.Active;
	port32.Address.range(31,2) = S.REGFILE[Ra].range(31,2);
	port32.Address.range(1,0) = sc_uint<1>(0);
	port32.DATA = S.REGFILE[Rb];
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::ST16(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr)
{
	Z = S;
	port16.Active = S.Active;
	port16.Address.range(31,1) = S.REGFILE[Ra].range(31,1);
	port16.Address.bit(0) = sc_uint<1>(0);
	port16.DATA = sc_uint<16>(S.REGFILE[Rb].range(15,0));
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::ST08(sc_uint<4> Ra, sc_uint<4> Rb, sc_uint<32> currAddr)
{
	Z = S;
	port8.Address = S.REGFILE[Ra];
	port8.Active = S.Active;
	port8.DATA = S.REGFILE[Rb].range(7,0);
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::AND(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	sc_int<32> result;
	Z = S;
	result = S.REGFILE[Ra] & S.REGFILE[Rb];
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = result;
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = result.range(7,4);
	}
	Z.PC = currAddr + sc_uint<2>(2);
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::OR(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	sc_int<32> result;
	Z = S;
	result = S.REGFILE[Ra] | S.REGFILE[Rb];
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = result;
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = result.range(7,4);
	}
	Z.PC = currAddr + sc_uint<2>(2);
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::XOR(sc_uint<4> Rd, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	sc_int<32> result;
	Z = S;
	result = S.REGFILE[Ra] ^ S.REGFILE[Rb];
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = result;
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = result.range(7,4);
	}
	Z.PC = currAddr + sc_uint<2>(2);
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::CMP(sc_uint<4> mode, sc_uint<4> Rb, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	Z = S;
	if(mode == 0b0000)
	{
		Z.REGFILE[14].bit(1) = S.REGFILE[Ra] == S.REGFILE[Rb];
	}
	if(mode == 0b1000)
	{
		Z.REGFILE[14].bit(1) = !(S.REGFILE[Ra] == S.REGFILE[Rb]);
	}
	if(mode == 0b0010)
	{
		Z.REGFILE[14].bit(1) = S.REGFILE[Ra] > S.REGFILE[Rb];
	}
	if(mode == 0b0001)
	{
		Z.REGFILE[14].bit(1) = (S.REGFILE[Ra] > S.REGFILE[Rb]) | (S.REGFILE[Ra] == S.REGFILE[Rb]);
	}
	if(mode == 0b1001)
	{
		Z.REGFILE[14].bit(1) = (S.REGFILE[Ra] < S.REGFILE[Rb]);
	}
	if(mode == 0b1010)
	{
		Z.REGFILE[14].bit(1) = (S.REGFILE[Ra] < S.REGFILE[Rb]) | (S.REGFILE[Ra] == S.REGFILE[Rb]);
	}

	Z.PC = currAddr + sc_uint<2>(2);
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::CIMM(sc_uint<1> conditional, sc_int<8> Imm, sc_uint<32> currAddr)
{
	Z = S;
	if(conditional)
	{
		if(S.REGFILE[14].bit(1) == sc_uint<1>(1))
		{
			Z.REGFILE[13] = currAddr + sc_uint<2>(2);
			Z.PC = currAddr + (sc_int<32>(Imm) << sc_int<2>(1));
			Z.REGFILE[15] = currAddr+2;
		}
		else
		{
			Z.PC = currAddr + sc_uint<2>(2);
			Z.REGFILE[15] = currAddr + sc_uint<2>(2);
		}
	}
	else
	{
		Z.REGFILE[13] = currAddr + sc_uint<2>(2);
		Z.PC = currAddr + (sc_int<32>(Imm) << sc_int<2>(1));
		Z.REGFILE[15] = currAddr+2;
	}
}

void LT16_v0_1::processor::TST(sc_uint<4> Ra, sc_uint<4> Rd, sc_uint<32> currAddr)
{
	sc_uint<8> result;
	Z = S;
	port8.Address = S.REGFILE[Ra];
	port8.Active = S.Active;
	result = port8.DATA;
	if((result & sc_uint<8>(128)) == sc_uint<8>(0))
	{
		Z.REGFILE[14].bit(0) = sc_uint<1>(1);
	}
	else
	{
		Z.REGFILE[14].bit(0) = sc_uint<1>(0);
	}
	result = result | sc_uint<8>(128);
	port8.DATA = result;
	Z.PC = currAddr + sc_uint<2>(2);
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::RETI(sc_uint<32> currAddr)
{
	Z = S;
	port32.Address = S.REGFILE[12];
	port32.Active = S.Active;
	Z.PC = sc_uint<32>(port32.DATA);

	port32.Address = S.REGFILE[12] + sc_int<32>(4);
	port32.Active = S.Active;
	Z.REGFILE[14] = sc_uint<32>(port32.DATA);

	Z.REGFILE[15] = currAddr + sc_uint<2>(2);

	Z.REGFILE[12] = S.REGFILE[12] + sc_int<32>(8);
}




/////////////// added by Luis J. /////////////////////

void LT16_v0_1::processor::LSH(sc_uint<4> Rd, sc_uint<4> Ra, sc_int<4> Imm, sc_uint<32> currAddr)
{
	sc_int<32> result;
	Z = S;
	result = sc_uint<32>(S.REGFILE[Ra]) << (sc_uint<4>(Imm)+1);
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = result;
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = result.range(7,4);
	}
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::RSH(sc_uint<4> Rd, sc_uint<4> Ra, sc_int<4> Imm, sc_uint<32> currAddr)
{
	sc_int<32> result;
	Z = S;
	result = sc_uint<32>(S.REGFILE[Ra]) >> (sc_uint<4>(Imm)+1);
	if(Rd < sc_uint<4>(14))
	{
		Z.REGFILE[Rd] = result;
	}
	if(Rd == sc_uint<4>(14))
	{
		Z.REGFILE[14].range(7,4) = result.range(7,4);
	}
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::CREG(sc_uint<1> conditional, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	Z = S;
	if(conditional)
	{
		if(S.REGFILE[14].bit(1) == sc_uint<1>(1))
		{
			Z.REGFILE[13] = currAddr + sc_uint<2>(2);
			Z.PC = Z.REGFILE[Ra];
			Z.REGFILE[15] = currAddr+2;
		}
		else
		{
			Z.PC = currAddr + sc_uint<2>(2);
			Z.REGFILE[15] = currAddr + sc_uint<2>(2);
		}
	}
	else
	{
		Z.REGFILE[13] = currAddr + sc_uint<2>(2);
		Z.PC = Z.REGFILE[Ra];
		Z.REGFILE[15] = currAddr+2;
	}
}

void LT16_v0_1::processor::TRAP(sc_int<8> Imm, sc_uint<32> currAddr){
	//nichting implementiertings
	Z.PC = currAddr+2;
	Z.REGFILE[15] = currAddr + sc_uint<2>(2);
}

void LT16_v0_1::processor::BRT(sc_uint<1> conditional, sc_uint<4> Ra, sc_uint<32> currAddr)
{
	Z = S;
	if(conditional)
	{
		if(S.REGFILE[14].bit(1) == sc_uint<1>(1))
		{
			// this  is according to documentation, but should it be PC = PC + Ra&&FFFE??? idk yo
			Z.PC = Z.PC + (S.REGFILE[Ra] << sc_uint<1>(1));
			//Z.PC.range(31,1) = Z.PC.range(31,1) + S.REGFILE[Ra].range(31,1);
			//Z.PC.bit(0) = sc_uint<1>(0);
			Z.REGFILE[15] = currAddr+2;
		}
		else
		{
			Z.PC = currAddr+2;
			Z.REGFILE[15] = currAddr + sc_uint<2>(2);
		}
	}
	else
	{
		// this  is according to documentation, but should it be PC = PC + Ra&&FFFE??? idk yo
		Z.PC = Z.PC + (S.REGFILE[Ra] << sc_uint<1>(1));
		Z.REGFILE[15] = currAddr+2;
	}
}
