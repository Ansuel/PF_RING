/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2022 Intel Corporation. */

/* ethtool register test data */
struct igb_reg_test {
	u16 reg;
	u16 reg_offset;
	u16 array_len;
	u16 test_type;
	u32 mask;
	u32 write;
};

/* In the hardware, registers are laid out either singly, in arrays
 * spaced 0x100 bytes apart, or in contiguous tables.  We assume
 * most tests take place on arrays or single registers (handled
 * as a single-element array) and special-case the tables.
 * Table tests are always pattern tests.
 *
 * We also make provision for some required setup steps by specifying
 * registers to be written without any read-back testing.
 */

#define PATTERN_TEST	1
#define SET_READ_TEST	2
#define WRITE_NO_TEST	3
#define TABLE32_TEST	4
#define TABLE64_TEST_LO	5
#define TABLE64_TEST_HI	6

/* i210 reg test */
static struct igb_reg_test reg_test_i210[] = {
	{ E1000_FCAL,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_FCAH,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_FCT,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_RDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_RDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF },
	/* RDH is read-only for i210, only test RDT. */
	{ E1000_RDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_FCRTH,	   0x100, 1,  PATTERN_TEST, 0x0003FFF0, 0x0003FFF0 },
	{ E1000_FCTTV,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_TIPG,	   0x100, 1,  PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF },
	{ E1000_TDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_TDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_TDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF },
	{ E1000_TDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0x003FFFFB },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0xFFFFFFFF },
	{ E1000_TCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RA,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RA,	   0, 16, TABLE64_TEST_HI,
						0x900FFFFF, 0xFFFFFFFF },
	{ E1000_MTA,	   0, 128, TABLE32_TEST,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ 0, 0, 0, 0 }
};

/* i350 reg test */
static struct igb_reg_test reg_test_i350[] = {
	{ E1000_FCAL,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_FCAH,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_FCT,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	/* VET is readonly on i350 */
	{ E1000_RDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_RDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF },
	{ E1000_RDBAL(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_RDBAH(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDLEN(4),  0x40,  4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF },
	/* RDH is read-only for i350, only test RDT. */
	{ E1000_RDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_RDT(4),	   0x40,  4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_FCRTH,	   0x100, 1,  PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 },
	{ E1000_FCTTV,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_TIPG,	   0x100, 1,  PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF },
	{ E1000_TDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_TDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_TDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF },
	{ E1000_TDBAL(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_TDBAH(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_TDLEN(4),  0x40,  4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF },
	{ E1000_TDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_TDT(4),	   0x40,  4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0x003FFFFB },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0xFFFFFFFF },
	{ E1000_TCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RA,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RA,	   0, 16, TABLE64_TEST_HI,
						0xC3FFFFFF, 0xFFFFFFFF },
	{ E1000_RA2,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RA2,	   0, 16, TABLE64_TEST_HI,
						0xC3FFFFFF, 0xFFFFFFFF },
	{ E1000_MTA,	   0, 128, TABLE32_TEST,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ 0, 0, 0, 0 }
};

/* 82580 reg test */
static struct igb_reg_test reg_test_82580[] = {
	{ E1000_FCAL,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_FCAH,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_FCT,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_VET,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_RDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF },
	{ E1000_RDBAL(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_RDBAH(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDLEN(4),  0x40,  4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF },
	/* RDH is read-only for 82580, only test RDT. */
	{ E1000_RDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_RDT(4),	   0x40,  4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_FCRTH,	   0x100, 1,  PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 },
	{ E1000_FCTTV,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_TIPG,	   0x100, 1,  PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF },
	{ E1000_TDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_TDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_TDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF },
	{ E1000_TDBAL(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_TDBAH(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_TDLEN(4),  0x40,  4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF },
	{ E1000_TDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_TDT(4),	   0x40,  4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0x003FFFFB },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0xFFFFFFFF },
	{ E1000_TCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RA,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RA,	   0, 16, TABLE64_TEST_HI,
						0x83FFFFFF, 0xFFFFFFFF },
	{ E1000_RA2,	   0, 8, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RA2,	   0, 8, TABLE64_TEST_HI,
						0x83FFFFFF, 0xFFFFFFFF },
	{ E1000_MTA,	   0, 128, TABLE32_TEST,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ 0, 0, 0, 0 }
};

/* 82576 reg test */
static struct igb_reg_test reg_test_82576[] = {
	{ E1000_FCAL,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_FCAH,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_FCT,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_VET,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_RDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF },
	{ E1000_RDBAL(4),  0x40,  12, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_RDBAH(4),  0x40,  12, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDLEN(4),  0x40,  12, PATTERN_TEST, 0x000FFFF0, 0x000FFFFF },
	/* Enable all queues before testing. */
	{ E1000_RXDCTL(0), 0x100, 4,  WRITE_NO_TEST, 0,
						E1000_RXDCTL_QUEUE_ENABLE },
	{ E1000_RXDCTL(4), 0x40,  12, WRITE_NO_TEST, 0,
						E1000_RXDCTL_QUEUE_ENABLE },
	/* RDH is read-only for 82576, only test RDT. */
	{ E1000_RDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_RDT(4),	   0x40,  12, PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_RXDCTL(0), 0x100, 4,  WRITE_NO_TEST, 0, 0 },
	{ E1000_RXDCTL(4), 0x40,  12, WRITE_NO_TEST, 0, 0 },
	{ E1000_FCRTH,	   0x100, 1,  PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 },
	{ E1000_FCTTV,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_TIPG,	   0x100, 1,  PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF },
	{ E1000_TDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_TDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_TDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF },
	{ E1000_TDBAL(4),  0x40,  12, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF },
	{ E1000_TDBAH(4),  0x40,  12, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_TDLEN(4),  0x40,  12, PATTERN_TEST, 0x000FFFF0, 0x000FFFFF },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0x003FFFFB },
	{ E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0xFFFFFFFF },
	{ E1000_TCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RA,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RA,	   0, 16, TABLE64_TEST_HI,
						0x83FFFFFF, 0xFFFFFFFF },
	{ E1000_RA2,	   0, 8, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RA2,	   0, 8, TABLE64_TEST_HI,
						0x83FFFFFF, 0xFFFFFFFF },
	{ E1000_MTA,	   0, 128, TABLE32_TEST,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ 0, 0, 0, 0 }
};

/* 82575 register test */
static struct igb_reg_test reg_test_82575[] = {
	{ E1000_FCAL,	0x100,	1, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_FCAH,	0x100,	1, PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_FCT,	0x100,	1, PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF },
	{ E1000_VET,	0x100,	1, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RDBAL(0),   0x100,	4, PATTERN_TEST, 0xFFFFFF80,
		0xFFFFFFFF },
	{ E1000_RDBAH(0),   0x100,	4, PATTERN_TEST, 0xFFFFFFFF,
		0xFFFFFFFF },
	{ E1000_RDLEN(0),   0x100,	4, PATTERN_TEST, 0x000FFF80, 0x000FFFFF },
	/* Enable all four RX queues before testing. */
	{ E1000_RXDCTL(0),	0x100,	4, WRITE_NO_TEST, 0,
						E1000_RXDCTL_QUEUE_ENABLE },
	/* RDH is read-only for 82575, only test RDT. */
	{ E1000_RDT(0),	0x100,	4, PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_RXDCTL(0),	0x100,	4, WRITE_NO_TEST, 0, 0 },
	{ E1000_FCRTH,	0x100,	1, PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 },
	{ E1000_FCTTV,	0x100,	1, PATTERN_TEST, 0x0000FFFF, 0x0000FFFF },
	{ E1000_TIPG,	0x100,	1, PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF },
	{ E1000_TDBAL(0),   0x100,	4, PATTERN_TEST, 0xFFFFFF80,
		0xFFFFFFFF },
	{ E1000_TDBAH(0),   0x100,	4, PATTERN_TEST, 0xFFFFFFFF,
		0xFFFFFFFF },
	{ E1000_TDLEN(0),   0x100,	4, PATTERN_TEST, 0x000FFF80,
		0x000FFFFF },
	{ E1000_RCTL,	0x100,	1, SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_RCTL,	0x100,	1, SET_READ_TEST, 0x04CFB3FE, 0x003FFFFB },
	{ E1000_RCTL,	0x100,	1, SET_READ_TEST, 0x04CFB3FE, 0xFFFFFFFF },
	{ E1000_TCTL,	0x100,	1, SET_READ_TEST, 0xFFFFFFFF, 0x00000000 },
	{ E1000_TXCW,	0x100,	1, PATTERN_TEST, 0xC000FFFF, 0x0000FFFF },
	{ E1000_RA,	0,	16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ E1000_RA,	0,	16, TABLE64_TEST_HI,
						0x800FFFFF, 0xFFFFFFFF },
	{ E1000_MTA,	0,	128, TABLE32_TEST,
						0xFFFFFFFF, 0xFFFFFFFF },
	{ 0, 0, 0, 0 }
};


