#ifndef SRC_COMMON_HW_INCLUDE_MILLIS_H_
#define SRC_COMMON_HW_INCLUDE_MILLIS_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"



bool millisInit(void);
uint32_t millis(void);


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INCLUDE_MILLIS_H_ */