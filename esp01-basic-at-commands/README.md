# ESP01 Basic AT Commands

This is a list of basic AT commands to test in ESP01 module.

> _**Important:** I've forgotten to configure my serial communication to send CR&LF at the end of AT commands and module always returned error, so don't forget to configure it to append a CR&LF to AT commands._

| AT Command | Description |
| ---------- | ----------- |
| AT | Tests AT startup |
| AT+RST | Restarts the module |
| AT+GMR | Checks version information |
| AT+CWMODE? | Checks wifi mode (1 - station, 2 - SoftAP, 3 - both) |
| AT+CWMODE=? | Test command |
| AT+CWMODE=1 | Sets wifi to station mode |
| AT+CWLAP | List available access points |
| AT+CWJAP=&lt;ssid>,&lt;pwd> | Connects to an access point |
| AT+CIPAP=&lt;ip>[,&lt;gtw>,&lt;subnetmask>] | Sets the IP address |
| AT+CISFSR | Gets current IP |
| AT+PING=&lt;ip> | Pings packets to a host |

