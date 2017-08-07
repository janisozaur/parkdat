#ifndef SV6_DECODE_H
#define SV6_DECODE_H

#include "SV6_ENCODE_DECODE.h"

#ifndef dllPort
#define dllPort __declspec(dllexport)
#else
#define dllPort
#endif

dllPort void DecodeSv6(SV6_FILE * sv6, char * inFileStream, int sv6CompressedSize);
dllPort void OpenSv6(SV6_FILE * sv6, char * sv6FileName);

#endif // SV6_DECODE_H
