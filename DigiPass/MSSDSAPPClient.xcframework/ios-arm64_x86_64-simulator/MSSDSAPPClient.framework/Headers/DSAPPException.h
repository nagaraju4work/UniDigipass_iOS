//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef DSAPPEXCEPTIONS_H_
#define DSAPPEXCEPTIONS_H_

#include <exception>
#include <string>
using namespace std;

/**
 * Exception which can be thrown by the DSAPP library in case of error.
 */
class DSAPPException: public exception
{

public:

	/** Constructor */
	DSAPPException(int errorCode);

	/** Desturctor */
	virtual ~DSAPPException() throw ();

	/**
	 * Gets the error code
	 * @return The error code
	 */
	int getErrorCode();

	/**
	 * Gets a default error message associated with the error code
	 * @return The error message
	 */
	string getMessage();

	/**
	 * Generic method to get the default error message
	 */
	virtual const char * what() const throw ();

private:

	/** Error code */
	int errorCode;

	/** Message */
	string message;

	static string messageUnknownErrorCode();
	static string messageInternalError();
	static string messageActivationPasswordTooLong();
	static string messageChsKeyNullOrEmpty();
	static string messageIncorrectChsKeyLength();
	static string messageIncorrectChsKeyFormat();
	static string messageClientPrivateKeyNullOrEmpty();
	static string messageIncorrectClientPrivateKeyLength();
	static string messageIncorrectClientPrivateKeyFormat();
	static string messageEncryptedServerPublicKeyNullOrEmpty();
	static string messageIncorrectEncryptedServerPublicKeyLength();
	static string messageIncorrectEncryptedServerPublicKeyFormat();
	static string messageEncryptedNoncesNullOrEmpty();
	static string messageIncorrectEncryptedNoncesLength();
	static string messageIncorrectEncryptedNoncesFormat();
	static string messageClientNonceNullOrEmpty();
	static string messageIncorrectClientNonceLength();
	static string messageIncorrectClientNonceFormat();
	static string messageXFADNullOrEmpty();
	static string messageIncorrectXFADFormat();
	static string messageIncorrectXERCFormat();
	static string messageServerInitialVectorNullOrEmpty();
	static string messageIncorrectServerInitialVectorLength();
	static string messageIncorrectServerInitialVectorFormat();
	static string messageErrorWhileCheckingTheNonce();
	static string messageSharedDataLengthNullOrEmpty();
	static string messageSharedDataLengthTooShort();
	static string messageSharedDataLengthTooLong();
	static string messageChecksumCannotBeValidated();
	static string messageNullOrEmptySessionKey();
	static string messageIncorrectSessionKeyLength();
	static string messageIncorrectSessionKeyFormat();
	static string messageEncryptedDataNullOrEmpty();
	static string messageIncorrectEncryptedDataFormat();
	static string messageNullDecryptedDataBufferLengthAddress();
	static string messageNullDecryptedDataBuffer();
	static string messageDecryptedDataBufferTooSmall();
	static string messageIncorrectDecryptedDataFormat();
	static string messageSharedSecretTooLong();
	static string messageSRPClientEphemeralKeyNullOrEmpty();
	static string messageSRPClientEphemeralKeyTooLong();
	static string messageSRPClientEphemeralKeyInvalid();
	static string messageSRPClientEphemeralKeyIncorrectFormat();
	static string messageSRPUserIdentifierNullOrEmpty();
	static string messageSRPUserIdentifierTooLongOrTooShort();
	static string messageSRPPasswordNullOrEmpty();
	static string messageSRPPasswordTooLongOrTooShort();
	static string messageSRPSaltNullOrEmpty();
	static string messageSRPSaltIncorrectLength();
	static string messageSRPSaltIncorrectFormat();
	static string messageSRPServerEphemeralKeyNullOrEmpty();
	static string messageSRPServerEphemeralKeyTooLong();
	static string messageSRPServerEphemeralKeyInvalid();
	static string messageSRPServerEphemeralKeyIncorrectFormat();
	static string messageSRPClientPrivateKeyNullOrEmpty();
	static string messageSRPClientPrivateKeyTooLong();
	static string messageSRPClientPrivateKeyInvalid();
	static string messageSRPClientPrivateKeyIncorrectFormat();
	static string messageSRPSessionKeyNullOrEmpty();
	static string messageSRPSessionKeyIncorrectLength();
	static string messageSRPSessionKeyIncorrectFormat();
	static string messageSRPClientVerificationMessageNullOrEmpty();
	static string messageSRPClientVerificationMessageIncorrectLength();
	static string messageSRPClientVerificationMessageIncorrectFormat();
	static string messageSRPServerVerificationMessageNullOrEmpty();
	static string messageSRPServerVerificationMessageIncorrectLength();
	static string messageSRPServerVerificationMessageIncorrectFormat();
	static string messageSRPMACNullOrEmpty();
	static string messageSRPMACIncorrectLength();
	static string messageSRPMACIncorrectFormat();
	static string messageSRPEncryptionCounterNullOrEmpty();
	static string messageSRPEncryptionCounterIncorrectLength();
	static string messageSRPEncryptionCounterIncorrectFormat();
	static string messageSRPEncryptedDataNullOrEmpty();
	static string messageSRPEncryptedDataIncorrectFormat();
	static string messageSRPMessageVerificationFailed();
	static string messageSRPMACVerificationFailed();
	static string messageSRPNullOrEmptyData();

};

#endif
