/*
 * Ai-Thinker A9(G) Library using AT Commands
 */

#ifndef A9G_AT_COMMANDS_H
#define A9G_AT_COMMANDS_H

#include <Arduino.h>
#include <stdbool.h>
#include <CayenneLPP.h>

typedef enum {
    RESTART,
    SHUTDOWN
} A9G_shdn_level_t;

typedef enum {
    PHONE_FAILURE=0,
    NO_CONNECT_PHONE,
    PHONE_ADAPTER_LINK_RESERVED,
    OPERATION_NOT_ALLOWED,
    OPERATION_NOT_SUPPORTED,
    PHSIM_PIN_REQUIRED,
    PHFSIM_PIN_REQUIRED,
    PHFSIM_PUK_REQUIRED,
    SIM_NOT_INSERTED=10,
    SIM_PIN_REQUIRED,
    SIM_PUK_REQUIRED,
    SIM_FAILURE,
    SIM_BUSY,
    SIM_WRONG,
    INCORRECT_PASSWORD,
    SIM_PIN2_REQUIRED,
    SIM_PUK2_REQUIRED,
    MEMORY_FULL=20,
    INVALID_INDEX,
    NOT_FOUND,
    MEMORY_FAILURE,
    TEXT_LONG,
    INVALID_CHAR_INTEXT,
    DAIL_STR_LONG,
    INVALID_CHAR_INDIAL,
    NO_NET_SERVICE=30,
    NETWORK_TIMOUT,
    NOT_ALLOW_EMERGENCY,
    NET_PER_PIN_REQUIRED=40,
    NET_PER_PUK_REQUIRED,
    NET_SUB_PER_PIN_REQ,
    NET_SUB_PER_PUK_REQ,
    SERVICE_PROV_PER_PIN_REQ,
    SERVICE_PROV_PER_PUK_REQ,
    CORPORATE_PER_PIN_REQ,
    CORPORATE_PER_PUK_REQ,
    PHSIM_PBK_REQUIRED,
    EXE_NOT_SURPORT,
    EXE_FAIL,
    NO_MEMORY,
    OPTION_NOT_SURPORT,
    PARAM_INVALID,
    EXT_REG_NOT_EXIT,
    EXT_SMS_NOT_EXIT,
    EXT_PBK_NOT_EXIT,
    EXT_FFS_NOT_EXIT,
    INVALID_COMMAND_LINE,
    GPRS_ILLEGAL_MS_3=103,
    GPRS_ILLEGAL_MS_6=106,
    GPRS_SVR_NOT_ALLOWED,
    GPRS_PLMN_NOT_ALLOWED=111,
    GPRS_LOCATION_AREA_NOT_ALLOWED,
    GPRS_ROAMING_NOT_ALLOWED,
    GPRS_OPTION_NOT_SUPPORTED=132,
    GPRS_OPTION_NOT_SUBSCRIBED,
    GPRS_OPTION_TEMP_ORDER_OUT,
    GPRS_UNSPECIFIED_GPRS_ERROR=148,
    GPRS_PDP_AUTHENTICATION_FAILURE,
    GPRS_INVALID_MOBILE_CLASS,
    SIM_VERIFY_FAIL=264,
    SIM_UNBLOCK_FAIL,
    SIM_CONDITION_NO_FULLFILLED,
    SIM_UNBLOCK_FAIL_NO_LEFT,
    SIM_VERIFY_FAIL_NO_LEFT,
    SIM_INVALID_PARAMETER,
    SIM_UNKNOW_COMMAND,
    SIM_WRONG_CLASS,
    SIM_TECHNICAL_PROBLEM,
    SIM_CHV_NEED_UNBLOCK,
    SIM_NOEF_SELECTED,
    SIM_FILE_UNMATCH_COMMAND,
    SIM_CONTRADICTION_CHV,
    SIM_CONTRADICTION_INVALIDATION,
    SIM_MAXVALUE_REACHED,
    SIM_PATTERN_NOT_FOUND,
    SIM_FILEID_NOT_FOUND,
    SIM_STK_BUSY,
    SIM_UNKNOW,
    SIM_PROFILE_ERROR
} CME_error_t;

typedef enum {
    UNASSIGNED_NUM=1,
    OPER_DETERM_BARR=8,
    CALL_BARRED=10,
    SM_TRANS_REJE=21,
    DEST_OOS=27,
    UNINDENT_SUB,
    FACILIT_REJE,
    UNKONWN_SUB,
    NW_OOO=38,
    TMEP_FAIL=41,
    CONGESTION,
    RES_UNAVAILABLE=47,
    REQ_FAC_NOT_SUB=50,
    RFQ_FAC_NOT_IMP=69,
    INVALID_SM_TRV=81,
    INVALID_MSG=95,
    INVALID_MAND_INFO,
    MSG_TYPE_ERROR,
    MSG_NOT_COMP,
    INFO_ELEMENT_ERROR,
    PROT_ERROR=111,
    IW_UNSPEC=127,
    TEL_IW_NOT_SUPP,
    SMS_TYPE0_NOT_SUPP,
    CANNOT_REP_SMS,
    UNSPEC_TP_ERROR=143,
    DCS_NOT_SUPP,
    MSG_CLASS_NOT_SUPP,
    UNSPEC_TD_ERROR=159,
    CMD_CANNOT_ACT,
    CMD_UNSUPP,
    UNSPEC_TC_ERROR=175,
    TPDU_NOT_SUPP,
    SC_BUSY=192,
    NO_SC_SUB,
    SC_SYS_FAIL,
    INVALID_SME_ADDR,
    DEST_SME_BARR,
    SM_RD_SM,
    TP_VPF_NOT_SUPP,
    TP_VP_NOT_SUPP,
    D0_SIM_SMS_STO_FULL=208,
    NO_SMS_STO_IN_SIM,
    ERR_IN_MS,
    MEM_CAP_EXCCEEDED,
    SIM_APP_TK_BUSY,
    SIM_DATA_DL_ERROR,
    UNSPEC_ERRO_CAUSE=255,
    ME_FAIL=300,
    SMS_SERVIEC_RESERVED,
    OPER_NOT_ALLOWED,
    OPER_NOT_SUPP,
    INVALID_PDU_PARAM,
    INVALID_TXT_PARAM,
    SIM_NOT_INSERT=310,
    CMS_SIM_PIN_REQUIRED,
    PH_SIM_PIN_REQUIRED=312,
    SIM_FAIL,
    CMS_SIM_BUSY,
    CMS_SIM_WRONG,
    CMS_SIM_PUK_REQUIRED,
    CMS_SIM_PIN2_REQUIRED,
    CMS_SIM_PUK2_REQUIRED,
    MEM_FAIL=320,
    INVALID_MEM_INDEX,
    MEM_FULL,
    SCA_ADDR_UNKNOWN=330,
    NO_NW_SERVICE,
    NW_TIMEOUT,
    NO_CNMA_ACK_EXPECTED=340,
    UNKNOWN_ERROR=500,
    USER_ABORT=512, // TIMER_EXPIRED
    UNABLE_TO_STORE,
    INVALID_STATUS,
    INVALID_ADDR_CHAR,
    INVALID_LEN,
    INVALID_PDU_CHAR,
    INVALID_PARA,
    INVALID_LEN_OR_CHAR,
    INVALID_TXT_CHAR
} CMS_error_t;

class A9Gdriver
{
    public:

        /**
         * Passes the Serial (software or hardware) connected to the A9(G)
         * to be driven directly by the library. The Serial MUST had been
         * initialized externally at 115200 baud, prior to pass the serial
         * to this function
         */
        A9Gdriver(Stream& serial);

        // GENERAL FUNCTIONS

        void init();
        void sendRst(A9G_shdn_level_t type);

        // GPS FUNCTIONS

        bool GPS_setStatus(bool enable); // GPS
        bool GPS_getStatus();   // GPS?

        // GPRS FUNCTIONS

        void NET_attach(bool enable); // CGATT
        void NET_setPDP(int profile, const char * APN);  // CGDCONT
        void NET_activatePDP(int profile, bool activate); // CGACT

        // HTTP FUNCTIONS

        void HTTP_sendGet(String url); // HTTPGET
        void HTTP_sendPost(String url,String contentType, String bodyContent); // HTTPPOST

        // MQTT FUNCTIONS

        void MQTT_connect(const char * server, uint16_t port, String clientID, uint16_t aliveSeconds, bool cleanSession, const char * username, const char * password);    // MQTTCONN
        void MQTT_pub(const char * topic, String payload, uint8_t qos, bool dup, bool remain);    // MQTTPUB
        void MQTT_pub(const char * topic, CayenneLPP payload, uint8_t qos, bool dup, bool remain);    // MQTTPUB
        void MQTT_sub(String topic, bool sub, uint8_t qos);    // MQTTSUB
        void MQTT_disconnect(); // MQTTDISCONN

    protected:
        Stream& _serial;
        void _dropRx();
        void _flushTx();
        void _sendComm(String command); // AT+
        void _sendCommln(String command); // AT+
        void _sendLongString(const char * str);
        void _sendBuffer(const char * buffer, size_t size);
        bool _catchRx(String needle);
};

#endif // A9G_AT_COMMANDS_H !def
