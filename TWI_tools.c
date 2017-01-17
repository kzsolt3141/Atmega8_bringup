/*
 * TWI_tools.c
 *
 * Created: 12/22/2016 6:42:01 PM
 *  Author: Zsolt
 *-------------------------------
 * Do NOT modify this code!
 *-------------------------------
 */ 

//------------------------------------------------
//               HEADERS
//------------------------------------------------
#include "TWI_tools.h"

//------------------------------------------------
//               FUNCTIONS
//------------------------------------------------

//------------------------------------------------
//               void TWIInit(void)
//------------------------------------------------
// the function initializes TWI controller
void TWIInit(void)
{
    //set SCL to F_CPU/(16+2*TWBR*prescaler)
    TWSR &= ~((1 << TWPS1) | 
	          (1 << TWPS0));  // set prescaler to 1
    TWBR  =   0x1;            // set bitrate to  12
    TWCR |=   (1 << TWEN);    // enable TWI
}

//------------------------------------------------
//               void TWIStart(void)
//------------------------------------------------
// send start bit condition through TWI interface: 
// SCL is high while SDA falls
void TWIStart(void)
{
    TWCR  = (1 << TWINT)|               // clearing this flag (by writing 1) will start a transfer
	        (1 << TWSTA)|               // set controller to send start bit trough TWI
			(1 << TWEN);                // keep  TWI interface enable
    while ((TWCR & (1 << TWINT)) == 0); // wait until TWINT is cleared
}

//------------------------------------------------
//               void TWIStop(void)
//------------------------------------------------
// send stop bit condition through TWI interface: 
// SCL is high while SDA rises
void TWIStop(void)
{
    TWCR  = (1 << TWINT)| // clearing this flag will start a transfer
	        (1 << TWSTO)| // set controller to send stop bit trough TWI
		    (1 << TWEN);  // enable TWI interface
}

//------------------------------------------------
//               void TWIWrite(uint8_t u8data)
//------------------------------------------------
//write 8 bit data trough TWI interface into slave device
void TWIWrite(uint8_t u8data)
{
    TWDR = u8data;           // insert 8bit data in data register
    TWCR |= (1 << TWINT)|    // start a transfer by clearing TWINT flag
	        (1 << TWEN);     // keep TWI interface on
	TWCR &= ~((1 << TWSTA)   // start bit condition set to 0
	         |(1 << TWSTO)); // stop bit condition set to 0
    while ((TWCR & (1 << TWINT)) == 0); // wait until TWINT is cleared
}

//------------------------------------------------
//               uint8_t TWIReadACK(void)
//------------------------------------------------
// read out a 8 bit data from slave through TWI interface
// the data will appear in TWDR register, 
// after the 8 bit data is received , ACK is sent to slave device
// the function returns the value from TWDR
uint8_t TWIReadACK(void)
{
    TWCR  = (1 << TWINT)|               // start a transfer by clearing TWINT flag
	        (1 << TWEN) |               // keep TWI interface on
			(1 << TWEA);                // send/receive acknowledge bit
    while ((TWCR & (1 << TWINT)) == 0); // wait until TWINT is cleared
    return TWDR;                        // return read out data
}

//------------------------------------------------
//               uint8_t TWIReadNACK(void)
//------------------------------------------------
// read out a 8 bit data from slave through TWI interface
// the data will appear in TWDR register, 
// after the 8 bit data is received , ACK is NOT sent to slave device
// the function returns the value from TWDR
uint8_t TWIReadNACK(void)
{
    TWCR  = (1 << TWINT)|  // start a transfer by clearing TWINT flag
	        (1 << TWEN);   // keep TWI interface on
    while ((TWCR & (1 << TWINT)) == 0); // wait until TWINT is cleared
    return TWDR;           // return read out data
}

//------------------------------------------------
//               uint8_t TWIGetStatus(void)
//------------------------------------------------
// after each thransfer the TWI controller signalizes the 
// status of the transfer writing a status code into TWSR register
// the function returnes the status register value
// obs: lower 3 bits are not fro status => masking them is required
uint8_t TWIGetStatus(void)
{
    uint8_t status;
    status = TWSR & 0xF8; // mask lower 3 bits of the status register
    return status;        // return the masked value
}