
#ifndef WBCSDKEXCEPTION_H_
#define WBCSDKEXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

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
 * This exception is thrown when a problem occurs while using WBC SDK.
 */
class WBCSDKException: public exception
{

public:

    /**
     * Constructs a new {@link WBCSDKException}.
     * @param errorCode The error code. See {@link WBCSDKErrorCodes} for more details.
     */
    WBCSDKException(int errorCode);

    /**
     * Constructs a new {@link WBCSDKException}.
     * @param errorCode The error code. See {@link WBCSDKErrorCodes} for more details.
     * @param cause Exception describing the cause of the failure.
     */
    WBCSDKException(int errorCode, exception cause);

    /** Destructor */
    virtual ~WBCSDKException() throw ();

    /**
     * Retrieves the error code of the {@link WBCSDKException}.
     * Error codes are defined in the {@link WBCSDKErrorCodes} class.
     * @return The error code of the exception.
     */
    int getErrorCode();

    /**
     * Retrieves the cause of the {@link WBCSDKException}, only with {@link WBCSDKErrorCodes::INTERNAL_ERROR}.
     * @return The cause of the {@link WBCSDKException}.
     */
    exception getCause();

private:

    /** Error code */
    int errorCode;

    /** Embedded exception */
    exception e;

};

}
}
}
}
}
}

#endif /* WBCSDKEXCEPTION_H_ */
