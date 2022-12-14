
#ifndef WBCSDKCONSTANTS_H_
#define WBCSDKCONSTANTS_H_

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
 * Defines constants used by the WBC SDK
 */
class WBCSDKConstants
{
public:

    /** AES cipher mechanism */
    const static unsigned char CRYPTO_MECHANISM_AES = 0x03;

    /** CTR cipher mode */
    const static unsigned char CRYPTO_MODE_CTR = 0x04;
};

}
}
}
}
}
}

#endif /* WBCSDKCONSTANTS_H_ */
