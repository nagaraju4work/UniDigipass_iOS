//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef SRPCLIENTEPHEMERALKEYRESPONSE_H_
#define SRPCLIENTEPHEMERALKEYRESPONSE_H_

#include <string>
using namespace std;

/**
 * Response class used to store the elements resulting of SRP client ephemeral key generation.
 * The GenerateSRPClientEphemeralKeyResponse object is returned by {@link DSAPPClient#generateSRPClientEphemeralKey}.
 */
class SRPClientEphemeralKeyResponse
{

public:

    SRPClientEphemeralKeyResponse();

    /** The SRP public ephemeral key. Hexadecimal string of size inferior or equal to {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH}. 
	 * Must be sent to the server and stored on the client side to be used for the SRP session key generation and the server message verification. 
	 */
    string clientEphemeralPublicKey;

    /** The SRP private ephemeral key. Hexadecimal string of size inferior or equal to {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH}. 
	 * Must be stored on the client side and used for the SRP session key generation. 
	 */
    string clientEphemeralPrivateKey;
};


#endif
