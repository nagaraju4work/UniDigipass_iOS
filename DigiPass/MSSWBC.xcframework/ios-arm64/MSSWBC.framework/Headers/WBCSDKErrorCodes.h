
#ifndef WBCSDKERRORCODES_H_
#define WBCSDKERRORCODES_H_

namespace com
{
namespace vasco
{
namespace digipass
{
namespace sdk
{
namespace utils
{
namespace wbc
{

/**
 * This class provides the error codes managed by the WBC SDK.
 */
class WBCSDKErrorCodes
{
public:

    /** Internal error */
    const static int INTERNAL_ERROR = -5550;

    /** The crypto mechanism is invalid. */
    const static int CRYPTO_MECHANISM_INVALID = -5551;

    /** The crypto mode is invalid. */
    const static int CRYPTO_MODE_INVALID = -5552;

    /** The WBCSDKTable object is invalid. */
    const static int WBCSDK_TABLES_INVALID = -5553;

    /** The initial vector byte array is null. */
    const static int INITIAL_VECTOR_NULL = -5554;

    /** The initial vector length is incorrect according to the selected mechanism. */
    const static int INITIAL_VECTOR_INCORRECT_LENGTH = -5555;

    /** The input byte array is null. */
    const static int INPUT_DATA_NULL = -5556;

    /** The input bytes array length is incorrect according to the selected mechanism. */
    const static int INPUT_DATA_INCORRECT_LENGTH = -5557;

    /** The output byte array is null. */
    const static int OUTPUT_DATA_NULL = -5558;

    /** The output data length is invalid. */
    const static int OUTPUT_DATA_INCORRECT_LENGTH = -5559;

};

}
}
}
}
}
}

#endif /* WBCSDKERRORCODES_H_ */
