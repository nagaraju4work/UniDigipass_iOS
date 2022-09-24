//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//  Generated by WBCSDK_TableGenerator 4.21.1
//
//////////////////////////////////////////////////////////////////////////////

#ifndef WBCSDKTABLES_H_
#define WBCSDKTABLES_H_
#include <WBCSDK/WBCSDKTables.h>

//#include "WBCSDK/WBCSDKTables.h"

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
                        class WBCSDKTablesImpl : public WBCSDKTables
                        {
                        private:
                            static const unsigned char final_decoding[131120];
                            static const unsigned char initial_encoding[131120];
                            static const unsigned char typeIA_input_sbox[512];
                            static const unsigned char typeIAs[65536];
                            static const unsigned char typeIB_output_sbox_inv[512];
                            static const unsigned char typeIBs[65536];
                            static const unsigned char typeIIs[147456];
                            static const unsigned char typeIIIs[147456];
                            static const unsigned char typeIV_IAs[61440];
                            static const unsigned char typeIV_IBs[61440];
                            static const unsigned char typeIV_IIs[110592];
                            static const unsigned char typeIV_IIIs[110592];
                            
                            static gf2matrix *initial_encoding_data;
                            static gf2matrix *final_decoding_data;
                            static sboxes_8bit_t* typeIA_input_sbox_data;
                            static typeIA_t* typeIAs_data;
                            static sboxes_8bit_t* typeIB_output_sbox_inv_data;
                            static typeIB_t* typeIBs_data;
                            static typeII_t* typeIIs_data;
                            static typeIII_t* typeIIIs_data;
                            static typeIV_IA_t* typeIV_IAs_data;
                            static typeIV_IB_t* typeIV_IBs_data;
                            static typeIV_II_round_t* typeIV_IIs_data;
                            static typeIV_III_round_t* typeIV_IIIs_data;
                            
                        public:
                            virtual gf2matrix *getInitialEncoding();
                            
                            virtual gf2matrix *getFinalDecoding();
                            
                            virtual sboxes_8bit_t *getTypeIA_input_sbox();
                            
                            virtual typeIA_t* getTypeIAs();
                            
                            virtual sboxes_8bit_t* getTypeIB_output_sbox_inv();
                            
                            virtual typeIB_t* getTypeIBs();
                            
                            virtual typeII_t* getTypeIIs();
                            
                            virtual typeIII_t* getTypeIIIs();
                            
                            virtual typeIV_IA_t* getTypeIV_IAs();
                            
                            virtual typeIV_IB_t* getTypeIV_IBs();
                            
                            virtual typeIV_II_round_t* getTypeIV_IIs();
                            
                            virtual typeIV_III_round_t* getTypeIV_IIIs();
                        };
                        
                    }
                }
            }
        }
    }
}
#endif /* WBCSDKTABLES_H_ */