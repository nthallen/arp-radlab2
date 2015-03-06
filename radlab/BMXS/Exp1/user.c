#include "bmxs_all.h"


//! Function to process the users commands from telemetry
int user_command( char *command, BMXS_t *BMXS ){

	struct OUT_FTIR_PACKET c2dPacket;

	c2dPacket.header.signature = htonl( FTIR_SIGNATURE );
	//! First char of command is tested and based on that will decide what the second char could be
	switch( command[0] ){
		case 'E':
			switch( command[1] ){
				case 'N': // Enable command
					c2dPacket.header.command = PC2D_ENABLE_TX;
					c2dPacket.header.size = htons( 1 );
					c2dPacket.txctrl.mode = FP_TM_ALL;
					tcp_send( &c2dPacket, 8 );
					return 1;
					
				case 'X':  // Clean exit mainly for debugging, not typically used by user
					c2dPacket.header.command = PC2D_ENABLE_TX;
					c2dPacket.header.size = htons( 1 );
					c2dPacket.txctrl.mode = FP_TM_DISABLE;
					tcp_send( &c2dPacket, 8 );
					return 7;
				
				default:
					nl_error( 1, "not valid command" );
					return -1;
			}
		case 'D': 
			if( command[1] == 'A' ){ // Disable Command
					c2dPacket.header.command = PC2D_ENABLE_TX;
					c2dPacket.header.size = htons( 1 );
					c2dPacket.txctrl.mode = FP_TM_STATUS;
					tcp_send( &c2dPacket, 8 );
					return 1;
				}	
			else{
				nl_error( 1, "not valid command" );
			}	
		case 'N':
			// Sets the number of coads
			if( command[1] == 'C' )
				BMXS->numcoads = atoi(&command[3]);
			return 1;
		
		case 'R':
			// The different resolutions that are possible to set in the BMXS struct
			if( command[1] == 'E' ){
				switch( command[3] ){
					case '1':
						if( (command[4] != '6') ||(command[4] != '2') ){
							c2dPacket.command.command[0] = 0x00; // 1
							BMXS->resolution = 1;
						}
						if( command[4] == '6' ){
							c2dPacket.command.command[0] = 0x04; // 16
							BMXS->resolution = 16;
						}
						if( command[4] == '2' ){
							c2dPacket.command.command[0] = 0x07; // 128
							BMXS->resolution = 128;
						}
						break;						
					case '2':
						c2dPacket.command.command[0] = 0x01; // 2
						BMXS->resolution = 2;
						break;
					case '3':
						c2dPacket.command.command[0] = 0x05; // 32
						BMXS->resolution = 32;
						break;
					case '4':
						c2dPacket.command.command[0] = 0x02; // 4
						BMXS->resolution = 4;
						break;
					case '6':
						c2dPacket.command.command[0] = 0x06; // 64
						BMXS->resolution = 64;
						break;
					case '8':
						c2dPacket.command.command[0] = 0x03; // 8
						BMXS->resolution = 8;
						break;
					default:
						nl_error( 1, "not valid resolution" );
						return -1;
				}
				c2dPacket.header.command = PC2D_DATA;
				c2dPacket.header.size = 1;
				tcp_send( &c2dPacket, sizeof(c2dPacket) );
				
			return 1;
			}
		
		default:
			return -1;
	}
}
