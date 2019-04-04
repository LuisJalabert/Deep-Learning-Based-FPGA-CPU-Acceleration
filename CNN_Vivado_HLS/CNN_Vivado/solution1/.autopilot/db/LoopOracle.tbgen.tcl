set moduleName LoopOracle
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {LoopOracle}
set C_modelType { void 0 }
set C_modelArgList {
	{ DataInTr float 32 regular {array 19456 { 1 3 } 1 1 }  }
	{ CnnOut int 32 regular {array 2 { 0 0 } 0 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "DataInTr", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "DataInTr","cData": "float","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1},{"low" : 0,"up" : 75,"step" : 1},{"low" : 0,"up" : 255,"step" : 1}]}]}]} , 
 	{ "Name" : "CnnOut", "interface" : "memory", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "CnnOut","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 1,"step" : 1}]}]}]} ]}
# RTL Port declarations: 
set portNum 17
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ DataInTr_address0 sc_out sc_lv 15 signal 0 } 
	{ DataInTr_ce0 sc_out sc_logic 1 signal 0 } 
	{ DataInTr_q0 sc_in sc_lv 32 signal 0 } 
	{ CnnOut_address0 sc_out sc_lv 1 signal 1 } 
	{ CnnOut_ce0 sc_out sc_logic 1 signal 1 } 
	{ CnnOut_we0 sc_out sc_logic 1 signal 1 } 
	{ CnnOut_d0 sc_out sc_lv 32 signal 1 } 
	{ CnnOut_address1 sc_out sc_lv 1 signal 1 } 
	{ CnnOut_ce1 sc_out sc_logic 1 signal 1 } 
	{ CnnOut_we1 sc_out sc_logic 1 signal 1 } 
	{ CnnOut_d1 sc_out sc_lv 32 signal 1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "DataInTr_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "DataInTr", "role": "address0" }} , 
 	{ "name": "DataInTr_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "DataInTr", "role": "ce0" }} , 
 	{ "name": "DataInTr_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "DataInTr", "role": "q0" }} , 
 	{ "name": "CnnOut_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "CnnOut", "role": "address0" }} , 
 	{ "name": "CnnOut_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CnnOut", "role": "ce0" }} , 
 	{ "name": "CnnOut_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CnnOut", "role": "we0" }} , 
 	{ "name": "CnnOut_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "CnnOut", "role": "d0" }} , 
 	{ "name": "CnnOut_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "CnnOut", "role": "address1" }} , 
 	{ "name": "CnnOut_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CnnOut", "role": "ce1" }} , 
 	{ "name": "CnnOut_we1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CnnOut", "role": "we1" }} , 
 	{ "name": "CnnOut_d1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "CnnOut", "role": "d1" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"],
		"CDFG" : "LoopOracle",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "4086734", "EstimateLatencyMax" : "4086734",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "DataInTr", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "CnnOut", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "C1W1_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "C2W2", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "C3B4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "C3W3", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "FCW5", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.C1W1_0_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.C2W2_U", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.C3B4_U", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.C3W3_U", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.FCW5_U", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.DataOutC1_U", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.DataOutMP1_U", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.DataOutC2_U", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.DataOutMP2_U", "Parent" : "0"},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.DataOutC3_U", "Parent" : "0"},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.DataOutMP3_U", "Parent" : "0"},
	{"ID" : "12", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dataOutView_U", "Parent" : "0"},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_generic_fmax_float_s_fu_1366", "Parent" : "0",
		"CDFG" : "generic_fmax_float_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "0", "ap_start" : "0", "ap_ready" : "1", "ap_done" : "0", "ap_continue" : "0", "ap_idle" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "1",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "x", "Type" : "None", "Direction" : "I"},
			{"Name" : "y", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "14", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.LoopOracle_fadd_32ns_32ns_32_4_full_dsp_1_U3", "Parent" : "0"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.LoopOracle_fmul_32ns_32ns_32_3_max_dsp_1_U4", "Parent" : "0"},
	{"ID" : "16", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.LoopOracle_fcmp_32ns_32ns_1_1_1_U5", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	LoopOracle {
		DataInTr {Type I LastRead 5 FirstWrite -1}
		CnnOut {Type O LastRead -1 FirstWrite 12}
		C1W1_0 {Type I LastRead -1 FirstWrite -1}
		C2W2 {Type I LastRead -1 FirstWrite -1}
		C3B4 {Type I LastRead -1 FirstWrite -1}
		C3W3 {Type I LastRead -1 FirstWrite -1}
		FCW5 {Type I LastRead -1 FirstWrite -1}}
	generic_fmax_float_s {
		x {Type I LastRead 0 FirstWrite -1}
		y {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "4086734", "Max" : "4086734"}
	, {"Name" : "Interval", "Min" : "4086735", "Max" : "4086735"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	DataInTr { ap_memory {  { DataInTr_address0 mem_address 1 15 }  { DataInTr_ce0 mem_ce 1 1 }  { DataInTr_q0 mem_dout 0 32 } } }
	CnnOut { ap_memory {  { CnnOut_address0 mem_address 1 1 }  { CnnOut_ce0 mem_ce 1 1 }  { CnnOut_we0 mem_we 1 1 }  { CnnOut_d0 mem_din 1 32 }  { CnnOut_address1 MemPortADDR2 1 1 }  { CnnOut_ce1 MemPortCE2 1 1 }  { CnnOut_we1 MemPortWE2 1 1 }  { CnnOut_d1 MemPortDIN2 1 32 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
