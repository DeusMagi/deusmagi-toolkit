/**
 * @file
 * Packet API header file.
 *
 * @author Alex Tokar
 */

#ifndef TOOLKIT_PACKET_H
#define TOOLKIT_PACKET_H

#include "toolkit.h"
#include "stringbuffer_dec.h"
#include "packet_dec.h"

/**
 * A single data packet.
 */
struct packet_struct {
    /**
     * Next packet to send.
     */
    struct packet_struct *next;

    /**
     * Previous packet.
     */
    struct packet_struct *prev;

    /**
     * The data.
     */
    uint8_t *data;

    /**
     * Length of 'data'.
     */
    size_t len;

    /**
     * Current size of 'data'.
     */
    size_t size;

    /**
     * Expand size.
     */
    size_t expand;

    /**
     * Position in 'data'.
     */
    size_t pos;

    /**
     * Whether to enable NDELAY on this packet.
     */
    uint8_t ndelay;

    /**
     * The packet's command type.
     */
    uint8_t type;

#ifndef NDEBUG
    /**
     * StringBuffer instance used to describe the packet contents.
     */
    StringBuffer *sb;
#endif
};

/**
 * Structure used to save state of the packet so that one can go back to it.
 */
typedef struct packet_save {
    /**
     * Position to save.
     */
    size_t pos;

#ifndef NDEBUG
    /**
     * StringBuffer instance position to save.
     */
    size_t sb_pos;
#endif
} packet_save_t;

/**
 * How many packet structures to allocate when expanding the packets
 * memory pool.
 */
#define PACKET_EXPAND 10

#ifndef NDEBUG
#define packet_debug(_packet, _indent, _fmt, ...) \
    do { \
        stringbuffer_append_printf((_packet)->sb, "%*s" _fmt, (_indent), "", \
                                   ## __VA_ARGS__); \
    } while (0)
#define packet_debug_data(_packet, _indent, _fmt, ...) \
    packet_debug(_packet, _indent, _fmt ": ", ## __VA_ARGS__)
#else
#define packet_debug(_packet, _indent, _fmt, ...)
#define packet_debug_data(_packet, _indent, _fmt, ...)
#endif

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(packet);

void toolkit_packet_deinit(void);
packet_struct *packet_new(uint8_t type, size_t size, size_t expand);
void packet_free(packet_struct *packet);
void packet_compress(packet_struct *packet);
void packet_enable_ndelay(packet_struct *packet);
void packet_set_pos(packet_struct *packet, size_t pos);
size_t packet_get_pos(packet_struct *packet);
packet_struct *packet_dup(packet_struct *packet);
void packet_delete(packet_struct *packet, size_t pos, size_t len);
void packet_save(packet_struct *packet, packet_save_t *packet_save_buf);
void packet_load(packet_struct *packet, const packet_save_t *packet_save_buf);
char *packet_get_debug(packet_struct *packet);
void packet_append_uint8(packet_struct *packet, uint8_t data);
void packet_append_int8(packet_struct *packet, int8_t data);
void packet_append_uint16(packet_struct *packet, uint16_t data);
void packet_append_int16(packet_struct *packet, int16_t data);
void packet_append_uint32(packet_struct *packet, uint32_t data);
void packet_append_int32(packet_struct *packet, int32_t data);
void packet_append_uint64(packet_struct *packet, uint64_t data);
void packet_append_int64(packet_struct *packet, int64_t data);
void packet_append_float(packet_struct *packet, float data);
void packet_append_double(packet_struct *packet, double data);
void packet_append_data_len(packet_struct *packet, const uint8_t *data,
        size_t len);
void packet_append_string_len(packet_struct *packet, const char *data,
        size_t len);
void packet_append_string(packet_struct *packet, const char *data);
void packet_append_string_len_terminated(packet_struct *packet,
        const char *data, size_t len);
void packet_append_string_terminated(packet_struct *packet, const char *data);
void packet_append_packet(packet_struct *packet, packet_struct *src);
uint8_t packet_to_uint8(uint8_t *data, size_t len, size_t *pos);
int8_t packet_to_int8(uint8_t *data, size_t len, size_t *pos);
uint16_t packet_to_uint16(uint8_t *data, size_t len, size_t *pos);
int16_t packet_to_int16(uint8_t *data, size_t len, size_t *pos);
uint32_t packet_to_uint32(uint8_t *data, size_t len, size_t *pos);
int32_t packet_to_int32(uint8_t *data, size_t len, size_t *pos);
uint64_t packet_to_uint64(uint8_t *data, size_t len, size_t *pos);
int64_t packet_to_int64(uint8_t *data, size_t len, size_t *pos);
float packet_to_float(uint8_t *data, size_t len, size_t *pos);
double packet_to_double(uint8_t *data, size_t len, size_t *pos);
char *packet_to_string(uint8_t *data, size_t len, size_t *pos, char *dest,
        size_t dest_size);
void packet_to_stringbuffer(uint8_t *data, size_t len, size_t *pos,
        StringBuffer *sb);

#endif
