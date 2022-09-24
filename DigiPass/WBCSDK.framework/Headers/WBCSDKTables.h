
#ifndef WBSDKTables_H_
#define WBSDKTables_H_


#ifndef WBCTYPES_DEC_H_
#define WBCTYPES_DEC_H_

#include <stdlib.h>

#ifdef WIN32
#include "stdint.h"
#else
#include <stdint.h>
#endif

// Number of rounds (set to 10 for AES128)
#define NR 10

// Type I Lookup tables
typedef uint8_t (typeI_t)[4][4][256][16];
// Type IA Lookup tables (same as typeI_t)
typedef typeI_t typeIA_t;
// Type IB Lookup tables (same as typeI_t)
typedef typeI_t typeIB_t;
// Type II or Type III Lookup tables (for one round)
typedef uint8_t (typeII_round_t)[4][4][256][4];
// Type II or Type III Lookup tables (for one round)
typedef typeII_round_t typeIII_round_t;
// Type II or Type III Lookup tables for all rounds
typedef typeII_round_t (typeII_t)[NR-1];
// Type II or Type III Lookup tables for all rounds
typedef typeII_t typeIII_t;
// Type IV Lookup tables following Type I (128 bit)
typedef uint8_t (typeIV128_t)[4][4][15][2][128];
// Type IV Lookup tables following Type IA (128 bit)
typedef typeIV128_t typeIV_IA_t;
// Type IV Lookup tables following Type IB (128 bit)
typedef typeIV128_t typeIV_IB_t;
// Type IV Lookup tables following Type II or III (32 bit) for one round
typedef uint8_t (typeIV32_round_t)[4][4][3][2][128];
// Type IV Lookup tables following Type II or III (32 bit) for all rounds
typedef typeIV32_round_t (typeIV32_t)[NR-1];
// Type IV Lookup tables following Type II (32 bit) for all rounds
typedef typeIV32_round_t typeIV_II_round_t;
// Type IV Lookup tables following Type III (32 bit) for all rounds
typedef typeIV32_round_t typeIV_III_round_t;
// 4-bit strips for 32bit operations
typedef uint8_t _4bit_strip32_t[4][4][4];
// 4-bit strips for 128bit operations
typedef uint8_t _4bit_strip128_t[4][4][16];
// 2 4x4sboxes used in 4bit encoding/decoding
typedef uint8_t (sboxes_8bit_t)[4][4][2][16];



// A word is the typical packed data structure to represent packed bits
typedef uint64_t word;

// Type of row and column indexes
// This type is used for integer values that hold row/colum sized values
typedef int rci_t;

// Type of word indexes
// This type is used for the array of words that make up a row
typedef int wi_t;

// Blocks
typedef struct
{
    size_t size;
    word* begin;
    word* end;
} mzd_block_t;


// Dense matrices over GF(2)
typedef struct mzd_t
{
    // Number of rows.
    rci_t nrows;
    // Number of columns.
    rci_t ncols;
    // Number of words with valid bits.
    // width = ceil((ncols + offset) / matrix_radix)
    wi_t width;
    // Offset in words between rows.
    // rowstride = (width < mzd_paddingwidth || (width & 1) == 0) ? width : width + 1;
    // where width is the width of the underlying non-windowed matrix.
    wi_t rowstride;
    // Offset in words from start of block to first word.
    // rows[0] = blocks[0].begin + offset_vector;
    // This, together with rowstride, makes the rows array obsolete.
    wi_t offset_vector;
    // Number of rows to the first row counting from the start of the first block.
    wi_t row_offset;
    // column offset of the first column.
    uint16_t offset;
    // Booleans to speed up things.
    // The bits have the following meaning:
    // 0: Has non-zero offset (and thus is windowed).
    // 1: Has non-zero excess.
    // 2: Is windowed, but has zero offset.
    // 3: Is windowed, but has zero excess.
    // 4: Is windowed, but owns the blocks allocations.
    // 5: Spans more than 1 block.
    uint8_t flags;
    // blockrows_log = log2(blockrows);
    // where blockrows is the number of rows in one block, which is a power of 2.
    uint8_t blockrows_log;
    // Mask for valid bits in the word with the highest index (width - 1).
    word high_bitmask;
    // Mask for valid bits in the word with the lowest index (0).
    word low_bitmask;
    // Contains pointers to the actual blocks of memory containing the
    // values packed into words of size matrix_radix.
    mzd_block_t *blocks;
    // Address of first word in each row, so the first word of row i is m->rows[i]
    word **rows;
} mzd_t;

// make gf2matrix the same as mzd_t in m4ri
typedef mzd_t gf2matrix;


extern "C"
{


int message_to_typeIA_input_sbox(uint8_t *message, int nLength, sboxes_8bit_t typeIA_input_sbox);
int message_to_typeIAs(uint8_t *message, int nLength, typeIA_t typeIAs);
int message_to_typeIV_IAs(uint8_t *message, int nLength, typeIV_IA_t typeIV_IAs);
int message_to_typeIIs(uint8_t *message, int nLength, typeII_t typeIIs);
int message_to_typeIV_IIs(uint8_t *message, int nLength, typeIV_II_round_t typeIV_IIs[NR - 1]);
int message_to_typeIIIs(uint8_t *message, int nLength, typeIII_t typeIIIs);
int message_to_typeIV_IIIs(uint8_t *message, int nLength, typeIV_III_round_t typeIV_IIIs[NR - 1]);
int message_to_typeIBs(uint8_t *message, int nLength, typeIB_t typeIBs);
int message_to_typeIV_IBs(uint8_t *message, int nLength, typeIV_IB_t typeIV_IBs);
int message_to_typeIB_output_sbox_inv(uint8_t *message, int nLength, sboxes_8bit_t typeIB_output_sbox_inv);
int message_to_gf2matrix(uint8_t *message, int nLength, gf2matrix **matrix);


}

#endif /* WBCTYPES_DEC_H_ */




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
 * VDS internal use. Interface that is implemented by class generated by Table Generator.
 */
class WBCSDKTables
{


public:
    virtual ~WBCSDKTables();

    /** VDS internal use. Do not use */
    virtual gf2matrix *getInitialEncoding() = 0;

    /** VDS internal use. Do not use */
    virtual gf2matrix *getFinalDecoding() = 0;

    /** VDS internal use. Do not use */
    virtual sboxes_8bit_t *getTypeIA_input_sbox() = 0;

    /** VDS internal use. Do not use */
    virtual typeIA_t* getTypeIAs() = 0;

    /** VDS internal use. Do not use */
    virtual sboxes_8bit_t* getTypeIB_output_sbox_inv() = 0;

    /** VDS internal use. Do not use */
    virtual typeIB_t* getTypeIBs() = 0;

    /** VDS internal use. Do not use */
    virtual typeII_t* getTypeIIs() = 0;

    /** VDS internal use. Do not use */
    virtual typeIII_t* getTypeIIIs() = 0;

    /** VDS internal use. Do not use */
    virtual typeIV_IA_t* getTypeIV_IAs() = 0;

    /** VDS internal use. Do not use */
    virtual typeIV_IB_t* getTypeIV_IBs() = 0;

    /** VDS internal use. Do not use */
    virtual typeIV_II_round_t* getTypeIV_IIs() = 0;

    /** VDS internal use. Do not use */
    virtual typeIV_III_round_t* getTypeIV_IIIs() = 0;


};

}
}
}
}
}
}

#endif /* WBSDKTables_H_ */
