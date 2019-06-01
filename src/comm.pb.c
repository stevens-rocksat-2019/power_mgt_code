/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.3 at Tue May 28 21:21:29 2019. */

#include "comm.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t RailConfiguration_fields[9] = {
    PB_FIELD(  1, INT32   , REQUIRED, STATIC  , FIRST, RailConfiguration, powerRail, powerRail, 0),
    PB_FIELD(  2, FLOAT   , OPTIONAL, STATIC  , OTHER, RailConfiguration, currentLimit, powerRail, 0),
    PB_FIELD(  3, FLOAT   , OPTIONAL, STATIC  , OTHER, RailConfiguration, voltageCutoff, currentLimit, 0),
    PB_FIELD(  4, BOOL    , OPTIONAL, STATIC  , OTHER, RailConfiguration, currentLimitEnabled, voltageCutoff, 0),
    PB_FIELD(  5, BOOL    , OPTIONAL, STATIC  , OTHER, RailConfiguration, voltageLimitEnabled, currentLimitEnabled, 0),
    PB_FIELD(  6, INT64   , OPTIONAL, STATIC  , OTHER, RailConfiguration, timeLimit, voltageLimitEnabled, 0),
    PB_FIELD(  7, BOOL    , OPTIONAL, STATIC  , OTHER, RailConfiguration, timeLimitEnabled, timeLimit, 0),
    PB_FIELD(  8, FLOAT   , OPTIONAL, STATIC  , OTHER, RailConfiguration, dutyCycle, timeLimitEnabled, 0),
    PB_LAST_FIELD
};

const pb_field_t PowerConfiguration_fields[2] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, PowerConfiguration, railConfiguration, railConfiguration, &RailConfiguration_fields),
    PB_LAST_FIELD
};

const pb_field_t PowerControl_fields[3] = {
    PB_FIELD(  1, INT32   , OPTIONAL, STATIC  , FIRST, PowerControl, powerRail, powerRail, 0),
    PB_FIELD(  2, UENUM   , OPTIONAL, STATIC  , OTHER, PowerControl, powerState, powerRail, 0),
    PB_LAST_FIELD
};

const pb_field_t PowerRailInfo_fields[5] = {
    PB_FIELD(  1, INT32   , OPTIONAL, STATIC  , FIRST, PowerRailInfo, powerRail, powerRail, 0),
    PB_FIELD(  2, FLOAT   , OPTIONAL, STATIC  , OTHER, PowerRailInfo, voltage, powerRail, 0),
    PB_FIELD(  3, FLOAT   , OPTIONAL, STATIC  , OTHER, PowerRailInfo, current, voltage, 0),
    PB_FIELD(  4, UENUM   , OPTIONAL, STATIC  , OTHER, PowerRailInfo, powerState, current, 0),
    PB_LAST_FIELD
};

const pb_field_t PowerEvent_fields[3] = {
    PB_FIELD(  1, INT32   , OPTIONAL, STATIC  , FIRST, PowerEvent, powerRail, powerRail, 0),
    PB_FIELD(  2, UENUM   , OPTIONAL, STATIC  , OTHER, PowerEvent, eventType, powerRail, 0),
    PB_LAST_FIELD
};

const pb_field_t TxMicro_fields[4] = {
    PB_FIELD(  1, INT64   , OPTIONAL, STATIC  , FIRST, TxMicro, timeStamp, timeStamp, 0),
    PB_FIELD(  2, MESSAGE , REPEATED, STATIC  , OTHER, TxMicro, powerRailInfo, timeStamp, &PowerRailInfo_fields),
    PB_FIELD(  3, MESSAGE , OPTIONAL, STATIC  , OTHER, TxMicro, powerEvent, powerRailInfo, &PowerEvent_fields),
    PB_LAST_FIELD
};

const pb_field_t RxMicro_fields[3] = {
    PB_FIELD(  1, MESSAGE , OPTIONAL, STATIC  , FIRST, RxMicro, powerConfiguration, powerConfiguration, &PowerConfiguration_fields),
    PB_FIELD(  2, MESSAGE , OPTIONAL, STATIC  , OTHER, RxMicro, powerControl, powerConfiguration, &PowerControl_fields),
    PB_LAST_FIELD
};




/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(TxMicro, powerRailInfo[0]) < 65536 && pb_membersize(TxMicro, powerEvent) < 65536 && pb_membersize(RxMicro, powerConfiguration) < 65536 && pb_membersize(RxMicro, powerControl) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_RailConfiguration_PowerConfiguration_PowerControl_PowerRailInfo_PowerEvent_TxMicro_RxMicro)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(TxMicro, powerRailInfo[0]) < 256 && pb_membersize(TxMicro, powerEvent) < 256 && pb_membersize(RxMicro, powerConfiguration) < 256 && pb_membersize(RxMicro, powerControl) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_RailConfiguration_PowerConfiguration_PowerControl_PowerRailInfo_PowerEvent_TxMicro_RxMicro)
#endif


/* @@protoc_insertion_point(eof) */
