/*-------------------------------------------------------------------------
   Register Declarations for NXP  P89LPC924 and P89LPC925
   (Based on datasheet Rev. 03 � 15 December 2004)

   Written By -  Jesus Calvino-Fraga / jesusc at ece.ubc.ca (February 2007)

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option); any later version

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

   In other words, you are welcome to use, share and improve this program
   You are forbidden to forbid anyone else to use, share and improve
   what you give them.   Help stamp out software-hoarding!
-------------------------------------------------------------------------*/

#ifndef REG_P89LPC925_H
#define REG_P89LPC925_H

#include <compiler.h>

SFR(ACC, 0xE0); // Accumulator
   SBIT(ACC_7, 0xE0, 7);
   SBIT(ACC_6, 0xE0, 6);
   SBIT(ACC_5, 0xE0, 5);
   SBIT(ACC_4, 0xE0, 4);
   SBIT(ACC_3, 0xE0, 3);
   SBIT(ACC_2, 0xE0, 2);
   SBIT(ACC_1, 0xE0, 1);
   SBIT(ACC_0, 0xE0, 0);

SFR(ADCON1, 0x97); // A/D control register 1
   #define ENBI1   0x80
   #define ENADCI1 0x40
   #define TMM1    0x20
   #define EDGE1   0x10
   #define ADCI1   0x08
   #define ENADC1  0x04
   #define ADCS11  0x02
   #define ADCS10  0x01

SFR(ADINS, 0xA3); // A/D input select
   #define ADI13 0x80
   #define ADI12 0x40
   #define ADI11 0x20
   #define ADI10 0x10

SFR(ADMODA, 0xC0); // A/D mode register A
   #define BNDI1  0x80
   #define BURST1 0x40
   #define SCC1   0x20
   #define SCAN1  0x10

SFR(ADMODB, 0xA1); // A/D mode register B
   #define CLK2   0x80
   #define CLK1   0x40
   #define CLK0   0x20
   #define ENDAC1 0x08
   #define BSA1   0x02

SFR(AD1BH, 0xC4); // A/D_1 boundary high register

SFR(AD1BL, 0xBC); // A/D_1 boundary low register

SFR(AD1DAT0, 0xD5); // A/D_1 data register 0

SFR(AD1DAT1, 0xD6); // A/D_1 data register 1

SFR(AD1DAT2, 0xD7); // A/D_1 data register 2

SFR(AD1DAT3, 0xF5); // A/D_1 data register 3

SFR(AUXR1, 0xA2); // Auxiliary function register
   #define CLKLP 0x80
   #define EBRR  0x40
   #define ENT1  0x20
   #define ENT0  0x10
   #define SRST  0x08
   #define DPS   0x01

SFR(B, 0xF0); // B register
   SBIT(B_7, 0xF0, 7);
   SBIT(B_6, 0xF0, 6);
   SBIT(B_5, 0xF0, 5);
   SBIT(B_4, 0xF0, 4);
   SBIT(B_3, 0xF0, 3);
   SBIT(B_2, 0xF0, 2);
   SBIT(B_1, 0xF0, 1);
   SBIT(B_0, 0xF0, 0);

SFR(BRGR0, 0xBE); // Baud rate generator rate LOW

SFR(BRGR1, 0xBF); // Baud rate generator rate HIGH

SFR(BRGCON, 0xBD); // Baud rate generator control
   #define SBRGS 0x02
   #define BRGEN 0x01

SFR(CMP1, 0xAC); // Comparator1 control register
   #define CE1  0x20
   #define CP1  0x10
   #define CN1  0x08
   #define OE1  0x04
   #define CO1  0x02
   #define CMF1 0x01

SFR(CMP2, 0xAD); // Comparator2 control register
   #define CE2  0x20
   #define CP2  0x10
   #define CN2  0x08
   #define OE2  0x04
   #define CO2  0x02
   #define CMF2 0x01

SFR(DIVM, 0x95); // CPU clock divide-by-M control

SFR(DPH, 0x83); // Data pointer HIGH

SFR(DPL, 0x82); // Data pointer LOW

SFR(FMADRH, 0xE7); // Program Flash address HIGH

SFR(FMADRL, 0xE6); // Program Flash address LOW

SFR(FMCON, 0xE4); // Program Flash control (Read)
   #define BUSY 0x80
   #define HVA  0x08
   #define HVE  0x04
   #define SV  0x02
   #define OI  0x01

SFR(FMCON, 0xE4); // Program Flash control (Write)
   #define FMCMD_7 0x80
   #define FMCMD_6 0x40
   #define FMCMD_5 0x20
   #define FMCMD_4 0x10
   #define FMCMD_3 0x08
   #define FMCMD_2 0x04
   #define FMCMD_1 0x02
   #define FMCMD_0 0x01

SFR(FMDATA, 0xE5); // Program Flash data

SFR(I2ADR, 0xDB); // I2C slave address register
   #define I2ADR_6 0x80
   #define I2ADR_5 0x40
   #define I2ADR_4 0x20
   #define I2ADR_3 0x10
   #define I2ADR_2 0x08
   #define I2ADR_1 0x04
   #define I2ADR_0 0x02
   #define GC      0x01

SFR(I2CON, 0xD8); // I2C control register
   SBIT(I2EN,  0xD8, 6);
   SBIT(STA,   0xD8, 5);
   SBIT(STO,   0xD8, 4);
   SBIT(SI,    0xD8, 3);
   SBIT(AA,    0xD8, 2);
   SBIT(CRSEL, 0xD8, 0);

SFR(I2DAT, 0xDA); // I2C data register

SFR(I2SCLH, 0xDD); // Serial clock generator/SCL duty cycle register HIGH

SFR(I2SCLL, 0xDC); // Serial clock generator/SCL duty cycle register LOW

SFR(I2STAT, 0xD9); // I2C status register
   #define STA_4 0x80
   #define STA_3 0x40
   #define STA_2 0x20
   #define STA_1 0x10
   #define STA_0 0x08

SFR(IEN0, 0xA8); // Interrupt enable 0
   SBIT(EA,    0xA8, 7);
   SBIT(EWDRT, 0xA8, 6);
   SBIT(EBO,   0xA8, 5);
   SBIT(ES,    0xA8, 4);
   SBIT(ESR,   0xA8, 4);
   SBIT(ET1,   0xA8, 3);
   SBIT(EX1,   0xA8, 2);
   SBIT(ET0,   0xA8, 1);
   SBIT(EX0,   0xA8, 0);

SFR(IEN1, 0xE8); // Interrupt enable 1
   SBIT(EAD,  0xE8, 7);
   SBIT(EST,  0xE8, 6);
   SBIT(EC,   0xE8, 2);
   SBIT(EKBI, 0xE8, 1);
   SBIT(EI2C, 0xE8, 0);

SFR(IP0, 0xB8); // Interrupt priority 0
   SBIT(PWDRT, 0xB8, 6);
   SBIT(PBO,   0xB8, 5);
   SBIT(PS,    0xB8, 4);
   SBIT(PSR,   0xB8, 4);
   SBIT(PT1,   0xB8, 3);
   SBIT(PX1,   0xB8, 2);
   SBIT(PT0,   0xB8, 1);
   SBIT(PX0,   0xB8, 0);

SFR(IP0H, 0xB7); // Interrupt priority 0 HIGH
   #define PWDRTH 0x40
   #define PBOH   0x20
   #define PSH    0x10
   #define PSRH   0x10
   #define PT1H   0x08
   #define PX1H   0x04
   #define PT0H   0x02
   #define PX0H   0x01

SFR(IP1, 0xF8); // Interrupt priority 1
   SBIT(PAD,  0xF8, 7);
   SBIT(PST,  0xF8, 6);
   SBIT(PC,   0xF8, 2);
   SBIT(PKBI, 0xF8, 1);
   SBIT(PI2C, 0xF8, 0);

SFR(IP1H, 0xF7); // Interrupt priority 1 HIGH
   #define PADH  0x80
   #define PSTH  0x40
   #define PCH   0x04
   #define PKBIH 0x02
   #define PI2CH 0x01

SFR(KBCON, 0x94); // Keypad control register
   #define PATN_SEL 0x02 //Pattern Matching Polarity selection
   #define KBIF     0x01 // Keypad Interrupt Flag

SFR(KBMASK, 0x86); // Keypad interrupt register mask

SFR(KBPATN, 0x93); // Keypad pattern register

SFR(P0, 0x80); // Port 0
   SBIT(P0_7, 0x80, 7);
   SBIT(P0_6, 0x80, 6);
   SBIT(P0_5, 0x80, 5);
   SBIT(P0_4, 0x80, 4);
   SBIT(P0_3, 0x80, 3);
   SBIT(P0_2, 0x80, 2);
   SBIT(P0_1, 0x80, 1);
   SBIT(P0_0, 0x80, 0);
   //P0 alternate pin functions
   SBIT(T1,     0x80, 7);
   SBIT(CMP_1,  0x80, 6); //Should be CMP1 but there is SFR with that name
   SBIT(CMPREF, 0x80, 5);
   SBIT(CIN1A,  0x80, 4);
   SBIT(CIN1B,  0x80, 3);
   SBIT(CIN2A,  0x80, 2);
   SBIT(CIN2B,  0x80, 1);
   SBIT(CMP_2,  0x80, 0); //Should be CMP2 but there is SFR with that name
   //More P0 alternate pin functions
   SBIT(KB7, 0x80, 7);
   SBIT(KB6, 0x80, 6);
   SBIT(KB5, 0x80, 5);
   SBIT(KB4, 0x80, 4);
   SBIT(KB3, 0x80, 3);
   SBIT(KB2, 0x80, 2);
   SBIT(KB1, 0x80, 1);
   SBIT(KB0, 0x80, 0);

SFR(P1, 0x90); // Port 1
   SBIT(P1_7, 0x90, 7);
   SBIT(P1_6, 0x90, 6);
   SBIT(P1_5, 0x90, 5);
   SBIT(P1_4, 0x90, 4);
   SBIT(P1_3, 0x90, 3);
   SBIT(P1_2, 0x90, 2);
   SBIT(P1_1, 0x90, 1);
   SBIT(P1_0, 0x90, 0);
   //P1 alternate pin functions
   SBIT(RST,  0x90, 5);
   SBIT(INT1, 0x90, 4);
   SBIT(INT0, 0x90, 3);
   SBIT(SDA,  0x90, 3);
   SBIT(T0,   0x90, 2);
   SBIT(SCL,  0x90, 2);
   SBIT(RXD,  0x90, 1);
   SBIT(TXD,  0x90, 0);

SFR(P3, 0xB0); // Port 3
   SBIT(P3_1, 0xB0, 1);
   SBIT(P3_0, 0xB0, 0);
   SBIT(XTAL1, 0xB0, 1);
   SBIT(XTAL2, 0xB0, 0);

SFR(P0M1, 0x84); // Port0 output mode1
   #define P0M1_7 0x80
   #define P0M1_6 0x40
   #define P0M1_5 0x20
   #define P0M1_4 0x10
   #define P0M1_3 0x08
   #define P0M1_2 0x04
   #define P0M1_1 0x02
   #define P0M1_0 0x01

SFR(P0M2, 0x85); // Port0 output mode2
   #define P0M2_7 0x80
   #define P0M2_6 0x40
   #define P0M2_5 0x20
   #define P0M2_4 0x10
   #define P0M2_3 0x08
   #define P0M2_2 0x04
   #define P0M2_1 0x02
   #define P0M2_0 0x01

SFR(P1M1, 0x91); // Port1 output mode1
   #define P1M1_7 0x80
   #define P1M1_6 0x40
   #define P1M1_4 0x10
   #define P1M1_3 0x08
   #define P1M1_2 0x04
   #define P1M1_1 0x02
   #define P1M1_0 0x01

SFR(P1M2, 0x92); // Port1 output mode2
   #define P1M2_7 0x80
   #define P1M2_6 0x40
   #define P1M2_4 0x10
   #define P1M2_3 0x08
   #define P1M2_2 0x04
   #define P1M2_1 0x02
   #define P1M2_0 0x01

SFR(P3M1, 0xB1); // Port3 output mode1
   #define P3M1_1 0x02
   #define P3M1_0 0x01

SFR(P3M2, 0xB2); // Port3 output mode2
   #define P3M2_1 0x02
   #define P3M2_0 0x01

SFR(PCON, 0x87); // Power control register
   #define SMOD1 0x80
   #define SMOD0 0x40
   #define BOPD  0x20
   #define BOI   0x10
   #define GF1   0x08
   #define GF0   0x04
   #define PMOD1 0x02
   #define PMOD0 0x01

SFR(PCONA, 0xB5); // Power control register A
   #define RTCPD 0x80
   #define VCPD  0x20
   #define ADPD  0x10
   #define I2PD  0x08
   #define SPD   0x02

SFR(PSW, 0xD0); // Program status word
   SBIT(CY,  0xD0, 7);
   SBIT(AC,  0xD0, 6);
   SBIT(F0,  0xD0, 5);
   SBIT(RS1, 0xD0, 4);
   SBIT(RS0, 0xD0, 3);
   SBIT(OV,  0xD0, 2);
   SBIT(F1,  0xD0, 1);
   SBIT(P,   0xD0, 0);

SFR(PT0AD, 0xF6); // Port0 digital input disable
   #define PT0AD_5 0x20
   #define PT0AD_4 0x10
   #define PT0AD_3 0x08
   #define PT0AD_2 0x04
   #define PT0AD_1 0x02

SFR(RSTSRC, 0xDF); // Reset source register
   #define BOF 0x20
   #define POF 0x10
   #define R_BK 0x08
   #define R_WD 0x04
   #define R_SF 0x02
   #define R_EX 0x01

SFR(RTCCON, 0xD1); // Real-time clock control
   #define RTCF  0x80
   #define RTCS1 0x40
   #define RTCS0 0x20
   #define ERTC  0x02
   #define RTCEN 0x01

SFR(RTCH, 0xD2); // Real-time clock register HIGH

SFR(RTCL, 0xD3); // Real-time clock register LOW

SFR(SADDR, 0xA9); // Serial port address register

SFR(SADEN, 0xB9); // Serial port address enable

SFR(SBUF, 0x99); // Serial Port data buffer register

SFR(SCON, 0x98); // Serial port control
   SBIT(FE,  0x98, 7);
   SBIT(SM0, 0x98, 7);
   SBIT(SM1, 0x98, 6);
   SBIT(SM2, 0x98, 5);
   SBIT(REN, 0x98, 4);
   SBIT(TB8, 0x98, 3);
   SBIT(RB8, 0x98, 2);
   SBIT(TI,  0x98, 1);
   SBIT(RI,  0x98, 0);

SFR(SSTAT, 0xBA); // Serial port extended status register
   #define DBMOD  0x80
   #define INTLO  0x40
   #define CIDIS  0x20
   #define DBISEL 0x10
   #define FE     0x08
   #define BR     0x04
   #define OE     0x02
   #define STINT  0x01

SFR(SP, 0x81); // Stack pointer

SFR(TAMOD, 0x8F); // Timer0 and 1 auxiliary mode
   #define T1M2 0x10
   #define T0M2 0x01

SFR(TCON, 0x88); // Timer0 and 1 control
   SBIT(TF1, 0x88, 7);
   SBIT(TR1, 0x88, 6);
   SBIT(TF0, 0x88, 5);
   SBIT(TR0, 0x88, 4);
   SBIT(IE1, 0x88, 3);
   SBIT(IT1, 0x88, 2);
   SBIT(IE0, 0x88, 1);
   SBIT(IT0, 0x88, 0);

SFR(TH0, 0x8C); // Timer0 HIGH

SFR(TH1, 0x8D); // Timer 1 HIGH

SFR(TL0, 0x8A); // Timer 0 LOW

SFR(TL1, 0x8B); // Timer 1 LOW

SFR(TMOD, 0x89); // Timer0 and 1 mode
   #define T1GATE 0x80
   #define T1C_T  0x40
   #define T1M1   0x20
   #define T1M0   0x10
   #define T0GATE 0x08
   #define T0C_T  0x04
   #define T0M1   0x02
   #define T0M0   0x01

SFR(TRIM, 0x96); // Internal oscillator trim register
   #define RCCLK  0x80
   #define ENCLK  0x40
   #define TRIM_5 0x20
   #define TRIM_4 0x10
   #define TRIM_3 0x08
   #define TRIM_2 0x04
   #define TRIM_1 0x02
   #define TRIM_0 0x01

SFR(WDCON, 0xA7); // Watchdog control register
   #define PRE2  0x80 //Watchdog Prescaler Tap Select bit 2
   #define PRE1  0x40 //Watchdog Prescaler Tap Select bit 1
   #define PRE0  0x20 //Watchdog Prescaler Tap Select bit 0
   #define WDRUN 0x04 //Watchdog Run Control
   #define WDTOF 0x02 //Watchdog Timer Time-Out Flag
   #define WDCLK 0x01 //Watchdog input clock select

SFR(WDL, 0xC1); // Watchdog load

SFR(WFEED1, 0xC2); // Watchdog feed 1

SFR(WFEED2, 0xC3); // Watchdog feed 2

#endif /*REG_P89LPC925_H*/
