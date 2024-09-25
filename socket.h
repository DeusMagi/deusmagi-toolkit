/*************************************************************************
 *           Atrinik, a Multiplayer Online Role Playing Game             *
 *                                                                       *
 *   Copyright (C) 2009-2014 Alex Tokar and Atrinik Development Team     *
 *                                                                       *
 * Fork from Crossfire (Multiplayer game for X-windows).                 *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the Free Software           *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             *
 *                                                                       *
 * The author can be reached at admin@atrinik.org                        *
 ************************************************************************/

/**
 * @file
 * Socket API.
 */

#ifndef TOOLKIT_SOCKET_H
#define TOOLKIT_SOCKET_H

#include "toolkit.h"
#include "socket_crypto_dec.h"
#include "socket_dec.h"

/**
 * Commands used for sending data from client to server.
 */
enum {
    SERVER_CMD_CONTROL,
    SERVER_CMD_ASK_FACE,
    SERVER_CMD_SETUP,
    SERVER_CMD_VERSION,
    SERVER_CMD_CRYPTO,
    SERVER_CMD_CLEAR,
    SERVER_CMD_REQUEST_UPDATE,
    SERVER_CMD_KEEPALIVE,
    SERVER_CMD_ACCOUNT,
    SERVER_CMD_ITEM_EXAMINE,
    SERVER_CMD_ITEM_APPLY,
    SERVER_CMD_ITEM_MOVE,
    SERVER_CMD_ASK_RESOURCE,
    SERVER_CMD_PLAYER_CMD,
    SERVER_CMD_ITEM_LOCK,
    SERVER_CMD_ITEM_MARK,
    SERVER_CMD_FIRE,
    SERVER_CMD_QUICKSLOT,
    SERVER_CMD_QUESTLIST,
    SERVER_CMD_MOVE_PATH,
    SERVER_CMD_COMBAT,
    SERVER_CMD_TALK,
    SERVER_CMD_MOVE,
    SERVER_CMD_TARGET,

    SERVER_CMD_NROF
};

/**
 * All the possible socket commands.
 */
enum {
    CLIENT_CMD_MAP,
    CLIENT_CMD_DRAWINFO,
    CLIENT_CMD_FILE_UPDATE,
    CLIENT_CMD_ITEM,
    CLIENT_CMD_SOUND,
    CLIENT_CMD_TARGET,
    CLIENT_CMD_ITEM_UPDATE,
    CLIENT_CMD_ITEM_DELETE,
    CLIENT_CMD_STATS,
    CLIENT_CMD_IMAGE,
    CLIENT_CMD_ANIM,
    CLIENT_CMD_CRYPTO,
    CLIENT_CMD_PLAYER,
    CLIENT_CMD_MAPSTATS,
    CLIENT_CMD_RESOURCE,
    CLIENT_CMD_VERSION,
    CLIENT_CMD_SETUP,
    CLIENT_CMD_CONTROL,
    CLIENT_CMD_PAINTING,
    CLIENT_CMD_CHARACTERS,
    CLIENT_CMD_BOOK,
    CLIENT_CMD_PARTY,
    CLIENT_CMD_QUICKSLOT,
    CLIENT_CMD_COMPRESSED,
    /** @deprecated */
    CLIENT_CMD_REGION_MAP,
    CLIENT_CMD_SOUND_AMBIENT,
    CLIENT_CMD_INTERFACE,
    CLIENT_CMD_NOTIFICATION,
    CLIENT_CMD_KEEPALIVE,

    CLIENT_CMD_NROF
};

/**
 * Possible socket roles.
 */
typedef enum socket_role {
    SOCKET_ROLE_SERVER, ///< Client socket.
    SOCKET_ROLE_CLIENT, ///< Server socket.
} socket_role_t;

#define MAP_UPDATE_CMD_SAME 0
#define MAP_UPDATE_CMD_NEW 1
#define MAP_UPDATE_CMD_CONNECTED 2

/**
 * @defgroup CMD_TARGET_xxx Target command types
 * Target command types; informs the client about whether the target is a
 * friend, enemy, etc.
 *@{*/
/** Self (the player). */
#define CMD_TARGET_SELF 0
/** Enemy. */
#define CMD_TARGET_ENEMY 1
/** Neutral. */
#define CMD_TARGET_NEUTRAL 2
/** Friend. */
#define CMD_TARGET_FRIEND 3
/*@}*/

/**
 * @defgroup CMD_INTERFACE_xxx Interface command types
 * Interface command types.
 *@{*/
/** Text; the NPC message contents. */
#define CMD_INTERFACE_TEXT 0
/**
 * Link, follows the actual text, but is a special command in order to
 * support link shortcuts.
 */
#define CMD_INTERFACE_LINK 1
/** Icon; the image in the upper left corner square. */
#define CMD_INTERFACE_ICON 2
/** Title; text next to the icon. */
#define CMD_INTERFACE_TITLE 3
/**
 * If found in the command, will open the console with any text followed
 * by this.
 */
#define CMD_INTERFACE_INPUT 4
/**
 * Hidden text to prepend to the final text input string, when sent to
 * the NPC.
 */
#define CMD_INTERFACE_INPUT_PREPEND 5
/** Allow tabs to be entered. */
#define CMD_INTERFACE_ALLOW_TAB 6
/** Disable cleaning up text input. */
#define CMD_INTERFACE_INPUT_CLEANUP_DISABLE 7
/** Allow empty text input to be sent. */
#define CMD_INTERFACE_INPUT_ALLOW_EMPTY 8
/** Scroll to the bottom when the interface is created. */
#define CMD_INTERFACE_SCROLL_BOTTOM 9
/** Text to prefix for autocompletion of text. */
#define CMD_INTERFACE_AUTOCOMPLETE 10
/** Restore previous interface data. */
#define CMD_INTERFACE_RESTORE 11
/** Text to append to the existing text. */
#define CMD_INTERFACE_APPEND_TEXT 12
/** Animation; animated image in the upper left corner square. */
#define CMD_INTERFACE_ANIM 13
/** Virtual object. */
#define CMD_INTERFACE_OBJECT 14
/*@}*/

/**
 * @defgroup CMD_NOTIFICATION_xxx Notification command types
 * Notification command types.
 *@{*/
/** The notification contents. */
#define CMD_NOTIFICATION_TEXT 0
/** What macro or command to execute. */
#define CMD_NOTIFICATION_ACTION 1
/** Macro temporarily assigned to this notification. */
#define CMD_NOTIFICATION_SHORTCUT 2
/**
 * How many milliseconds must pass before the notification is
 * dismissed.
 */
#define CMD_NOTIFICATION_DELAY 3
/*@}*/

/**
 * @defgroup CMD_SETUP_xxx Setup command types
 * Setup command types
 *@{*/
/** Enable/disable sound. */
#define CMD_SETUP_SOUND 0
/**  Set the map size. */
#define CMD_SETUP_MAPSIZE 1
/** Enable/disable bot flag. */
#define CMD_SETUP_BOT 2
/** URL of the data files to use. */
#define CMD_SETUP_DATA_URL 3
/*@}*/

/**
 * @defgroup CMD_QUERY_xxx Query command types
 * Query command types.
 *@{*/
/** Get character name. */
#define CMD_QUERY_GET_NAME 1
/** Get character password. */
#define CMD_QUERY_GET_PASSWORD 2
/** Confirm password for character creation. */
#define CMD_QUERY_CONFIRM_PASSWORD 3
/*@}*/

/**
 * @defgroup MAP2_FLAG_xxx Map2 layer flags
 * Flags used to mark what kind of data there is on layers
 * in map2 protocol.
 *@{*/
/** Multi-arch object. */
#define MAP2_FLAG_MULTI      1
/** Player name. */
#define MAP2_FLAG_NAME       2
/** Animation instead of a face. */
#define MAP2_FLAG_ANIMATION  4
/** Tile's Z position. */
#define MAP2_FLAG_HEIGHT     8
/** The object should be highlighted in red. */
#define MAP2_FLAG_INFRAVISION 16
/** X align. */
#define MAP2_FLAG_ALIGN 32
/** Draw the object twice. */
#define MAP2_FLAG_DOUBLE 64
/** More flags from @ref MAP2_FLAG2_xxx. */
#define MAP2_FLAG_MORE 128
/*@}*/

/**
 * @defgroup MAP2_FLAG2_xxx Extended map2 layer flags
 * Extended flags used to mark what kind of data there is on layers
 * in map2 protocol.
 *@{*/
/** Custom alpha value. */
#define MAP2_FLAG2_ALPHA 1
/** Custom rotate value in degrees. */
#define MAP2_FLAG2_ROTATE 2
/** Zoom. */
#define MAP2_FLAG2_ZOOM 4
/** Possible target. */
#define MAP2_FLAG2_TARGET 8
/** Target's HP bar. */
#define MAP2_FLAG2_PROBE 16
/** Priority rendering. */
#define MAP2_FLAG2_PRIORITY 32
/** Second alpha pass rendering. */
#define MAP2_FLAG2_SECONDPASS 64
/** The object glows. */
#define MAP2_FLAG2_GLOW 128
/*@}*/

/**
 * @defgroup MAP2_FLAG_EXT_xxx Map2 tile flags
 * Flags used to mark what kind of data there is on different
 * tiles in map2 protocol.
 *@{*/
/** An animation. */
#define MAP2_FLAG_EXT_ANIM   1
/*@}*/

/**
 * @defgroup ANIM_xxx Animation types
 * Animation types.
 *@{*/
/** Damage animation. */
#define ANIM_DAMAGE     1
/** Kill animation. */
#define ANIM_KILL       2
/*@}*/

/**
 * @defgroup MAP2_MASK_xxx Map2 mask flags
 * Flags used for masks in map2 protocol.
 *@{*/
/** Clear cell, with all layers. */
#define MAP2_MASK_CLEAR      0x2
#define MAP2_MASK_DARKNESS 0x4
#define MAP2_MASK_DARKNESS_MORE 0x8
/*@}*/

/**
 * @defgroup MAP2_LAYER_xxx Map2 layer types
 *@{*/
/** Clear this layer. */
#define MAP2_LAYER_CLEAR    255
/*@}*/

/**
 * @defgroup CMD_MAPSTATS_xxx Mapstats command types
 * Mapstats command types.
 *@{*/
/** Change map name. */
#define CMD_MAPSTATS_NAME 1
/** Change map music. */
#define CMD_MAPSTATS_MUSIC 2
/** Change map weather. */
#define CMD_MAPSTATS_WEATHER 3
/** Text animation. */
#define CMD_MAPSTATS_TEXT_ANIM 4
/*@}*/

/**
 * @defgroup CMD_SOUND_xxx Sound command types
 * The sound command types.
 *@{*/
/** A sound effect, like poison, melee/range hit, spell sound, etc. */
#define CMD_SOUND_EFFECT 1
/** Background music. */
#define CMD_SOUND_BACKGROUND 2
/** Path to sound effect with an absolute filename. MIDI is not supported. */
#define CMD_SOUND_ABSOLUTE 3
/*@}*/

/**
 * @defgroup CMD_TARGET_xxx Target command types
 * Target command types.
 *@{*/
/**
 * Target something at the specified X/Y position on the map.
 */
#define CMD_TARGET_MAPXY 1
/**
 * Clear target.
 */
#define CMD_TARGET_CLEAR 2
/*@}*/

/**
 * @defgroup CMD_ACCOUNT_xxx Account command types
 * Account command types.
 *@{*/
/**
 * Login as the specified account.
 */
#define CMD_ACCOUNT_LOGIN 1
/**
 * Create the specified account.
 */
#define CMD_ACCOUNT_REGISTER 2
/**
 * Login with a character.
 */
#define CMD_ACCOUNT_LOGIN_CHAR 3
/**
 * Create a new character.
 */
#define CMD_ACCOUNT_NEW_CHAR 4
/**
 * Change the current account's password.
 */
#define CMD_ACCOUNT_PSWD 5
/*@}*/

/**
 * @defgroup COLOR_xxx Color HTML notations
 * HTML notations of various common collors.
 *@{*/
/** White. */
#define COLOR_WHITE "ffffff"
/** Orange. */
#define COLOR_ORANGE "ff9900"
/** Navy (most used for NPC messages). */
#define COLOR_NAVY "00ffff"
/** Red. */
#define COLOR_RED "ff3030"
/** Green. */
#define COLOR_GREEN "00ff00"
/** Blue. */
#define COLOR_BLUE "0080ff"
/** Gray. */
#define COLOR_GRAY "999999"
/** Brown. */
#define COLOR_BROWN "c07f40"
/** Purple. */
#define COLOR_PURPLE "cc66ff"
/** Pink. */
#define COLOR_PINK "ff9999"
/** Yellow. */
#define COLOR_YELLOW "ffff33"
/** Dark navy. */
#define COLOR_DK_NAVY "00c4c2"
/** Dark green. */
#define COLOR_DK_GREEN "006600"
/** Dark orange. */
#define COLOR_DK_ORANGE "ff6600"
/** Bright purple. */
#define COLOR_BRIGHT_PURPLE "ff66ff"
/** Gold. */
#define COLOR_HGOLD "d4d553"
/** Dark gold. */
#define COLOR_DGOLD "999900"
/** Black. */
#define COLOR_BLACK "000000"
/*@}*/

/**
 * @defgroup NDI_xxx New draw info flags
 * Various flags for draw_info().
 *@{*/
/** Say command. */
#define NDI_SAY 0x0100
/** The message is a shout. */
#define NDI_SHOUT 0x0200
/** The message is a tell. */
#define NDI_TELL 0x0400
/** This message comes from a player. */
#define NDI_PLAYER 0x0800
/** Message is an emote command. */
#define NDI_EMOTE 0x01000
/**
 * Message will be played as animation in the middle of the client
 * screen.
 */
#define NDI_ANIM 0x02000
/** Inform all players of this message. */
#define NDI_ALL 0x20000
/*@}*/

/**
 * @defgroup CS_FLAG_xxx Client/server item flags
 * Flags for the item command. Used in query_flags().
 *@{*/
/**
 * The item is applied.
 */
#define CS_FLAG_APPLIED 1
/**
 * The item is unpaid.
 */
#define CS_FLAG_UNPAID 2
/**
 * The item is magical.
 */
#define CS_FLAG_IS_MAGICAL 4
/**
 * The item is cursed.
 */
#define CS_FLAG_CURSED 8
/**
 * The item is damned.
 */
#define CS_FLAG_DAMNED 16
/**
 * The item is an opened container.
 */
#define CS_FLAG_CONTAINER_OPEN 32
/**
 * The item is locked.
 */
#define CS_FLAG_LOCKED 64
/**
 * The item is trapped.
 */
#define CS_FLAG_IS_TRAPPED 128
/**
 * The item is a two-handed weapon.
 */
#define CS_FLAG_WEAPON_2H 256
/*@}*/

/**
 * @defgroup UPD_XXX Item update flags
 * Client/server item update flags.
 *@{*/
/** Update ID location where this object is. */
#define UPD_LOCATION 1
/** Update object's flags. */
#define UPD_FLAGS 2
/** Update object's weight. */
#define UPD_WEIGHT 4
/** Update object's face. */
#define UPD_FACE 8
/** Update object's name. */
#define UPD_NAME 16
/** Update object's animation. */
#define UPD_ANIM 32
/** Update object's animation speed. */
#define UPD_ANIMSPEED 64
/** Update object's nrof. */
#define UPD_NROF 128
/** Update object's facing direction. */
#define UPD_DIRECTION 256
/** Update object's type, subtype, qua/con, level and skill. */
#define UPD_TYPE 512
/** Extra data, such as spell/skill data. */
#define UPD_EXTRA 1024
/** Item glow. */
#define UPD_GLOW 2048
/*@}*/

/**
 * @defgroup CS_STAT_xx Client/server stats
 * IDs for the various stats that get sent across.
 *@{*/
#define CS_STAT_HP              1
#define CS_STAT_MAXHP           2
#define CS_STAT_SP              3
#define CS_STAT_MAXSP           4
#define CS_STAT_STR             5
#define CS_STAT_DEX             6
#define CS_STAT_CON             7
#define CS_STAT_INT             8
#define CS_STAT_POW             9
#define CS_STAT_EXP             11
#define CS_STAT_LEVEL           12
#define CS_STAT_WC              13
#define CS_STAT_AC              14
#define CS_STAT_DAM             15
#define CS_STAT_ARMOUR          16
#define CS_STAT_SPEED           17
#define CS_STAT_FOOD            18
#define CS_STAT_WEAPON_SPEED    19
#define CS_STAT_RANGE           20
#define CS_STAT_TITLE           21
#define CS_STAT_FLAGS           25
#define CS_STAT_WEIGHT_LIM      26
#define CS_STAT_REG_HP          28
#define CS_STAT_REG_MANA        29
#define CS_STAT_TARGET_HP       31

#define CS_STAT_GENDER 35
#define CS_STAT_ACTION_TIME 36
#define CS_STAT_RANGED_DAM 37
#define CS_STAT_RANGED_WC 38
#define CS_STAT_RANGED_WS 39
#define CS_STAT_PATH_ATTUNED 40
#define CS_STAT_PATH_REPELLED 41
#define CS_STAT_PATH_DENIED 42

#define CS_STAT_RESIST_START    100
#define CS_STAT_RESIST_END      117
#define CS_STAT_RES_PHYS        100
#define CS_STAT_RES_MAG         101
#define CS_STAT_RES_FIRE        102
#define CS_STAT_RES_ELEC        103
#define CS_STAT_RES_COLD        104
#define CS_STAT_RES_CONF        105
#define CS_STAT_RES_ACID        106
#define CS_STAT_RES_DRAIN       107
#define CS_STAT_RES_GHOSTHIT    108
#define CS_STAT_RES_POISON      109
#define CS_STAT_RES_SLOW        110
#define CS_STAT_RES_PARA        111
#define CS_STAT_TIME            112
#define CS_STAT_RES_FEAR        113
#define CS_STAT_RES_DEPLETE     114
#define CS_STAT_RES_DEATH       115
#define CS_STAT_RES_HOLYWORD    116
#define CS_STAT_RES_BLIND       117

#define CS_STAT_EQUIP_START 100
#define CS_STAT_EQUIP_END 116

#define CS_STAT_PROT_START 130
#define CS_STAT_PROT_END 149
/*@}*/

/**
 * @defgroup cs_state_flags Client/server state flags
 * These are used with @ref CS_STAT_FLAGS to determine the
 * server thinks the fire-on and run-on states are.
 *@{*/
#define SF_FIREON           1
#define SF_RUNON            2
#define SF_BLIND            4
#define SF_XRAYS            8
#define SF_INFRAVISION      16
/*@}*/

/**
 * @defgroup map_face_flags Map face flags
 * These are the 'face flags' we grab out of the flags object structure
 * 1:1.
 *
 * We use a macro to get them from the object, doing it fast AND to mask the
 * bigger
 * object flags to uint8.
 *@{*/

/** Object is sleeping */
#define FFLAG_SLEEP     0x01
/** Object is confused */
#define FFLAG_CONFUSED  0x02
/** Object is paralyzed */
#define FFLAG_PARALYZED 0x04
/** Object is scared - it will run away */
#define FFLAG_SCARED    0x08
/** Object is blinded */
#define FFLAG_BLINDED   0x10
/** Object is invisible (can be seen with "see invisible" on) */
#define FFLAG_INVISIBLE 0x20
/** Object is ethereal */
#define FFLAG_ETHEREAL  0x40
/** Object is probed */
#define FFLAG_PROBE     0x80
/*@}*/

/**
 * @defgroup anim_flags Animation flags
 * Used to indicate what stage the animation is in.
 *@{*/
#define ANIM_FLAG_MOVING 0x01 ///< Moving.
#define ANIM_FLAG_ATTACKING 0x02 ///< Attacking.
#define ANIM_FLAG_STOP_MOVING 0x04 ///< Stop moving.
#define ANIM_FLAG_STOP_ATTACKING 0x08 ///< Stop attacking.
/*@}*/

/**
 * @defgroup CHAT_TYPE_xxx Chat types
 * Chat types.
 *@{*/
#define CHAT_TYPE_ALL 1 ///< Goes to the 'all' tab window.
#define CHAT_TYPE_GAME 2 ///< Game-related messages (eg, examine output)
#define CHAT_TYPE_CHAT 3 ///< Player chat.
#define CHAT_TYPE_LOCAL 4 ///< Local map chat.
#define CHAT_TYPE_PRIVATE 5 ///< Private chat (/tell)
#define CHAT_TYPE_GUILD 6 ///< Guild chat.
#define CHAT_TYPE_PARTY 7 ///< Party chat.
#define CHAT_TYPE_OPERATOR 8 ///< Operator-only chat.
/*@}*/

#define CMD_TALK_NPC 1
#define CMD_TALK_INV 2
#define CMD_TALK_BELOW 3
#define CMD_TALK_CONTAINER 4
#define CMD_TALK_NPC_NAME 5
#define CMD_TALK_CLOSE 6

/**
 * @defgroup CMD_CONTROL_xxx Control command types
 *@{*/
/**
 * Control command concerning a map.
 */
#define CMD_CONTROL_MAP 1
/**
 * Control command concerning a player.
 */
#define CMD_CONTROL_PLAYER 2
/*@}*/


/**
 * @defgroup CMD_CONTROL_MAP_xxx Map control command types
 *@{*/
/**
 * Reset the specified map.
 */
#define CMD_CONTROL_MAP_RESET 1
/*@}*/

/**
 * @defgroup CMD_CONTROL_PLAYER_xxx Player control command types
 *@{*/
/**
 * Teleport player to the specified map.
 */
#define CMD_CONTROL_PLAYER_TELEPORT 1
/*@}*/

/**
 * @defgroup CMD_APPLY_ACTION_xxx Apply action types
 * Used for special handling of the apply command.
 *@{*/
#define CMD_APPLY_ACTION_NORMAL 0 ///< Normal apply. Not transmitted.
#define CMD_APPLY_ACTION_NONE 1 ///< No action.
#define CMD_APPLY_ACTION_BELOW_NEXT 2 ///< Next group of items.
#define CMD_APPLY_ACTION_BELOW_PREV 3 ///< Previous group of items.
/*@}*/

/**
 * @defgroup CMD_CRYPTO_xxx Crypto command types
 * Used to create different sub-commands for the crypto command.
 *@{*/
/**
 * The hello sub-command.
 *
 * This is the ONLY command in the exchange that is not encrypted, and is
 * merely used to begin the crypto exchange.
 *
 * The client sends this command, containing zero bytes of data *or* an X509
 * certificate to be authenticated against, to the server, which responds
 * with its own X509 certificate.
 */
#define CMD_CRYPTO_HELLO 1
/**
 * The key sub-command.
 *
 * Client exchanges key to use for AES encryption with the server, until such
 * a time as the ECDH keys are derived.
 *
 * The client will also include an IV buffer of variable size that the server
 * must store (for its own AES encryption/decryption) and replicate in its key
 * response (which will be encrypted with the received key).
 *
 * Client encrypts this with the server's public key.
 */
#define CMD_CRYPTO_KEY 2
/**
 * The curves sub-command. Establishes elliptic curve to use.
 *
 * The client uses this to inform the server about the list of curves it
 * supports. It is an error if the server receives an empty set, and MUST
 * close the connection immediately. The server MUST choose one of the
 * curves to use; if it doesn't support any in the set, the connection MUST
 * be terminated immediately.
 *
 * In turn, the server sends the chosen curve to use to the client. The client
 * MUST verify that it supports the given curve, and that a curve was, in fact,
 * provided in the hello message. It is an error if the client cannot select a
 * usable curve and MUST terminate the connection immediately.
 *
 * Encrypted with AES and the previously agreed-upon key.
 */
#define CMD_CRYPTO_CURVES 3
/**
 * The pubkey sub-command. Exchanges ECDH public keys.
 *
 * Client and server both use this command to exchange their public keys with
 * each other, and to subsequently derive the shared secret key.
 *
 * Both sides also exchange IV buffers to use for AES and they locally combine
 * them.
 *
 * This communication is also encrypted with AES and the previously
 * agreed-upon key.
 */
#define CMD_CRYPTO_PUBKEY 4
/**
 * The secret sub-command. Sets a secret key to use for checksums.
 *
 * The client uses this to inform the server about the secret key (a salt)
 * to use for protocol message checksums, and the other way around.
 */
#define CMD_CRYPTO_SECRET 5
/**
 * The done sub-command. This command indicates a successful crypto handshake,
 * and marks the connection ready for receiving/sending Atrinik game data.
 */
#define CMD_CRYPTO_DONE 6
/*@}*/

/**
 * Player equipment.
 * @anchor PLAYER_EQUIP_xxx
 */
enum {
    /**
     * Ammunition.
     */
    PLAYER_EQUIP_AMMO,
    /**
     * Amulet.
     */
    PLAYER_EQUIP_AMULET,
    /**
     * Weapon.
     */
    PLAYER_EQUIP_WEAPON,
    /**
     * Shield.
     */
    PLAYER_EQUIP_SHIELD,
    /**
     * Gauntlets.
     */
    PLAYER_EQUIP_GAUNTLETS,
    /**
     * Right ring.
     */
    PLAYER_EQUIP_RING_RIGHT,
    /**
     * Helm.
     */
    PLAYER_EQUIP_HELM,
    /**
     * Armor.
     */
    PLAYER_EQUIP_ARMOUR,
    /**
     * Belt.
     */
    PLAYER_EQUIP_BELT,
    /**
     * Pants.
     */
    PLAYER_EQUIP_PANTS,
    /**
     * Boots.
     */
    PLAYER_EQUIP_BOOTS,
    /**
     * Cloak.
     */
    PLAYER_EQUIP_CLOAK,
    /**
     * Bracers.
     */
    PLAYER_EQUIP_BRACERS,
    /**
     * Ranged weapon.
     */
    PLAYER_EQUIP_WEAPON_RANGED,
    /**
     * Light (lantern, torch).
     */
    PLAYER_EQUIP_LIGHT,
    /**
     * Left ring.
     */
    PLAYER_EQUIP_RING_LEFT,
    /**
     * Skill item.
     */
    PLAYER_EQUIP_SKILL_ITEM,

    /**
     * Maximum number of equipment.
     */
    PLAYER_EQUIP_MAX
};

/**
 * Timeout when attempting a connection in seconds.
 */
#define SOCKET_TIMEOUT_MS 30.0

#ifdef WIN32
static inline const char *s_strerror(int val)
{
    wchar_t *s = NULL;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS, NULL, val,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR) &s, 0, NULL);
    static char buf[4096];
    int end = snprintf(buf, sizeof(buf), "%S", s);
    if (end > 0) {
        for (int i = end - 1; i >= 0; i--) {
            if (buf[i] != '\n' && buf[i] != '\r') {
                break;
            }

            buf[i] = '\0';
        }
    }
    LocalFree(s);
    return buf;
}
#define s_errno WSAGetLastError()
#else
#define s_strerror(_val) strerror(_val)
#define s_errno errno
#endif

/* Prototypes */

TOOLKIT_FUNCS_DECLARE(socket);

socket_t *
socket_create(const char   *host,
              uint16_t      port,
              bool          secure,
              socket_role_t role,
              bool          dual_stack);
char *socket_get_addr(socket_t *sc);
char *socket_get_str(socket_t *sc);
int socket_cmp_addr(socket_t *sc, const struct sockaddr_storage *addr,
        unsigned short plen);
bool socket_connect(socket_t *sc);
int socket_fd(socket_t *sc);
bool socket_bind(socket_t *sc);
socket_t *socket_accept(socket_t *sc);
bool socket_read(socket_t *sc, void *buf, size_t len, size_t *amt);
bool socket_write(socket_t *sc, const void *buf, size_t len, size_t *amt);
bool socket_is_fd_valid(socket_t *sc);
bool socket_opt_linger(socket_t *sc, bool enable, unsigned short linger);
bool socket_opt_reuse_addr(socket_t *sc, bool enable);
bool socket_opt_non_blocking(socket_t *sc, bool enable);
bool socket_opt_ndelay(socket_t *sc, bool enable);
bool socket_opt_send_buffer(socket_t *sc, int bufsize);
bool socket_opt_recv_buffer(socket_t *sc, int bufsize);
void socket_destroy(socket_t *sc);
void socket_close(socket_t *sc);
bool socket_host2addr(const char *host, struct sockaddr_storage *addr);
const char *socket_addr2host(const struct sockaddr_storage *addr, char *buf,
        size_t bufsize);
unsigned short socket_addr_plen(const struct sockaddr_storage *addr);
int socket_addr_cmp(const struct sockaddr_storage *a,
        const struct sockaddr_storage *b, unsigned short plen);
void
socket_set_crypto(socket_t *sc, socket_crypto_t *crypto);
socket_crypto_t *
socket_get_crypto(socket_t *sc);
const char *
socket_get_host(socket_t *sc);
bool
socket_is_secure(socket_t *sc);
socket_role_t
socket_get_role(socket_t *sc);

#endif
