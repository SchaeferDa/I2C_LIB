# I²C-Library

## Overview
This I2C-Library is an education project.  
The I2C_LIB is written for Atmel ATmega328P and developed with Atmel Studio 7.0 IDE.   

**You can use it at your own risk.**

**[Download Library [latest version]](https://github.com/schaeferservices/I2C_LIB/releases)**

## Properties
### Used Portpins
- SDA: Port D Pin 2 [PD2]
- SCL: Port D Pin 3 [PD3]
- The library works for the Philips-I²C-Specification

## Usage
### Initalize I²C-Bus
```c
void initI2C(double time, char unit);
```
*set unit 'u' for µs  
set unir 'm' for ms*  

> parameters are optional  
> by default Bus is set to 5µs

### send start condition
```c
void sendStartCondition();
```

### send stop condition
```c
void sendStopCondition();
```

### send byte to bus
```c
boolean sendByte(unsigned char byte);
```

### read slave without specified register
```c
unsigned char readSlave(unsigned char slaveAddress);
```

### read register from slave
```c
unsigned char readRegister(unsigned char slaveAddress, unsigned char registerAddress);
```
