//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef SRPSESSIONKEYRESPONSE_H_
#define SRPSESSIONKEYRESPONSE_H_

#include <string>
using namespace std;

/**
 * Response class used to store the elements resulting of SRP client ephemeral key generation.
 * The GenerateSRPSessionKeyResponse object is returned by {@link DSAPPClient#generateSRPClientEphemeralKey}.
 */
class SRPSessionKeyResponse
{

public:

    SRPSessionKeyResponse();

    /** The SRP session key. {@link DSAPPConstants_SRP_SESSION_KEY_LENGTH} hexadecimal string. Must be stored on the client side and used for the data decryption. */
    string sessionKey;

    /** The SRP client evidence message. {@link DSAPPConstants_SRP_EVIDENCE_MESSAGE_LENGTH} hexadecimal string. Must be sent to the server. */
    string clientEvidenceMessage;
};


#endif
