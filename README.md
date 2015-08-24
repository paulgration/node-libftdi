node-libftdi
============

Binding for ftdi library calls.

Written and tested with node.js v0.12.7 on linux.

Requires ftdi development headers. Installing headers on Ubuntu:

```bash
$ sudo apt-get install libftdi-dev
```

Permissions may need to be changed to access the USB devices as a standard user.
Example udev rule to set the group permissions for ftdi devices:

```bash
SUBSYSTEM=="usb",ATTR{idVendor}=="0403",ATTR{idProduct}=="6001",GROUP="plugdev"
```

A specific device can be targeted by serial number as shown in the 'Example
usage' section.

## Installation

```bash
$ npm install libftdi
```

## Available methods

* create_context()
* ftdi_usb_open_desc(context, vendor, product, description, serial)
* ftdi_set_bitmode(context, bitmask, mode)
* ftdi_set_baudrate(context, baudrate)
* ftdi_get_error_string(context)
* ftdi_read_data(context, buf)
* ftdi_write_data(context, buf, size)
* ftdi_usb_purge_tx_buffer(context)

## Example usage

```js
var libftdi = require('libftdi')

// FTDI USB identifiers
var usbVendor = 0x0403;
var usbProduct = 0x6001;

// Read buffer size
var rxBufSize = 2048;

// Read baud rate
var rxBaudRate = 9600;

// Serial number of device
var serial = 'FT123456';

// Context
var ctx = libftdi.create_context();

libftdi.ftdi_usb_open_desc(ctx, usbVendor, usbProduct, null, serial);
console.log(libftdi.ftdi_get_error_string(ctx));

libftdi.ftdi_set_baudrate(ctx, rxBaudRate);
console.log(libftdi.ftdi_get_error_string(ctx));

// Buffer
var buf = new Buffer(rxBufSize);

// Read data
var data = libftdi.ftdi_read_data(ctx, buf);
console.log(libftdi.ftdi_get_error_string(ctx));
console.log('Byte count: ' + data);
console.log(buf);

// etc
```

## To Do
* Look at using NAN
* Add further error checking to function arguments
* Support for operating systems other than linux
* Add other functions from c version of libftdi
