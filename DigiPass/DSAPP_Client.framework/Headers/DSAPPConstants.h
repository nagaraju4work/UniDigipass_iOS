//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef DSAPPCONSTANTS_H_
#define DSAPPCONSTANTS_H_

/**
 * Constants used by the DSAPP library.
 */

/** Length of the serialized public key */
const int DSAPPConstants_PUBLIC_KEY_LENGTH = 128;

/** Length of the serialized private key */
const int DSAPPConstants_PRIVATE_KEY_LENGTH = 64;

/** Length of the nonce */
const int DSAPPConstants_NONCE_LENGTH = 8;

/** Length of the initial vector */
const int DSAPPConstants_INITIAL_VECTOR_LENGTH = 32;

/** Length of the CHS key */
const int DSAPPConstants_CHS_KEY_LENGTH = 32;
        
/** Length of the encrypted server nonce */
const int DSAPPConstants_ENCRYPTED_SERVER_NONCE_LENGTH = 32;

/** Length of the encrypted client + server nonces */
const int DSAPPConstants_ENCRYPTED_NONCES_LENGTH = 32;

/** Shared data min length */
const int DSAPPConstants_SHARED_DATA_MIN_LENGTH = 4;

/** Shared data max length */
const int DSAPPConstants_SHARED_DATA_MAX_LENGTH = 512;
        
/** Length of the session key */
const int DSAPPConstants_SESSION_KEY_LENGTH = 32;
        
/** Minimum length of the SRP password */
const int DSAPPConstants_SRP_PWD_MIN_LENGTH = 4;
        
/** Maximum length of the SRP password */
const int DSAPPConstants_SRP_PWD_MAX_LENGTH = 64;
        
/** Maximum length of the SRP user identifier */
const int DSAPPConstants_SRP_USER_ID_MAX_LENGTH = 64;
        
/** Minimum length of the SRP user identifier */
const int DSAPPConstants_SRP_USER_ID_MIN_LENGTH = 4;
        
/** Length of the session SRP salt */
const int DSAPPConstants_SRP_SALT_LENGTH = 32;
        
/** Maximum length of the SRP ephemeral key */
const int DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH = 512;
        
/** Length of the SRP evidence message */
const int DSAPPConstants_SRP_EVIDENCE_MESSAGE_LENGTH = 64;
        
/** Length of the SRP session key */
const int DSAPPConstants_SRP_SESSION_KEY_LENGTH = 64;
        
/** Length of the SRP MAC */
const int DSAPPConstants_SRP_MAC_LENGTH = 64;
        
/** Length of SRP encryption counter */
const int DSAPPConstants_SRP_ENCRYPTION_COUNTER_LENGTH = 16;


#endif
