# 🌐 IP Grinde

Welcome to the IP Grinde project, a versatile utility for cataloging and managing IP addresses (IPv4). IP Grinde allows you to store, filter, display, and validate IP addresses efficiently and user-friendly. You can also add additional features to enhance the utility of this tool.

## Key Features

IP Grinde offers the following features:

### 1) Persistence
Cataloged IP addresses are stored persistently by the program. This means your data remains saved between program executions.

### 2) MAC Address Filtering
You can search for IP addresses based on a user-provided address and mask. IP Grinde will return stored addresses that belong to the same subnet as the one provided.

### 3) Binary/Hexadecimal/Decimal Conversion
IP addresses can be displayed in various formats: binary, hexadecimal, and decimal. You can choose the representation that suits you best.

### 4) Validation
IP Grinde performs strict validation to ensure that only valid IP addresses are accepted. This prevents you from entering anything other than valid IP addresses.

## Main Loop
IP Grinde operates as an interactive menu with the user and only closes when the user desires. You can perform actions such as adding a new IP address, listing IP addresses, searching by mask, deleting an IP address, or exiting the program.

## How to Use IP Grinde

1. Clone this repository to your computer.
2. Compile the source code.
3. Run the program.
4. Use the interactive menu to interact with IP Grinde as needed.

```bash
$ git clone https://github.com/Naywvi/Ip_grinde.git
$ cd ip_grinde
$ make
$ ./compile.sh
$ ./ip_grinde