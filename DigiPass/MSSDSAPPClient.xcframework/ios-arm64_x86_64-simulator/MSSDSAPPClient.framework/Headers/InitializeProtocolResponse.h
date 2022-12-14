//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef INITIALIZEPROTOCOLRESPONSE_H_
#define INITIALIZEPROTOCOLRESPONSE_H_

#include <string>
using namespace std;

/**
 * Response class used to store the elements resulting of the protocol initialization.
 * The InitializeProtocolResponse object is returned by {@link DSAPPClient#initializeProtocol}.
 */
class InitializeProtocolResponse
{

public:

	InitializeProtocolResponse();

	/** The key derived from the shared secret. {@link DSAPPConstants_CHS_KEY_LENGTH} hexadecimal string. Must be stored on the client side and used for the data decryption. */
	string chsKey;

	/** The encrypted concatenation of the client public key and the client nonce. ({@link DSAPPConstants_PUBLIC_KEY_LENGTH} + {@link DSAPPConstants_NONCE_LENGTH}) hexadecimal characters. Must be sent to the server.*/
	string encryptedClientPublicKeyAndNonce;

	/** The client private key used for session key calculation. {@link DSAPPConstants_PRIVATE_KEY_LENGTH} hexadecimal string. Must be stored on the client side and used for the data decryption. */
	string clientPrivateKey;

	/** The initial vector used for public key encryption. {@link DSAPPConstants_INITIAL_VECTOR_LENGTH} hexadecimal string. Must be sent to the server. */
	string clientInitialVector;

	/** The client nonce that will be verified against the one received from the server. {@link DSAPPConstants_NONCE_LENGTH} hexadecimal string. Must be stored on the client side and used for the data decryption. */
	string clientNonce;

};


#endif
