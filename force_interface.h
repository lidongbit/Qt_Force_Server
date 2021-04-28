#ifndef __SERVO_FORCE_H__
#define __SERVO_FORCE_H__

#include <stdint.h>

typedef struct
{
    int32_t arm;    // 1: right arm, -1:left arm
    int32_t elbow;  // 1: elbow above wrist, -1:elbow below wrist
    int32_t wrist;  // 1: wrist down, -1: wrist up
    int32_t flip;   // 0: not flip wrist, 1: flip wrist

    int32_t dh_d1;
    int32_t dh_a1;
    int32_t dh_alpha1;
    int32_t dh_offset1;
    int32_t dh_d2;
    int32_t dh_a2;
    int32_t dh_alpha2;
    int32_t dh_offset2;
    int32_t dh_d3;
    int32_t dh_a4;
    int32_t dh_alpha4;
    int32_t dh_offset4;
    int32_t dh_d4;
    int32_t dh_a5;
    int32_t dh_alpha5;
    int32_t dh_offset5;
    int32_t dh_d6;
    int32_t dh_a6;
    int32_t dh_alpha6;
    int32_t dh_offset6;

    int32_t base_rmtx_0_0;
    int32_t base_rmtx_0_1;
    int32_t base_rmtx_0_2;
    int32_t base_rmtx_1_0;
    int32_t base_rmtx_1_1;
    int32_t base_rmtx_1_2;
    int32_t base_rmtx_2_0;
    int32_t base_rmtx_2_1;
    int32_t base_rmtx_2_2;
    int32_t base_p_x;
    int32_t base_p_y;
    int32_t base_p_z;

    int32_t bd_v1;
    int32_t bd_v2;
    int32_t bd_v3;
    int32_t bd_v4;
    int32_t bd_v5;
    int32_t bd_v6;

    int32_t kd_v1;
    int32_t kd_v2;
    int32_t kd_v3;
    int32_t kd_v4;
    int32_t kd_v5;
    int32_t kd_v6;

    int32_t md_v1;
    int32_t md_v2;
    int32_t md_v3;
    int32_t md_v4;
    int32_t md_v5;
    int32_t md_v6;

    int32_t imped_kp_1;
    int32_t imped_ki_1;
    int32_t imped_kd_1;
    int32_t imped_kp_2;
    int32_t imped_ki_2;
    int32_t imped_kd_2;
    int32_t imped_kp_3;
    int32_t imped_ki_3;
    int32_t imped_kd_3;
    int32_t imped_kp_4;
    int32_t imped_ki_4;
    int32_t imped_kd_4;
    int32_t imped_kp_5;
    int32_t imped_ki_5;
    int32_t imped_kd_5;
    int32_t imped_kp_6;
    int32_t imped_ki_6;
    int32_t imped_kd_6;

    int32_t adnit_kp_1;
    int32_t adnit_ki_1;
    int32_t adnit_kd_1;
    int32_t adnit_kp_2;
    int32_t adnit_ki_2;
    int32_t adnit_kd_2;
    int32_t adnit_kp_3;
    int32_t adnit_ki_3;
    int32_t adnit_kd_3;
    int32_t adnit_kp_4;
    int32_t adnit_ki_4;
    int32_t adnit_kd_4;
    int32_t adnit_kp_5;
    int32_t adnit_ki_5;
    int32_t adnit_kd_5;
    int32_t adnit_kp_6;
    int32_t adnit_ki_6;
    int32_t adnit_kd_6;
}PARA_FORCE_STD_INFO_t;//(4+90)*4


typedef struct
{
    int32_t update_flag;
    int32_t rsv_data;
    int32_t posture[4];
    double  para_data[90];
    double  para_rsv[35];
}PARA_FORCE_INFO_t;		//1024 Bytes


/********************service and feedback**********************/
typedef struct
{
    int32_t cmd;		//reference SERVO_CMD_e
    int32_t param1;
    int32_t param2;
    int32_t param3;
    int32_t param4;
    int32_t param5;
    int32_t param6;
    int32_t param7;
}ServoCoreProcessCall_t;
typedef struct
{
    int32_t param1;
    int32_t param2;
    int32_t param3;
    int32_t param4;
    int32_t param5;
    int32_t param6;
    int32_t param7;
    int32_t param8;
}ForceCoreProcessBack_t;


/******************Instruction*****************/
typedef struct{
    int32_t valid;
    int32_t not_used;
    double in_pos_given[6];
    double in_vel_given[6];
    double in_acc_given[6];
    double in_force_given[6];

    double in_pos_back[6];
    double in_vel_back[6];
    double in_acc_back[6];
    double in_force_back[6];
}FORCE_INSTRUCTION_INFO_t;

/**************************result feedback*************************/
typedef struct{
    int32_t valid;
    int32_t err_code;		//reference FORCE_ERR_CODE_e
    int32_t err_history[4];	//reference FORCE_ERR_CODE_e
    int32_t state;			//reference FORCE_CORE_STATE_e
    int32_t mode;			//reference FORCE_WORK_MODE_e
    int32_t sub_mode;		//reference FORCE_WORK_SUB_MODE_e
    int32_t rsv_data;
}FORCE_CORE_STATE_t;

typedef struct{
    int32_t valid;
    int32_t theta[6];
    int32_t force[6];
    int32_t dignose_var[6][16];
    int32_t rsv_data;
}FORCE_BACK_INFO_t;

/*****************************enums********************************/
typedef enum FORCE_WORK_MODE
{
    NO_MODE = 0,
    IMPEDANCE_MODE = 1,
    ADMITTANCE_MODE = 2,
}FORCE_WORK_MODE_e;

typedef enum FORCE_WORK_SUB_MODE
{
    NO_SUB_MODE = 0,
    TEACH = 1,
    LEARN = 2,
}FORCE_WORK_SUB_MODE_e;

typedef enum{
     /*state machine control*/
        CMD_WORKING = 0x01,
        CMD_IDLE = 0x02,
        CMD_SET_FAULT = 0x03,
        CMD_RESET_FAULT = 0x04,
        /*change mode*/
        CMD_SWITCH_MODE = 0x05,
        /*dignose config*/
        CMD_DIGNOSE_CONFIG = 0x06,
        CMD_GET_STATE = 0x07,
        CMD_SERVO_MAX = CMD_GET_STATE + 1,


}SERVO_CMD_e;

typedef enum
{
    NO_MODULE = 0x00,
    PARAM_MOUDLE = 0x01,
    ADNITTANCE_MOUDLE = 0x02,//dao na
    IMPEDANCE_MOUDLE = 0x03,//zu kang
    INSTRUCTION_MOUDLE = 0x04,//zhiling
    KINEMATIC_MOUDLE = 0x05,//forward kinematic
    KINEMATIC_INV_MOUDLE = 0x06,//inverse kinematic
    SERVO_COMM_MOUDLE = 0x07,//communication module
    DIFF_MOTION_MOUDLE = 0x08,
    MODULE_MAX = DIFF_MOTION_MOUDLE +1,
}FORCE_MODULE_e;

typedef enum
{
    HEART_ERR = 0x01,/*communication error*/
    CMD_ERR = 0x02,/*communication error*/
    INSTRUCTION_LOSE_ERR = 0x03,/*instruction buff empty*/
    INSTRUCTION_OVER_LIMIT_ERR = 0x04,/*instruction invalid*/
    RESULT_PUSH_ERR = 0x05,/*result buff full*/
    DIVED_ZERO = 0x06,
    KINEMATIC_CALC_ERR = 0x07,
    DIFF_CALC_ERR = 0x08,
    KINEMATIC_INV_CALC_ERR = 0x09,
}FORCE_ERR_CODE_e;

typedef enum
{
    POS_POSEULAR_GIVEN,
    THETA_BACK,
    THETA_BACK_TO_POS_EULAR,
    THETA_BACK_TO_POS_QUANT,
    OUT_POS_COMP,
    IN_FORCE_GIVEN_BASE,
    IN_FORCE_BACK_TOOL,
    IN_FORCE_BACK_BASE,
    FORCE_ERR_BASE,
    OUT_THETA,
    PID_ERR,
    PID_OUT,
    FVAR_MAX = PID_OUT + 1,
}FORCE_DIGNOSE_VAR_e;

typedef enum FORCE_CORE_STATE
{
    SM_BOOT = 0,
    SM_INIT = 1,
    SM_IDLE = 2,
    SM_WORKING = 3,
    SM_ABORT = 4,
    SM_ERROR = 5,
}FORCE_CORE_STATE_e;

#endif

