//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef GENERATESESSIONKEYRESPONSE_H_
#define GENERATESESSIONKEYRESPONSE_H_

#include <string>
using namespace std;

/**
 * Response class used during the generation of the session key.
 */
class GenerateSessionKeyResponse
{

public:

	GenerateSessionKeyResponse();
	
    /** Encrypted server nonce */
    string encryptedServerNonce;

    /** Client initial vector */
    string clientInitialVector;

    /** Session key */
    string sessionKey;

};

#endif
