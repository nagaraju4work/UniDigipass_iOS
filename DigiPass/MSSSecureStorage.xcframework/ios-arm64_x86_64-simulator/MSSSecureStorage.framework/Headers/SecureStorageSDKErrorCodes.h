//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

// Indicates that an internal error occurred
#define SecureStorageSDKErrorCodes_INTERNAL_ERROR -4300

// Name of the storage null
#define SecureStorageSDKErrorCodes_STORAGE_NAME_NULL -4301

// Name of the storage too long
#define SecureStorageSDKErrorCodes_STORAGE_NAME_INCORRECT_LENGTH -4302

// Name of the storage contains invalid characters. It can only contain alphanumeric characters (along wit “-“, “_” and “.”)
#define SecureStorageSDKErrorCodes_STORAGE_NAME_INCORRECT_FORMAT -4303

// Storage does not exist
#define SecureStorageSDKErrorCodes_UNKNOWN_STORAGE -4304

// Storage not readable
#define SecureStorageSDKErrorCodes_UNREADABLE_STORAGE -4305

// Android context null
#define SecureStorageSDKErrorCodes_CONTEXT_NULL -4306

// Iteration count must be >0
#define SecureStorageSDKErrorCodes_ITERATION_COUNT_INCORRECT -4307

// Key null
#define SecureStorageSDKErrorCodes_KEY_NULL -4308

// Key has incorrect length
#define SecureStorageSDKErrorCodes_KEY_INCORRECT_LENGTH -4309

// Key contains invalid character
#define SecureStorageSDKErrorCodes_KEY_INCORRECT_FORMAT -4310

// Storage does not contains requested key
#define SecureStorageSDKErrorCodes_UNKNOWN_KEY -4311

// Value null
#define SecureStorageSDKErrorCodes_VALUE_NULL -4312

// Value has incorrect length
#define SecureStorageSDKErrorCodes_VALUE_INCORRECT_LENGTH -4313

// Value contains invalid character
#define SecureStorageSDKErrorCodes_VALUE_INCORRECT_FORMAT -4314

// The used getter is incorrect according to the type of the requested data
#define SecureStorageSDKErrorCodes_INCORRECT_GETTER -4315

// The storage is corrupted
#define SecureStorageSDKErrorCodes_STORAGE_CORRUPTED -4316

// The storage is locked
#define SecureStorageSDKErrorCodes_DATA_LOCKED -4317

// The public encryption key in the keychain is not available
#define SecureStorageSDKErrorCodes_PUBLIC_KEY_UNAVAILABLE -4318

// The encryption algorithm is not supported
#define SecureStorageSDKErrorCodes_ENCRYPTION_ALGORITHM_NOT_SUPPORTED -4319

// The decryption algorithm is not supported
#define SecureStorageSDKErrorCodes_DECRYPTION_ALGORITHM_NOT_SUPPORTED -4320

// The data file cannot be read
#define SecureStorageSDKErrorCodes_READ_FILE_ERROR -4321

// The data file cannot be written
#define SecureStorageSDKErrorCodes_WRITE_FILE_ERROR -4322

// The data file cannot be deleted
#define SecureStorageSDKErrorCodes_REMOVE_FILE_ERROR -4323

// The encryption with the fingerprint failed
#define SecureStorageSDKErrorCodes_ENCRYPTION_WITH_FPERROR -4324

// The decryption with the fingerprint failed
#define SecureStorageSDKErrorCodes_DECRYPTION_WITH_FPERROR -4325

// The decrypted data cannot be deserialized
#define SecureStorageSDKErrorCodes_DESERIALIZATION_ERROR -4326

// The data cannot be serialized
#define SecureStorageSDKErrorCodes_SERIALIZATION_ERROR -4327

// The data encrypted with the fingerprint cannot be serialized
#define SecureStorageSDKErrorCodes_ENCRYPTION_WITH_FPDATA_ERROR -4328

// The decryption using a key derived from the fingerprint failed
#define SecureStorageSDKErrorCodes_INVALID_FINGERPRINT_ERROR -4329

// The volatile data encryption failed
#define SecureStorageSDKErrorCodes_VOLATILE_ENCRYPTION_DATA_ERROR -4330

// The volatile data encryption failed
#define SecureStorageSDKErrorCodes_VOLATILE_ENCRYPTION_ERROR -4331

// The volatile data decryption failed
#define SecureStorageSDKErrorCodes_VOLATILE_DECRYPTION_ERROR -4332

// The creation of the volatile key failed
#define SecureStorageSDKErrorCodes_VOLATILE_KEY_CREATION_ERROR -4333

// Error retrieving the volatile encryption key from the keychain
#define SecureStorageSDKErrorCodes_VOLATILE_KEY_COPY_ERROR -4334

// The volatile encryption key seems corrupted
#define SecureStorageSDKErrorCodes_VOLATILE_KEY_DATA_ERROR -4335

// Decryption with the secure enclave failed
#define SecureStorageSDKErrorCodes_SECURE_ENCLAVE_DECRYPTION_ERROR -4336

// Encryption with the secure enclave failed
#define SecureStorageSDKErrorCodes_SECURE_ENCLAVE_ENCRYPTION_ERROR -4337

// The creation of the secure enclave key failed
#define SecureStorageSDKErrorCodes_SECURE_ENCLAVE_KEY_ACCESS_CREATION_ERROR -4338

// The creation of the secure enclave key failed
#define SecureStorageSDKErrorCodes_SECURE_ENCLAVE_KEY_CREATION_ERROR -4339

// The deletion of the secure enclave key failed
#define SecureStorageSDKErrorCodes_SECURE_ENCLAVE_KEY_DELETION_ERROR -4340

// String value is not UTF-8 format encodable.
#define SecureStorageSDKErrorCodes_STRING_VALUE_NOT_UTF8_FORMAT -4341

