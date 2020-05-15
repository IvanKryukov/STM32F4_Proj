# Parser_proj

Parser only project.
If you want to control any action like data exchanging, peripherals control, etc. 
by computer keybord, just add _lib/parser to your project.

# Structure of command:

[command] [-p] [argument]
 -----------------------
[command] - word of several signs (example: help, log, set, send...)
[-p] - parameter of command, it contains an only sign (example: -p, -m... )
[argument] - word of numeric or symbolic signs to specialize commands


# It contains:
- _lib/parser
- usart_config
- its own configuration of GPIO in main.c
