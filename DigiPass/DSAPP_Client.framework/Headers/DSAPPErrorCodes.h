//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef DSAPPERRORCODES_H_
#define DSAPPERRORCODES_H_

/**
 * Error codes which can be returned by the DSAPP library in case of error.
 */

/** Internal error */
const int DSAPPErrorCodes_INTERNAL_ERROR = -4501;

/** Activation password too long. Limited to {@link DSAPPConstants_SHARED_DATA_MAX_LENGTH} characters. */
const int DSAPPErrorCodes_ACTIVATION_PASSWORD_TOO_LONG = -4502;

/** CHS key null or empty. Must be a {@link DSAPPConstants_CHS_KEY_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_CHS_KEY_NULL_OR_EMPTY = -4503;

/** Incorrect CHS key length. Must be a {@link DSAPPConstants_CHS_KEY_LENGTH} hexadecimal string.*/
const int DSAPPErrorCodes_CHS_KEY_INCORRECT_LENGTH = -4504;

/** Incorrect CHS key format. Must be a {@link DSAPPConstants_CHS_KEY_LENGTH} hexadecimal string.*/
const int DSAPPErrorCodes_CHS_KEY_INCORRECT_FORMAT = -4505;

/** Client private key null or empty. Must be a {@link DSAPPConstants_PRIVATE_KEY_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_CLIENT_PRIVATE_KEY_NULL_OR_EMPTY = -4506;

/** Incorrect Client private key length. Must be a {@link DSAPPConstants_PRIVATE_KEY_LENGTH} hexadecimal string.*/
const int DSAPPErrorCodes_CLIENT_PRIVATE_KEY_INCORRECT_LENGTH = -4507;

/** Incorrect Client private key format. Must be a {@link DSAPPConstants_PRIVATE_KEY_LENGTH} hexadecimal string.*/
const int DSAPPErrorCodes_CLIENT_PRIVATE_KEY_INCORRECT_FORMAT = -4508;

/** Encrypted server public key null or empty. Must be a {@link DSAPPConstants_PUBLIC_KEY_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_ENCRYPTED_SERVER_PUBLIC_KEY_NULL_OR_EMPTY = -4509;

/** Incorrect Encrypted server public key length. Must be a {@link DSAPPConstants_PUBLIC_KEY_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_ENCRYPTED_SERVER_PUBLIC_KEY_INCORRECT_LENGTH = -4510;

/** Incorrect Encrypted server public key format. Must be a {@link DSAPPConstants_PUBLIC_KEY_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_ENCRYPTED_SERVER_PUBLIC_KEY_INCORRECT_FORMAT = -4511;

/** Encrypted nonces null or empty. Must be a {@link DSAPPConstants_ENCRYPTED_NONCES_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_ENCRYPTED_NONCES_NULL_OR_EMPTY = -4512;

/** Incorrect Encrypted nonces length. Must be a {@link DSAPPConstants_ENCRYPTED_NONCES_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_ENCRYPTED_NONCES_INCORRECT_LENGTH = -4513;

/** Incorrect Encrypted nonces format. Must be a {@link DSAPPConstants_ENCRYPTED_NONCES_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_ENCRYPTED_NONCES_INCORRECT_FORMAT = -4514;

/** Client nonce null or empty. Must be a {@link DSAPPConstants_NONCE_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_CLIENT_NONCE_NULL_OR_EMPTY = -4515;

/** Incorrect Client nonce length. Must be a {@link DSAPPConstants_NONCE_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_CLIENT_NONCE_INCORRECT_LENGTH = -4516;

/** Incorrect Client nonce format. Must be a {@link DSAPPConstants_NONCE_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_CLIENT_NONCE_INCORRECT_FORMAT = -4517;

/** XFAD null or empty. Must be an hexadecimal string. */
const int DSAPPErrorCodes_XFAD_NULL_OR_EMPTY = -4518;

/** Incorrect XFAD format. Must be an hexadecimal string. */
const int DSAPPErrorCodes_XFAD_INCORRECT_FORMAT = -4519;

/** Incorrect XERC format. Must be an hexadecimal string. */
const int DSAPPErrorCodes_XERC_INCORRECT_FORMAT = -4520;

/** Server initial vector null or empty. Must be a {@link DSAPPConstants_INITIAL_VECTOR_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_SERVER_INITIAL_VECTOR_NULL_OR_EMPTY = -4521;

/** Incorrect Server initial vector length. Must be a {@link DSAPPConstants_INITIAL_VECTOR_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_SERVER_INITIAL_VECTOR_INCORRECT_LENGTH = -4522;

/** Incorrect Server initial vector format. Must be a {@link DSAPPConstants_INITIAL_VECTOR_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_SERVER_INITIAL_VECTOR_INCORRECT_FORMAT = -4523;

/** Error while checking the nonce: the decrypted nonce is not equal to the nonce which is provided in parameter.<br/> 
  * This error occured when the decryption of activation data is not done correctly. It might be due to a different shared secret between server and client.*/
const int DSAPPErrorCodes_CHECK_NONCE_ERROR = -4524;

/** Shared data length null or empty */
const int DSAPPErrorCodes_SHARED_DATA_NULL_OR_EMPTY = -4525;

/** Shared data length too short. Min length is {@link DSAPPConstants_SHARED_DATA_MIN_LENGTH}. */
const int DSAPPErrorCodes_SHARED_DATA_LENGTH_TOO_SHORT = -4526;

/** Shared data length too long. Max length is {@link DSAPPConstants_SHARED_DATA_MAX_LENGTH}.*/
const int DSAPPErrorCodes_SHARED_DATA_LENGTH_TOO_LONG = -4527;

/** The checksum cannot be validated. */
const int DSAPPErrorCodes_CHECKSUM_VALIDATION_FAILED = -4528;

/** Null or empty session key. It must be a {@link DSAPPConstants_SESSION_KEY_LENGTH} hexadecimal string.  */
const int DSAPPErrorCodes_SESSION_KEY_NULL_OR_EMPTY = -4529;

/** Incorrect session key length. It must be a {@link DSAPPConstants_SESSION_KEY_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_SESSION_KEY_INCORRECT_LENGTH = -4530;

/** Incorrect session key format. It must be a {@link DSAPPConstants_SESSION_KEY_LENGTH} hexadecimal string. */
const int DSAPPErrorCodes_SESSION_KEY_INCORRECT_FORMAT = -4531;

/** Encrypted data null or empty. Must be a hexadecimal string. */
const int DSAPPErrorCodes_ENCRYPTED_DATA_NULL_OR_EMPTY = -4532;

/** Incorrect encrypted data format. Must be a hexadecimal string.*/
const int DSAPPErrorCodes_ENCRYPTED_DATA_INCORRECT_FORMAT = -4533;

/** NULL decrypted data buffer length address. */
const int DSAPPErrorCodes_DECRYPTED_DATA_LENGTH_NULL = -4534;

/** NULL decrypted data buffer. */
const int DSAPPErrorCodes_DECRYPTED_DATA_NULL = -4535;

/** Decrypted data buffer too small. */
const int DSAPPErrorCodes_DECRYPTED_DATA_LENGTH_TOO_SMALL = -4536;

/** Shared secret too long. Limited to {@link DSAPPConstants_SHARED_DATA_MAX_LENGTH} characters. */
const int DSAPPErrorCodes_SHARED_SECRET_TOO_LONG = -4537;

/** Shared secret too long. Limited to {@link DSAPPConstants_SHARED_DATA_MAX_LENGTH} characters. */
const int DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_NULL_OR_EMPTY = -5700;

/** Client ephemeral key too long. Limited to {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} characters */
const int DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INCORRECT_LENGTH = -5701;

/** Client ephemeral key invalid */
const int DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INVALID = -5702;

/** Client ephemeral key incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INCORRECT_FORMAT = -5703;

/** User identifier null or empty */
const int DSAPPErrorCodes_SRP_USER_ID_NULL_OR_EMPTY = -5704;

/** User identifier too long or too short. Limited to between {@link DSAPPConstants_SRP_USER_ID_MIN_LENGTH} and {@link DSAPPConstants_SRP_USER_ID_MAX_LENGTH} characters  */
const int DSAPPErrorCodes_SRP_USER_ID_INCORRECT_LENGTH = -5705;

/** PAssword null or empty */
const int DSAPPErrorCodes_SRP_PASSWORD_NULL_OR_EMPTY = -5706;

/** Password too long or too short. Limited to between {@link DSAPPConstants_SRP_PWD_MIN_LENGTH} and {@link DSAPPConstants_SRP_PWD_MAX_LENGTH} characters  */
const int DSAPPErrorCodes_SRP_PASSWORD_INCORRECT_LENGTH = -5707;

/** Salt null or empty */
const int DSAPPErrorCodes_SRP_SALT_NULL_OR_EMPTY = -5708;

/** Salt incorrect length. Length must be {@link DSAPPConstants_SRP_SALT_LENGTH} characters */
const int DSAPPErrorCodes_SRP_SALT_INCORRECT_LENGTH = -5709;

/** Salt incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_SALT_INCORRECT_FORMAT = -5710;

/** Server ephemeral key null or empty */
const int DSAPPErrorCodes_SRP_SERVER_EPHEMERAL_KEY_NULL_OR_EMPTY = -5711;

/** Server ephemeral key too long. Limited to {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} characters */
const int DSAPPErrorCodes_SRP_SERVER_EPHEMERAL_KEY_INCORRECT_LENGTH = -5712;

/** Server ephemeral key invalid */
const int DSAPPErrorCodes_SRP_SERVER_EPHEMERAL_KEY_INVALID = -5713;

/** Server ephemeral key incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_SERVER_EPHEMERAL_KEY_INCORRECT_FORMAT = -5714;

/** Client private key null or empty */
const int DSAPPErrorCodes_SRP_CLIENT_PRIVATE_KEY_NULL_OR_EMPTY = -5715;

/** Client private key too long. Limited to {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} characters */
const int DSAPPErrorCodes_SRP_CLIENT_PRIVATE_KEY_INCORRECT_LENGTH = -5716;

/** Client private key invalid. It does not match client ephemeral key */
const int DSAPPErrorCodes_SRP_CLIENT_PRIVATE_KEY_INVALID = -5717;

/** Client private key incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_CLIENT_PRIVATE_KEY_INCORRECT_FORMAT = -5718;

/** Session key null or empty */
const int DSAPPErrorCodes_SRP_SESSION_KEY_NULL_OR_EMPTY = -5719;

/** Session key incorrect length. Length must be {@link DSAPPConstants_SRP_SESSION_KEY_LENGTH} characters */
const int DSAPPErrorCodes_SRP_SESSION_KEY_INCORRECT_LENGTH = -5720;

/** Session key incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_SESSION_KEY_INCORRECT_FORMAT = -5721;

/** Client verification message null or empty */
const int DSAPPErrorCodes_SRP_CLIENT_MESSAGE_NULL_OR_EMPTY = -5722;

/** Client verification message incorrect length. Length must be {@link DSAPPConstants_SRP_EVIDENCE_MESSAGE_LENGTH} characters */
const int DSAPPErrorCodes_SRP_CLIENT_MESSAGE_INCORRECT_LENGTH = -5723;

/** Client verification message incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_CLIENT_MESSAGE_INCORRECT_FORMAT = -5724;

/** Server verification message null or empty */
const int DSAPPErrorCodes_SRP_SERVER_MESSAGE_NULL_OR_EMPTY = -5725;

/** Server verification message  message incorrect length. Length must be {@link DSAPPConstants_SRP_EVIDENCE_MESSAGE_LENGTH} characters */
const int DSAPPErrorCodes_SRP_SERVER_MESSAGE_INCORRECT_LENGTH = -5726;

/** Server verification message incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_SERVER_MESSAGE_INCORRECT_FORMAT = -5727;

/** MAC null or empty */
const int DSAPPErrorCodes_SRP_MAC_NULL_OR_EMPTY = -5728;

/** MAC message incorrect length. Length must be {@link DSAPPConstants_SRP_MAC_LENGTH} characters */
const int DSAPPErrorCodes_SRP_MAC_INCORRECT_LENGTH = -5729;

/** MAC incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_MAC_INCORRECT_FORMAT = -5730;

/** Encryption counter null or empty */
const int DSAPPErrorCodes_SRP_ENCRYPTION_COUNTER_NULL_OR_EMPTY = -5731;

/** Encryption counter incorrect length. Length must be {@link DSAPPConstants_SRP_ENCRYPTION_COUNTER_LENGTH} characters */
const int DSAPPErrorCodes_SRP_ENCRYPTION_COUNTER_INCORRECT_LENGTH = -5732;

/** Encryption counter incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_ENCRYPTION_COUNTER_INCORRECT_FORMAT = -5733;

/** Encrypted data null or empty */
const int DSAPPErrorCodes_SRP_ENCRYPTED_DATA_NULL_OR_EMPTY = -5734;

/** Encrypted data incorrect format. It must be hexadecimal */
const int DSAPPErrorCodes_SRP_ENCRYPTED_DATA_INCORRECT_FORMAT = -5735;

/** Message verification failed */
const int DSAPPErrorCodes_SRP_MESSAGE_VERIFICATION_FAILED = -5736;

/** MAC verification failed */
const int DSAPPErrorCodes_SRP_MAC_VERIFICATION_FAILED = -5737;

/** Null or empty data */
const int DSAPPErrorCodes_SRP_DATA_NULL_OR_EMPTY = -5738;


#endif
