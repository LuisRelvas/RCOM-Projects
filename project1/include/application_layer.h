// Application layer protocol header.
// NOTE: This file must not be changed.

#ifndef _APPLICATION_LAYER_H_
#define _APPLICATION_LAYER_H_

#include <stdio.h>

/**
 * Application layer for file transmission over a serial connection.
 *
 * This function is the main entry point for transmitting or receiving files over a serial connection
 * using the specified application layer configuration.
 *
 * @param serialPort The name of the serial port to use for the connection.
 * @param role       The role of the connection, "tx" for transmitter or "rx" for receiver.
 * @param baudRate   The baud rate for the serial connection.
 * @param nTries     The number of retransmissions in case of failure.
 * @param timeout    The timeout value for the connection.
 * @param filename   The name of the file to be transmitted or received.
 */
void applicationLayer(const char *serialPort, const char *role, int baudRate,
                      int nTries, int timeout, const char *filename);


/**
 * Create a control packet for transmission.
 *
 * This function constructs a control packet for transmission based on the specified type,
 * file name, and size. Control packets are used to mark the start or end of a file transfer.
 *
 * @param buf   A buffer to store the constructed control packet.
 * @param type  Type of control packet (0 for Start, 1 for End).
 * @param f     Pointer to the file name string.
 * @param size  Size of the file in bytes.
 *
 * @return The total size of the constructed control packet.
 */
int createControlPacket(unsigned char* buf, int type, char* f, int size);

/**
 * Read and parse a data packet.
 *
 * This function reads and parses a data packet stored in the input buffer `buf`,
 * extracting the sequence number and data. Data packets are used to transmit file
 * content during a file transfer.
 *
 * @param data buffer where the extracted data will be stored.
 * @param buf  buffer containing the data packet to be parsed.
 * @param seq  pointer to an integer where the extracted sequence number will be stored.
 *
 * @return The size of the extracted data on success, -1 if the input buffer does not contain a valid data packet.
 */
int readDataPacket(unsigned char* data, unsigned char* buf, int* seq);

/**
 * Read and parse a control packet.
 *
 * This function reads and parses a control packet stored in the input buffer `buf`,
 * extracting the filename and file size information. Control packets are used to mark
 * the start or end of a file transfer.
 *
 * @param buf      A buffer containing the control packet to be parsed.
 * @param filename A character array to store the extracted filename.
 * @param filesz   A pointer to an integer where the extracted file size will be stored.
 *
 * @return 0 on success, -1 if the input buffer does not contain a valid control packet.
 */
int readControlPacket(unsigned char* buf, char* filename, int* filesz);

/**
 * Create a data packet for transmission.
 *
 * This function constructs a data packet for transmission by populating the
 * provided buffer with the necessary information and data. The data packet
 * structure is as follows:
 *
 * Byte 0: Packet type (0x01 for data packets).
 * Byte 1: Sequence number.
 * Byte 2-3: Data size (big-endian representation).
 * Byte 4 and onwards: Actual data content.
 *
 * @param buf   A buffer to store the constructed data packet.
 * @param aux   Sequence number to be included in the packet (limited to 0-255).
 * @param size  Size of the data in bytes.
 * @param data  Pointer to the data to be included in the packet.
 *
 * @return The total size of the constructed data packet in bytes.
 */
int createDataPacket(unsigned char* buf, int aux, int size, unsigned char* data);

#endif // _APPLICATION_LAYER_H_
