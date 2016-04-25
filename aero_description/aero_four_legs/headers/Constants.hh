#ifndef AERO_CONTROLLER_CONSTANTS_H_
#define AERO_CONTROLLER_CONSTANTS_H_

namespace aero
{
  namespace controller
  {
    // header offset = 6bytes
    const static size_t RAW_HEADER_OFFSET = 6;
    // data length = 77bytes
    const static size_t RAW_DATA_LENGTH = 77;
    // id: upper = 1, lower = 2
    const static uint8_t ID_UPPER = 1;
    const static uint8_t ID_LOWER = 2;

    // whole: 34DOF
    //  upper: 22DOF
    //   neck: 3DOF
    //   arm: 8DOF (including hand) * 2
    //    shoulder: 2DOF * 2
    //    elbow: 2DOF * 2
    //    wrist: 3DOF * 2
    //    hand: 1DOF * 2
    //   waist: 3DOF
    //  lower (4LEGS) : 12DOF
    //   leg: 3DOF * 4
    //    crotch: 2DOF * 4
    //    knee: 1DOF * 4
    //    (wheel: 1DOF * 4)

    const static size_t AERO_DOF = 34;
    const static size_t AERO_DOF_UPPER = 22;
    const static size_t AERO_DOF_LOWER = 12;
    const static size_t AERO_DOF_WHEEL = 4;

    // joint index in stroke vector
    // UPPER:
    const static size_t CAN_NECK_Y = 0;
    const static size_t CAN_NECK_RIGHT = 1;
    const static size_t CAN_NECK_LEFT = 2;

    const static size_t CAN_R_SHOULDER_P = 3;
    const static size_t CAN_R_SHOULDER_R = 4;
    const static size_t CAN_R_ELBOW_Y = 5;
    const static size_t CAN_R_ELBOW_P = 6;
    const static size_t CAN_R_WRIST_Y = 7;
    const static size_t CAN_R_WRIST_TOP = 8;
    const static size_t CAN_R_WRIST_BOTTOM = 9;
    const static size_t CAN_R_HAND = 10;

    const static size_t CAN_L_SHOULDER_P = 11;
    const static size_t CAN_L_SHOULDER_R = 12;
    const static size_t CAN_L_ELBOW_Y = 13;
    const static size_t CAN_L_ELBOW_P = 14;
    const static size_t CAN_L_WRIST_Y = 15;
    const static size_t CAN_L_WRIST_TOP = 16;
    const static size_t CAN_L_WRIST_BOTTOM = 17;
    const static size_t CAN_L_HAND = 18;

    const static size_t CAN_WAIST_RIGHT = 19;
    const static size_t CAN_WAIST_LEFT = 20;
    const static size_t CAN_WAIST_Y = 21;

    // LOWER (4 LEGS):
    const static size_t CAN_FRONT_R_CROTCH_Y = 0;
    const static size_t CAN_FRONT_R_CROTCH_P = 1;
    const static size_t CAN_FRONT_R_KNEE_P = 2;

    const static size_t CAN_REAR_R_CROTCH_Y = 3;
    const static size_t CAN_REAR_R_CROTCH_P = 4;
    const static size_t CAN_REAR_R_KNEE_P = 5;

    const static size_t CAN_FRONT_L_CROTCH_Y = 6;
    const static size_t CAN_FRONT_L_CROTCH_P = 7;
    const static size_t CAN_FRONT_L_KNEE_P = 8;

    const static size_t CAN_REAR_L_CROTCH_Y = 9;
    const static size_t CAN_REAR_L_CROTCH_P = 10;
    const static size_t CAN_REAR_L_KNEE_P = 11;

    // WHEEL:
    const static size_t CAN_FRONT_R_WHEEL = 0;
    const static size_t CAN_REAR_R_WHEEL = 1;
    const static size_t CAN_FRONT_L_WHEEL = 2;
    const static size_t CAN_REAR_L_WHEEL = 3;


    // joint index in raw vector (as int16_t)
    // UPPER: ID = 1
    const static size_t RAW_NECK_Y = 0;
    const static size_t RAW_NECK_RIGHT = 1;
    const static size_t RAW_NECK_LEFT = 2;
    const static size_t RAW_R_SHOULDER_P = 3;
    const static size_t RAW_R_SHOULDER_R = 4;
    const static size_t RAW_R_ELBOW_Y = 5;
    const static size_t RAW_R_ELBOW_P = 6;
    const static size_t RAW_R_WRIST_Y = 7;
    const static size_t RAW_R_WRIST_TOP = 8;
    const static size_t RAW_R_WRIST_BOTTOM = 9;
    const static size_t RAW_WAIST_RIGHT = 10;
    const static size_t RAW_R_HAND = 11;
    // 12 - 15: Force Sensor (uint8_t * 6, 2bytes N/A)
    const static size_t RAW_WAIST_Y = 16;
    // 17 - 18: N/A
    const static size_t RAW_L_SHOULDER_P = 19;
    const static size_t RAW_L_SHOULDER_R = 20;
    const static size_t RAW_L_ELBOW_Y = 21;
    const static size_t RAW_L_ELBOW_P = 22;
    const static size_t RAW_L_WRIST_Y = 23;
    const static size_t RAW_L_WRIST_TOP = 24;
    const static size_t RAW_L_WRIST_BOTTOM = 25;
    const static size_t RAW_WAIST_LEFT = 26;
    const static size_t RAW_L_HAND = 27;
    // 28 - 31: Force Sensor (uint8_t * 6, 2bytes N/A)
    // 32 - 34: N/A

    // LOWER (4 LEGS):
    const static size_t RAW_FRONT_R_CROTCH_Y = 0;
    const static size_t NA_FRONT_R_CROTCH_P = 1;  // slave, N/A
    const static size_t RAW_FRONT_R_CROTCH_P = 2;
    const static size_t NA_FRONT_R_KNEE_P = 3;  // slave, N/A
    const static size_t RAW_FRONT_R_KNEE_P = 4;
    const static size_t RAW_FRONT_R_WHEEL = 5;
    const static size_t RAW_REAR_R_CROTCH_Y = 6;
    const static size_t NA_REAR_R_CROTCH_P = 7;  // slave, N/A
    const static size_t RAW_REAR_R_CROTCH_P = 8;
    const static size_t NA_REAR_R_KNEE_P = 9;  // slave, N/A
    const static size_t RAW_REAR_R_KNEE_P = 10;
    const static size_t RAW_REAR_R_WHEEL = 11;
    // 12 - 15: N/A
    const static size_t RAW_FRONT_L_CROTCH_Y = 16;
    const static size_t NA_FRONT_L_CROTCH_P = 17;  // slave, N/A
    const static size_t RAW_FRONT_L_CROTCH_P = 18;
    const static size_t NA_FRONT_L_KNEE_P = 19;  // slave, N/A
    const static size_t RAW_FRONT_L_KNEE_P = 20;
    const static size_t RAW_FRONT_L_WHEEL = 21;
    const static size_t RAW_REAR_L_CROTCH_Y = 22;
    const static size_t NA_REAR_L_CROTCH_P = 23;  // slave, N/A
    const static size_t RAW_REAR_L_CROTCH_P = 24;
    const static size_t NA_REAR_L_KNEE_P = 25;  // slave, N/A
    const static size_t RAW_REAR_L_KNEE_P = 26;
    const static size_t RAW_REAR_L_WHEEL = 27;
    // 28 - 31: N/A
    // 32 - 34: IMU (uint8_t * 6)

    // offsets
    // UPPER:
    const static size_t OFFSET_R_SHOULDER_R = 1119;
    const static size_t OFFSET_R_HAND = -900;
    const static size_t OFFSET_L_SHOULDER_R = 1119;
    const static size_t OFFSET_L_HAND = -900;

    //LOWER:
    const static size_t OFFSET_FRONT_R_CROTCH_Y = 3500;
    const static size_t OFFSET_FRONT_R_KNEE_P = 650;
    const static size_t OFFSET_REAR_R_CROTCH_Y = -3500;
    const static size_t OFFSET_REAR_R_KNEE_P = 650;
    const static size_t OFFSET_FRONT_L_CROTCH_Y = -3500;
    const static size_t OFFSET_FRONT_L_KNEE_P = 650;
    const static size_t OFFSET_REAR_L_CROTCH_Y = 3500;
    const static size_t OFFSET_REAR_L_KNEE_P = 650;


    // sensor index (as int8_t)
    // UPPER:
    const static size_t RIGHT_HAND_SENSOR_FX = 30;
    const static size_t RIGHT_HAND_SENSOR_FY = 31;
    const static size_t RIGHT_HAND_SENSOR_FZ = 32;
    const static size_t RIGHT_HAND_SENSOR_RX = 33;
    const static size_t RIGHT_HAND_SENSOR_RY = 34;
    const static size_t RIGHT_HAND_SENSOR_RZ = 35;

    const static size_t LEFT_HAND_SENSOR_FX = 62;
    const static size_t LEFT_HAND_SENSOR_FY = 63;
    const static size_t LEFT_HAND_SENSOR_FZ = 64;
    const static size_t LEFT_HAND_SENSOR_RX = 65;
    const static size_t LEFT_HAND_SENSOR_RY = 66;
    const static size_t LEFT_HAND_SENSOR_RZ = 67;

    // LOWER (4LEGS has only IMU):
    const static size_t IMU_AX = 70;
    const static size_t IMU_AY = 71;
    const static size_t IMU_AZ = 72;
    const static size_t IMU_GX = 73;
    const static size_t IMU_GY = 74;
    const static size_t IMU_GZ = 75;

    // command list
    const static uint8_t CMD_MOTOR_CUR = 0x20;
    const static uint8_t CMD_MOTOR_ACC = 0x24;
    const static uint8_t CMD_MOTOR_GAIN = 0x25;
    const static uint8_t CMD_GET_POS = 0x42;
    const static uint8_t CMD_GET_CUR = 0x43;
    const static uint8_t CMD_GET_TMP = 0x45;
    const static uint8_t CMD_MOTOR_SRV = 0x50;
    const static uint8_t CMD_MOVE_INC = 0x67;
    const static uint8_t CMD_MOVE_ABS = 0x68;
  }
}

#endif
