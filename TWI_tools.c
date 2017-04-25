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
    TWSR &=  ~((1 << TWPS1) | (1 << TWPS0));  // set prescaler to 1
    TWBR  =   0x02;            // set bitrate to  12
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


void TWIReadRegBurst (uint8_t* buffer,const uint8_t slave_addr ,const uint8_t internal_addr, const uint8_t size)
{
	uint8_t status, i;
	TWIStart();									  // send S (Start bit)
	if (TWIGetStatus() != 0x08)					  // verify if S was sent
		printf("S bit error\n\r");
	TWIWrite(slave_addr << 1);			          // write to the slave address with W (write) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x18)							  // verify if slave responds to his address
	{
		printf("%x SLAVE at W lost\n\r", status);
	}		
	TWIWrite(internal_addr);					  // send to slave the internal register address which will be read
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x28)							  // verify if the slave responds to the written address with ACK
	{
		printf("%x internal addr lost\n\r", status);
	}		
	TWIStart();                                   // send a repeated S (start) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x10)							  // verify if the slave responds to the repeated start condition
	{
		printf("%x repeated start failed\n\r", status);
	}
	TWIWrite((slave_addr << 1) | 1);	          // write to the slave address with R (read) condition
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x40)							  // verify if slave responds to his address
	{
		printf("%x Slave at R lost\n\r", status);
	}
	for(i = 0; i < (size -1); i++)
	{
		*(buffer+i) = TWIReadACK();						  // read out data from with ACK (only one data will be read out, no need for ACK)
		status = TWIGetStatus();					  // get the status of the transfer
		if (status != 0x50)							  // verify if transfer was OK
		{
			printf("%x data with ACK lost\n\r", status);
		}
	}
	
	*(buffer+i) = TWIReadNACK();
	status = TWIGetStatus();					  // get the status of the transfer
	if (status != 0x58)							  // verify if transfer was OK
	{
		printf("%x data with NACK lost\n\r", status);
	}
	TWIStop();                                   // send P (stop) bit
}

void TWIWriteReg (const uint8_t slave_addr,const uint8_t internal_addr, const uint8_t data)
{
	uint8_t status;
	TWIStart();                               // send S (Start bit)
	status = TWIGetStatus(); 
	if (status != 0x08)               // verify if S was sent
	{
		printf("0x%x S bit error(W)\n\r", status);
	}	
	TWIWrite(slave_addr << 1);                // write to the slave address with W (write) condition 
	status = TWIGetStatus();                  // get the status of the transfer
	if (status != 0x18)                       // verify if slave responds to his address
	{
		printf("0x%x SLAVE lost(W)\n\r", status);
	}		
	TWIWrite(internal_addr);                  // send to slave the internal register address which will be written
	status = TWIGetStatus();                  // get the status of the transfer
	if (status != 0x28)						  // verify if the slave responds to the written address with ACK
	{
		printf("0x%x internal addr found(W)\n\r", status);
	}		
	TWIWrite(data);                           // write the internal register with the data
	status = TWIGetStatus();				  // get the status of the transfer
	if (status != 0x28)						  // verify if the slave accepted writted data with ACK
	{
		printf("0x%x Data not written(W)\n\r", status);
	}	
	TWIStop();                                // send P (stop) bit
}

void TWISniff ()
{
	uint8_t status, i;
	
	for (i=0; i<0xFF; i++)
	{
		TWIStart();                               // send S (Start bit)
		status = TWIGetStatus(); 
		if (status != 0x08)               // verify if S was sent
		{
			printf("0x%x S bit error(W)\n\r", status);
		}	
		
		TWIWrite(i << 1);                // write to the slave address with W (write) condition 
		status = TWIGetStatus();                  // get the status of the transfer
		if (status != 0x18)                       // verify if slave responds to his address
		{
			printf("0x%x 0x%x SLAVE lost(W)\n\r", status, i);
		}
		else
		{
			printf("0x%x 0x%x YESS\n\r", status, i);
		}	
		
		TWIStop(); 
	}		 	
}