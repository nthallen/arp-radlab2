
#ifndef _bomem_struct
#define _bomem_struct

#include <sys/socket.h>

#pragma pack(1)		//No gap between member of struct

#define MAX_STATUS 256			// Max # of bytes in status packet
#define CONFIGB_SIZE 1400		// # of bytes in config. block
#define MAX_CHANNEL 64			// Max # of channel for an instrument
#define MAX_FTIR_DESC 100		// Max length of ftir description
#define MAX_PASSWORD 16		// Max password length
#define MAX_FLASHFPGA 1024	// Max # of data for the FLASH/FPGA
#define MAX_COMMAND 1024		// Max # of bytes sent to instrument
#define MAX_DATA 32768			// Max # of bytes received from instrument

#define FTIR_SIGNATURE 0xAA55807F	// Packet signature


/**************************************************************************************************/
// Value Definitions
	
// Transmission mode:
#define FP_TM_ALL 			0x01		// Enable Status + Data
#define FP_TM_STATUS 		0x02		// Enable Status only
#define FP_TM_DISABLE		0x03		// Disable ALL
// Data packet type:	
#define DPT_START 			0x01 		// Dat Portion Type Start
#define DPT_CONTINUED		0x02		// Data Portion Type Continued	
#define DPT_END				0x03		// Data Portion Type End
#define DPT_COMPLETE		0x04		// Data Portion Type Complete
	
/**************************************************************************************************/
// Packet Commands and Definitions	
	
// PC to DEVICE 

#define PC2D_DATA				0xA0		// Data/status packet
#define PC2D_REQ_STATUS			0xA1		// Instrument status request
#define PC2D_REQ_CONFIG			0xA2		// Board configuration request
#define PC2D_UPL_CONFIG			0xA3		// Upload board configuration
#define PC2D_ENABLE_DEBUG		0xA4		// Enable debug mode
#define PC2D_REBOOT_EIMS		0xA5		// Ask ethernet board to reboot.
#define PC2D_FIRM_VERSIONS		0xA6		// Request firmware versions
	// 0xA7 is unused
#define PC2D_ENABLE_TX			0xA8		// Enable Data Transmission
#define PC2D_HOST_PRESENT		0xA9		// Host indicates it is still present
#define PC2D_UPL_CONFIGB		0xAA		// Upload instrument configuration block
#define PC2D_REQ_CONFIGB		0xAB		// Request instrument information	
#define PC2D_CONN_INFO			0xAC		// Send UDP port # &current time
#define PC2D_DISCONNECT			0xAD		// Request board to disconnect
#define PC2D_REQ_FTPLOG			0xAE		// Request FTP login information
#define PC2D_FTP_INFO			0xAF		// Send new FTP login information
#define PC2D_U_CONN_STATUS		0xC0		// Current connection status (UDP)
#define PC2D_U_REQ_CONFIGB		0xC1		// Request inst. configuration (UDP)
#define PC2D_U_NEW_IP			0xC2		// Inform board of new PC IP address (UDP)
#define PC2D_U_REQ_CONFIG		0xC3		// Board configuration request (UDP)
#define PC2D_U_FIRM_VERSION		0xC4		// Request firmware versions (UDP)

// DEVICE to PC Commands

#define D2PC_DATA				0xB0		// Data packet
#define D2PC_STATUS 			0xB1		// Status packet
#define D2PC_CONFIG				0xB2		// Requested board configuration
#define D2PC_RUPL_CONFIG 		0xB3		// Result of board config. upload
#define D2PC_FIRM_VERSION		0xB6		// Firmware(FLASH/FPGA) versions	
#define D2PC_REQ_HOSTP			0xB9		// Check if host is still present
#define D2PC_RUPL_CONFIGB		0xBA		// Result of inst. config. upload
#define D2PC_CONFIGB			0xBB		// Requested instrument configuration
#define D2PC_MRSTATUS			0xBD		// MR200 I/O status
#define D2PC_FTP_INFO			0xBE		// Requested FTP login information
#define D2PC_RFTP_INFO			0xBF		// Result of FTP login info. change
#define D2PC_U_CONN_STATUS 		0xD0		// Requested connection status (UDP)
#define D2PC_U_CONFIGB			0xD1		// Requested inst. configuration (UDP)	
#define D2PC_U_NEW_IP			0xD2		// Board new IP address notification (UDP)
#define D2PC_U_CONFIG			0xD3		// Requested board configuration (UDP)
#define D2PC_U_FIRM_VERSION 	0xD4		// Firmware (FLASH/FPGA) versions (UDP)	
	
/**************************************************************************************************/	
	
	

// Data sent to instrument
struct feth_command{ char command[MAX_COMMAND]; };

struct feth_config{ 						// Ethernet board configuration
	unsigned char ip_addr[4];				// Default IP
	char channel_type; 						// type of connections 0=LVDS 1=SERIAL 2=PARALLEL
	char uart_speed; 						// 1=1.5MHz, 2=2 MHz 3=3.125 MHz
	unsigned short udp_port; 				// UDP Port #
	unsigned short tcp_port; 				// TCP port #
	long max_psize; 						// Maximum packet size
	long DHCP_lease; 						// DHCP lease time
	unsigned char subnet_mask[4];
	unsigned char gateway[4]; 				// Default gateway
};

struct ftir_config_block {					// Instrument configuration (not interpreted by eth. board)

	char password[MAX_PASSWORD];
	char ftir_desc[MAX_FTIR_DESC+1];
	short type; 							// Link type
	short instrument; 						// instrument type
	char computer_ctrl;					 	// True if remote control
	char fgain_enable;						// True if first stage gain enabled
	char sgain_enable; 						// True if second stage gain enabled
	short max_channel;					 	// Max # of channels + first stage gain values for each channel
	long gains[MAX_CHANNEL][4];
	unsigned long crc; 						// CRC32 to validate block (MUST be at the end)
};

struct feth_debug{							// Debug command
	unsigned char mode;						// Debug type 0x01 Enable serial out 0x02 Enable Simulation 0x03 Memory read
	unsigned long read_start;				// Base address read start
	unsigned long read_size;				// Size to read
};
struct date_stamp_s{						 // Date stamp
	union{
		unsigned long stamp;
		struct{
			unsigned short day:8;
			unsigned short month: 8;
			unsigned short year:16;
		}date;
	};
};

struct time_stamp_s{						 // Time stamp
union{
	unsigned long stamp;
		struct{
			unsigned short seconds:8;
			unsigned short minutes: 8;
			unsigned short hour:16;
		}time;
	};
};

struct feth_conn_info{ 						// Connection info
	unsigned short udp_port;
	struct date_stamp_s host_date;
	struct time_stamp_s host_time;
	unsigned short host_msec;
};

struct feth_pc_new_ip { 					// New PC IP address notification
	unsigned char ip_addr[4];				// New PC IP address
};

struct feth_data{ 							// Data received from the instrument
	char ctype;								// Continuation type: 1=Start, 2=Continued, 3=End, 4=Complete
	char reserved[9];						// Reserved
	unsigned char data[MAX_DATA];
};

struct feth_config_block{ 					// Instrument configuartion packet

	union
	{
		unsigned char	data[CONFIGB_SIZE];
		struct ftir_config_block ftir_config;
	};
};

struct feth_s_header{						// Status header
	struct date_stamp_s date;
	struct time_stamp_s time;
	unsigned short milliseconds;
};

struct feth_status{							// Instrument status
	struct feth_s_header header;
	unsigned char data[MAX_STATUS];
};

struct feth_upl_result {					// Inst. or board config upload result
	unsigned char result; 				    // 0x00 = Good, 0x01 = Bad
};

struct feth_txctrl{ 						// Transmission control
	unsigned char mode; 					// Transmission mode
											// 0x01 = Enable ALL (data+status)
											// 0x02 = Enable STATUS only
											// 0x03 = Disable ALL
};

struct feth_f_ver{ 							// Ethernet board firmware versions (FLASH/FPGA)
	union
	{
		unsigned short version; 			// version of flash code
		struct { 
			unsigned char minor; 			// minor version
			unsigned char major; 			// major version
		} ;
	}flash;
	union
	{
		unsigned short version; 			// version of fpga code
		struct {
			unsigned char  minor; 			// minor version
			unsigned char major; 			// major version
		};
	}fpga;
};

struct feth_io_status{						// Instrument I/O status
	char ctype; 							// Continuation type: 1=Start, 2=Continued, 3=End, 4=Complete
	char reserved[9];						// Reserved
	unsigned char data[MAX_STATUS];
};

struct feth_ftp_info{						// Requested FTP login information
	char ftp_user[16];						// Current ftp login
	char ftp_pwd[16];						// Current ftp password
};

struct feth_new_ftp_info{					// Updated FTP login info
	char ftp_user[16]; 						// Current FTP login
	char ftp_pwd[16];						// Current FTP pwd
	char ftp_new_user[16];					// New FTP login
	char ftp_new_pwd[16];					// New FTP pwd
};

struct feth_board_new_ip { 					// New board IP address notification
	unsigned char ip_addr[4]; 				// new IP address
	unsigned char mac_addr[6]; 				// Device MAC address
};

struct feth_conn_stat{ 						// Board connection status
	char status; 							// Connection status: 0xAA->free 0x55->busy
	unsigned char mac_addr[6]; 				// Board MAC address
	unsigned short tcp_port; 				// port # for TCP connection
	};

struct feth_ftp_result {					// Result of updating FTP login information
	unsigned char result;					// 0x00 Accepted, 0x01 Refused, possibly because current info. doesn't match
};

struct Inst_info{							// Instrument list
	struct feth_conn_stat info;
	struct sockaddr_in saddr; 				// IP address
	struct ftir_config_block config; 		// inst. config.
	int valid; 								// Config info. valid
};

struct IN_HEADER{ 							// Header to all packet
	unsigned long signature;
	unsigned char command;
	unsigned short size;
};

struct OUT_FTIR_PACKET{ 					// Outgoing TCP packets (PC->D)

	struct IN_HEADER header;
	union
	{
		struct feth_command	command; 		// Command sent to ftir
		struct feth_config config;	 		// Ethernet board configuration
		struct feth_config_block bconfig; 	// instrument configuration
		struct feth_conn_info cinfo; 		// Post connection info
		struct feth_debug debug;			// Debug mode control
		struct feth_txctrl txctrl; 			// Transmission control
		struct feth_new_ftp_info ftpinfo;	// New FTP login information
		struct feth_ftp_result ftpres;		// FTP login info change result
		};
};

struct IN_TCP_FTIRPACKET{			 		// Incoming TCP packets (D->PC)
	struct IN_HEADER header;
	union{
		struct feth_data data;				// FTIR data
		struct feth_status status; 			// 256 bytes status
		struct feth_config config;			// Ethernet board configuration
		struct feth_upl_result uresult;		// Upload config result
		struct feth_f_ver firm_ver; 		// Board firmware versions
		struct feth_config_block bconfig;	// Instrument configuration
		struct feth_ftp_info ftpinfo;		// Current FTP login information
		struct feth_ftp_result ftpres;		// FTP login info change result
	};
};

struct IN_UDP_FTIRPACKET{ 					// Incoming UDP packets (D->PC)
	struct IN_HEADER header;
	union{
		struct feth_conn_stat c_status; 	// Board connection status
		struct feth_config_block bconfig;	// Instrument configuration
		struct feth_config config;			// Board configuration
		struct feth_board_new_ip new_b_ip;	// Board new IP address notification
		struct feth_pc_new_ip new_pc_ip; 	// pc new IP address notification
		struct feth_f_ver firm_ver; 		// Board firmware versions
	};
};

struct OUT_UDP_FTIRPACKET{					// Outgoing packets (PC->D)
	struct IN_HEADER header;
	struct feth_pc_new_ip new_ip; 			// Board new IP address notification

};

#pragma pack()

#endif
