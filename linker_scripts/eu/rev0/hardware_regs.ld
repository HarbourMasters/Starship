// Signal Processor Registers
SP_MEM_ADDR_REG = 0xA4040000; // defined:True
SP_DRAM_ADDR_REG = 0xA4040004; // defined:True
SP_RD_LEN_REG = 0xA4040008; // defined:True
SP_WR_LEN_REG = 0xA404000C; // defined:True
SP_STATUS_REG = 0xA4040010; // defined:True
SP_DMA_FULL_REG = 0xA4040014; // defined:True
SP_DMA_BUSY_REG = 0xA4040018; // defined:True
SP_SEMAPHORE_REG = 0xA404001C; // defined:True

SP_PC = 0xA4080000; // defined:True

// Display Processor Command Registers / Rasterizer Interface
DPC_START_REG = 0xA4100000; // defined:True
DPC_END_REG = 0xA4100004; // defined:True
DPC_CURRENT_REG = 0xA4100008; // defined:True
DPC_STATUS_REG = 0xA410000C; // defined:True
DPC_CLOCK_REG = 0xA4100010; // defined:True
DPC_BUFBUSY_REG = 0xA4100014; // defined:True
DPC_PIPEBUSY_REG = 0xA4100018; // defined:True
DPC_TMEM_REG = 0xA410001C; // defined:True

// Display Processor Span Registers
DPS_TBIST_REG = 0xA4200000; // defined:True // DPS_TBIST_REG / DP_TMEM_BIST
DPS_TEST_MODE_REG = 0xA4200004; // defined:True
DPS_BUFTEST_ADDR_REG = 0xA4200008; // defined:True
DPS_BUFTEST_DATA_REG = 0xA420000C; // defined:True

// MIPS Interface Registers
MI_MODE_REG = 0xA4300000; // defined:True // MI_MODE_REG / MI_INIT_MODE_REG
MI_VERSION_REG = 0xA4300004; // defined:True
MI_INTR_REG = 0xA4300008; // defined:True
MI_INTR_MASK_REG = 0xA430000C; // defined:True

// Video Interface Registers
VI_STATUS_REG = 0xA4400000; // defined:True // VI_STATUS_REG / VI_CONTROL_REG
VI_DRAM_ADDR_REG = 0xA4400004; // defined:True // VI_DRAM_ADDR_REG / VI_ORIGIN_REG
VI_WIDTH_REG = 0xA4400008; // defined:True
VI_INTR_REG = 0xA440000C; // defined:True
VI_CURRENT_REG = 0xA4400010; // defined:True
VI_BURST_REG = 0xA4400014; // defined:True // VI_BURST_REG / VI_TIMING_REG
VI_V_SYNC_REG = 0xA4400018; // defined:True
VI_H_SYNC_REG = 0xA440001C; // defined:True
VI_LEAP_REG = 0xA4400020; // defined:True
VI_H_START_REG = 0xA4400024; // defined:True
VI_V_START_REG = 0xA4400028; // defined:True
VI_V_BURST_REG = 0xA440002C; // defined:True
VI_X_SCALE_REG = 0xA4400030; // defined:True
VI_Y_SCALE_REG = 0xA4400034; // defined:True

// Audio Interface Registers
AI_DRAM_ADDR_REG = 0xA4500000; // defined:True
AI_LEN_REG = 0xA4500004; // defined:True
AI_CONTROL_REG = 0xA4500008; // defined:True
AI_STATUS_REG = 0xA450000C; // defined:True
AI_DACRATE_REG = 0xA4500010; // defined:True
AI_BITRATE_REG = 0xA4500014; // defined:True

// Peripheral/Parallel Interface Registers
PI_DRAM_ADDR_REG = 0xA4600000; // defined:True
PI_CART_ADDR_REG = 0xA4600004; // defined:True
D_A4600005 = 0xA4600005; // defined:True // TODO figure out its name
D_A4600006 = 0xA4600006; // defined:True // TODO figure out its name
D_A4600007 = 0xA4600007; // defined:True // TODO figure out its name
PI_RD_LEN_REG = 0xA4600008; // defined:True
PI_WR_LEN_REG = 0xA460000C; // defined:True
PI_STATUS_REG = 0xA4600010; // defined:True
PI_BSD_DOM1_LAT_REG = 0xA4600014; // defined:True // PI dom1 latency
PI_BSD_DOM1_PWD_REG = 0xA4600018; // defined:True // PI dom1 pulse width
PI_BSD_DOM1_PGS_REG = 0xA460001C; // defined:True // PI dom1 page size
PI_BSD_DOM1_RLS_REG = 0xA4600020; // defined:True // PI dom1 release
PI_BSD_DOM2_LAT_REG = 0xA4600024; // defined:True // PI dom2 latency
PI_BSD_DOM2_LWD_REG = 0xA4600028; // defined:True // PI dom2 pulse width
PI_BSD_DOM2_PGS_REG = 0xA460002C; // defined:True // PI dom2 page size
PI_BSD_DOM2_RLS_REG = 0xA4600030; // defined:True // PI dom2 release

// RDRAM Interface Registers
RI_MODE_REG = 0xA4700000; // defined:True
RI_CONFIG_REG = 0xA4700004; // defined:True
RI_CURRENT_LOAD_REG = 0xA4700008; // defined:True
RI_SELECT_REG = 0xA470000C; // defined:True
RI_REFRESH_REG = 0xA4700010; // defined:True
RI_LATENCY_REG = 0xA4700014; // defined:True
RI_RERROR_REG = 0xA4700018; // defined:True
RI_WERROR_REG = 0xA470001C; // defined:True

// Serial Interface Registers
SI_DRAM_ADDR_REG = 0xA4800000; // defined:True
SI_PIF_ADDR_RD64B_REG = 0xA4800004; // defined:True
D_A4800008 = 0xA4800008; // defined:True // reserved
D_A480000C = 0xA480000C; // defined:True // reserved
SI_PIF_ADDR_WR64B_REG = 0xA4800010; // defined:True
D_A4800014 = 0xA4800014; // defined:True // reserved
SI_STATUS_REG = 0xA4800018; // defined:True

LEO_CMD = 0xA5000508;
LEO_STATUS = 0xA5000508;
LEO_BM_CTL = 0xA5000510;
LEO_BM_STATUS = 0xA5000510;
LEO_SEQ_CTL = 0xA5000518;
LEO_SEQ_STATUS = 0xA5000518;
LEO_C2_BUFF = 0xA5000000;
LEO_SECTOR_BUFF = 0xA5000400;
LEO_DATA = 0xA5000500;
LEO_MISC_REG = 0xA5000504;
LEO_CUR_TK = 0xA500050C;
LEO_ERR_SECTOR = 0xA5000514;
LEO_CUR_SECTOR = 0xA500051C;
LEO_HARD_RESET = 0xA5000520;
LEO_C1_S0 = 0xA5000524;
LEO_HOST_SECBYTE = 0xA5000528;
LEO_C1_S2 = 0xA500052C;
LEO_SEC_BYTE = 0xA5000530;
LEO_C1_S4 = 0xA5000534;
LEO_C1_S6 = 0xA5000538;
LEO_CUR_ADDR = 0xA500053C;
LEO_ID_REG = 0xA5000540;
LEO_TEST_REG = 0xA5000544;
LEO_TEST_PIN_SEL = 0xA5000548;
LEO_RAM_ADDR = 0xA5000580;