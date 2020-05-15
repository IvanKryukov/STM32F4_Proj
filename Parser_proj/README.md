# Parser_proj

HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
H                                               H
H     HH   HH HHHHHH  HHHH  HHHHH   HHHHH       H
H    //H H//   //   //     //  // //   //       H
H   // H //   //   //     HHHHH  //   //        H
H  //   //   //   //     // H   //   //         H
H //   // HHHHHH  HHHH  //   H  HHHHH           H
H                                               H
H     HHHHH   HHHH   HHHHH   HHHHH HHHHHH HHHHH H
H    //  // //   // //  // //     //     //  // H
H   HHHHH  HHHHHHH HHHHH   HHHH  HHHHHH HHHHH   H
H  //     //   // // H       // //     // H     H
H //     //   // //   H HHHHH  HHHHHH //   H    H
H                                               H
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH$

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