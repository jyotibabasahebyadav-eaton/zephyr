/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Max settings key length (with all components) */
#define BT_SETTINGS_KEY_MAX 36

/* Base64-encoded string buffer size of in_size bytes */
#define BT_SETTINGS_SIZE(in_size) ((((((in_size) - 1) / 3) * 4) + 4) + 1)

#define ASCII_MAX (0x7E) /* ASCII of TILDE */
#define ASCII_MIN (0X21) /* ASCII of EXCLAMATION */
#define RAW_UID(X) (ASCII_MAX & (X ^ 0xFF))
#define ASCII_UID(X) ((RAW_UID(X) < ASCII_MIN) ? (RAW_UID(X) | ASCII_MIN) : RAW_UID(X))
#define ID_CHAR(Y, Z) (ASCII_UID(Y ^ Z)) /* Identification Character */

typedef enum {
	eMAC_INDEX_0 = 0,
	eMAC_INDEX_1 = 1,
	eMAC_INDEX_2 = 2,
	eMAC_INDEX_3 = 3,
	eMAC_INDEX_4 = 4,
	eMAC_INDEX_5 = 5,
	eMAC_SIZE = 6
} eMAC_INDEX;

typedef struct RandomEncryptedString {
	uint8_t u8UIDUpper;      /* UID Upper 1 Byte */
	uint8_t u8DeviceType;    /* Device Type 1 Byte */
	uint8_t u8IDChar;		 /* ID Char 1 Byte */
	uint8_t u8CC2String[24]; /* Champ Connected 2 String = 24 Bytes */
	uint8_t u8UIDLower[2];   /* UID Lower 2 Byte */
} RandomEncryptedString;

/* Helpers for keys containing a bdaddr */
void bt_settings_encode_key(char *path, size_t path_size, const char *subsys,
			    const bt_addr_le_t *addr, const char *key);
int bt_settings_decode_key(const char *key, bt_addr_le_t *addr);

void bt_settings_save_id(void);

int bt_settings_init(void);

inline void EncryptChampConnected2Hash(uint8_t u8IDChar, int8_t *const i8ConstStringFromHashCopy);
