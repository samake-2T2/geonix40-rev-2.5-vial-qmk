#pragma once

#include "quantum.h"
#include "debounce.h"
#include "usb_descriptor.h"
#include "usb_main.h"
#include "raw_hid.h"

/************************IO 口**************************/
/************************IO 口**************************/
/************************IO 口**************************/
#define ES_BATT_STDBY_IO    (A13)
#define ES_USB_POWER_IO     (C5)
#define ES_SPI_ACK_IO       (A4)
#define ES_PWM_DMA_IO       (A2)

#define ES_WUKEUP_IO        (D1)
#define ES_SDB_POWER_IO     (A3)
#define ES_LED_POWER_IO     (D0)

/************************SPI 命令**************************/
/************************SPI 命令**************************/
/************************SPI 命令**************************/
#define USER_EMI_COMMAND	    0XBB
#define USER_KEYBOARD_COMMAND	0X0A
#define USER_KEYBOARD_LENGTH    (64)

#define USER_SWITCH_2P4G_MODE	0X00
#define USER_SWITCH_BLE_1_MODE	0X01
#define USER_SWITCH_BLE_2_MODE	0X02
#define USER_SWITCH_BLE_3_MODE	0X03
#define USER_SWITCH_2P4G_PAIR	0X04
#define USER_SWITCH_BLE_1_PAIR	0X05
#define USER_SWITCH_BLE_2_PAIR	0X06
#define USER_SWITCH_BLE_3_PAIR	0X07
#define USER_SWITCH_USB_MODE	0X08

#define USER_KEYBOARD_SLEEP		0X09
#define USER_KEYBOARD_WAKEUP	0X0A

#define USER_KEY_BYTE_DATA		0X0B
#define USER_KEY_BIT_DATA		0X0C
#define USER_MOUSE_DATA			0X0D
#define USER_CONSUMER_DATA		0X0E
#define USER_SYSTEM_DATA		0X0F

#define USER_BATTERY_DATA		0X10

#define USER_GET_RF_STATUS	    0X11

#define USER_BLE1_WRITE_NAME	0X12
#define USER_BLE2_WRITE_NAME    0X13
#define USER_BLE3_WRITE_NAME    0X14

#define USER_SLEEP_TIME_WRITE   0X15       // 一级休眠时间
#define USER_DSLEEP_TIME_WRITE  0X16       // 二级休眠时间

#define USER_KEY_BYTE_LENGTH	0X08
#define USER_KEY_BIT_LENGTH		0X0F
#define USER_MOUSE_LENGTH		0X08
#define USER_CONSUMER_LENGTH	0X03
#define USER_SYSTEM_LENGTH		0X03
#define USER_BATTERY_LENGTH		0X02

#define KB_REPORT_ID            0x06    // Extend keyboard report ID.
#define SYS_REPORT_ID     	    0x03    // Extend System   report ID.
#define CON_REPORT_ID     	    0x04    // Extend Consumer report ID.
#define MOUSE_REPORT_ID  	    0x02    // Extend mouse	   report ID.

#define LOGO_LED_ENABLE         (1)
#define SIDE_LED_ENABLE         (0)

#define USER_DEFINE_KEY         (QK_KB)
enum Custom_Keycodes {
    QMK_KB_MODE_2P4G = USER_DEFINE_KEY,
    QMK_KB_MODE_BLE1,
    QMK_KB_MODE_BLE2,
    QMK_KB_MODE_BLE3,
    QMK_KB_MODE_USB,
    QMK_BATT_NUM,
    QMK_WIN_LOCK,
    QMK_KB_SIX_N_CH,
    RGB_RTOG,
    U_EE_CLR,
    USER_CHANGE,
    QMK_DEBOUNCE,
    QMK_TIME_SET,
    QMK_DTIME_SET,
    QMK_TEST_COLOUR,
#if LOGO_LED_ENABLE
    LOGO_TOG,
    LOGO_MOD,
    LOGO_RMOD,
    LOGO_HUI,
    LOGO_HUD,
    LOGO_SAI,
    LOGO_SAD,
    LOGO_VAI,
    LOGO_VAD,
    LOGO_SPI,
    LOGO_SPD,
#endif
    QMK_LED_RESET,
#if SIDE_LED_ENABLE
    SIDE_TOG,
    SIDE_MOD,
    SIDE_RMOD,
    SIDE_HUI,
    SIDE_HUD,
    SIDE_SAI,
    SIDE_SAD,
    SIDE_VAI,
    SIDE_VAD,
    SIDE_SPI,
    SIDE_SPD,
#endif
    QMK_KB_2P4G_PAIR,
    QMK_KB_BLE1_PAIR,
    QMK_KB_BLE2_PAIR,
    QMK_KB_BLE3_PAIR
};

enum Custom_KeyModes {
    QMK_BLE_MODE = 0,
    QMK_2P4G_MODE,
    QMK_USB_MODE
};

enum Custom_BleChannels {
    QMK_BLE_CHANNEL_1 = 1,
    QMK_BLE_CHANNEL_2,
    QMK_BLE_CHANNEL_3
};

enum Custom_Spi_Ack_S {
    SPI_NACK,
    SPI_ACK
};

enum Custom_Spi_Busy_S {
    SPI_BUSY,
    SPI_IDLE
};

enum Custom_Ble_24G_Status_S {
    BLE_24G_NONE,
    BLE_24G_PIAR,
    BLE_24G_RETURN
};

typedef struct {
    uint8_t Key_Mode;               // 键盘工作模式
    uint8_t Key_Mode_Old;           // 上一次的键盘工作模式
    uint8_t Ble_Channel;            // 蓝牙通道
    uint8_t Batt_Number;            // 电池电量
    uint8_t Nkro;                   // 六键全键无冲
    uint8_t Mac_Win_Mode;           // MAC系统WIN系统
    uint8_t Win_Lock;               // 锁WIN
    uint8_t Led_On_Off;             // 背光开关
    uint8_t Debounce_Delay;         // 按键消抖
    uint32_t User_Sleep_Time;       // 一级休眠
    uint32_t User_DSleep_Time;      // 二级休眠
#if LOGO_LED_ENABLE
    uint8_t Logo_On_Off;            // LOGO灯光开关
    uint8_t Logo_Mode;              // LOGO灯光模式
    uint8_t Logo_Colour;            // LOGO灯光颜色
    uint8_t Logo_Saturation;        // LOGO灯光饱和度
    uint8_t Logo_Brightness;        // LOGO灯光亮度
    uint8_t Logo_Speed;             // LOGO灯光速度
#endif
#if SIDE_LED_ENABLE
    uint8_t Side_On_Off;            // 测灯灯光开关
    uint8_t Side_Mode;              // 测灯灯光模式
    uint8_t Side_Colour;            // 测灯灯光颜色
    uint8_t Side_Saturation;        // 测灯灯光饱和度
    uint8_t Side_Brightness;        // 测灯灯光亮度
    uint8_t Side_Speed;             // 测灯灯光速度
#endif
} Keyboard_Info_t;

typedef struct {
    uint8_t System_Work_Status;     // 系统状态
    uint8_t System_Work_Mode;       // 工作模式
    uint8_t System_Work_Channel;    // 工作通道
    uint8_t System_Connect_Status;  // 连接状态
    uint8_t System_Led_Status;      // 系统指示灯
    uint8_t System_Sleep_Mode;      // 系统休眠
} Keyboard_Status_t;

typedef enum {
    KB_MODE_CONNECT_OK,  	        //连接成功
    KB_MODE_CONNECT_PAIR,	        //配对
    KB_MODE_CONNECT_RETURN,	        //回连
} keyboard_System_state_e;

typedef enum {
    USER_SLEEP_PASS,	            //休眠成功
    USER_SLEEP_FIAL,	            //休眠失败
} keyboard_System_Sleep_Status_s;

#define INIT_WORK_MODE              (QMK_USB_MODE)                                          // 默认工作模式
#define INIT_BLE_CHANNEL            (QMK_BLE_CHANNEL_1)                                     // 默认蓝牙通道
#define INIT_BATT_NUMBER            (50)                                                    // 上电的默认电池电量

#define INIT_SIX_KEY                (0)                                                     // 六键
#define INIT_ALL_KEY                (1)                                                     // 全键
#define INIT_ALL_SIX_KEY            (INIT_ALL_KEY)                                          // 全键

#define INIT_WIN_MODE               (0)                                                     // Windows
#define INIT_MAC_MODE               (1)                                                     // Mac
#define INIT_WIN_MAC_MODE           (INIT_WIN_MODE)                                         // Windows

#define INIT_WIN_NLOCK              (0)                                                     // 不锁WIN
#define INIT_WIN_LOCK               (1)                                                     // 锁WIN
#define INIT_WIN_LOCK_NLOCK         (INIT_WIN_NLOCK)                                        // 不锁WIN

#define INIT_LED_ON                 (0)                                                     // 开背光
#define INIT_LED_OFF                (1)                                                     // 不开背光
#define INIT_LED_ON_OFF             (INIT_LED_ON)                                           // 开背光

#define DEBOUNCE_DELAY_ONE          (2)                                                     // 消抖等级1
#define DEBOUNCE_DELAY_TWO          (5)                                                     // 消抖等级2
#define DEBOUNCE_DELAY_CLASS        (DEBOUNCE_DELAY_TWO)  

#define SLEEP_TIME_ONE              (60)                                                    // 休眠时间1分钟
#define SLEEP_TIME_TWO              (180)                                                   // 休眠时间3分钟
#define SLEEP_TIME_THREE            (600)                                                   // 休眠时间10分钟
#define SLEEP_TIME_FOUR             (1800)                                                  // 休眠时间30分钟
#define SLEEP_TIME_CLASS            (SLEEP_TIME_TWO)                                        // 默认休眠10分钟

#define U_PWM                       (RGB_MATRIX_MAXIMUM_BRIGHTNESS)                         // 亮度

#if LOGO_LED_ENABLE
#define LOGO_LED_PLAY_SPEED	        (0)                                                     // 灯光刷新速度
#define LOGO_LED_SIZE	            (29)                                                     // 灯光数量

#define LOGO_LED_ON                 (0)                                                     // 灯光打开
#define LOGO_LED_OFF                (1)                                                     // 灯光关闭

#define LOGO_WAVE_RGB_MODE          (1)                                                     // 彩色波浪
#define LOGO_WAVE_DS_MODE           (2)                                                     // 单色波浪
#define LOGO_SPECTRUM_MODE          (3)                                                     // 光谱
#define LOGO_BREATH_MODE            (4)                                                     // 单色呼吸
#define LOGO_LIGHT_MODE             (5)                                                     // 单色常量
#define LOGO_OFF_MODE               (6)                                                     // 关闭

#define LOGO_MAX_COLOUR             (255)                                                   // 颜色最大
#define LOGO_MIN_COLOUR             (0)                                                     // 颜色最小
#define COLOUR_LEVEL                (15)                                                    // 颜色等级

#define LOGO_MAX_SATURATION         (0)                                                     // 饱和度最大
#define LOGO_MIN_SATURATION         (255)                                                   // 饱和度最小
#define SATURATION_LEVEL            (15)                                                    // 饱和度等级

#define LOGO_MAX_BRIGHTNESS         (RGB_MATRIX_MAXIMUM_BRIGHTNESS)                         // 亮度最大
#define LOGO_MIN_BRIGHTNESS         (0)                                                     // 亮度最小
#define BRIGHTNESS_LEVEL            (16)                                                    // 亮度等级

#define LOGO_MAX_SPEED              (4)                                                     // 速度最大
#define LOGO_MIN_SPEED              (0)                                                     // 速度最小
#define SPEED_LEVEL                 (1)                                                     // 速度等级

#define INIT_LOGO_ON_OFF            (LOGO_LED_ON)                                           // 灯光打开
#define INIT_LOGO_MODE              (LOGO_WAVE_RGB_MODE)                                    // 彩色波浪
#define INIT_LOGO_COLOUR            (LOGO_MIN_COLOUR)                                       // 颜色最小
#define INIT_LOGO_SATURATION        (LOGO_MAX_SATURATION)                                   // 饱和度最大
#define INIT_LOGO_BRIGHTNESS        (LOGO_MAX_BRIGHTNESS-BRIGHTNESS_LEVEL)                  // 亮度最大
#define INIT_LOGO_SPEED             (1)                                                     // 速度居中

void User_Via_Qmk_Logo_Get_Value(uint8_t *data);
void User_Via_Qmk_Logo_Set_Value(uint8_t *data);
void User_Via_Qmk_Logo_Command(uint8_t *data, uint8_t length);

#endif
//--------------------------------------------------------------------------------------------------------
#if SIDE_LED_ENABLE
#define SIDE_LED_PLAY_SPEED	        (0)                                                     // 灯光刷新速度
#define SIDE_LED_SIZE	            (30)                                                    // 灯光数量

#define SIDE_LED_ON                 (0)                                                     // 灯光打开
#define SIDE_LED_OFF                (1)                                                     // 灯光关闭

#define SIDE_WAVE_RGB_MODE          (1)                                                     // 彩色波浪
#define SIDE_WAVE_DS_MODE           (2)                                                     // 单色波浪
#define SIDE_SPECTRUM_MODE          (3)                                                     // 光谱
#define SIDE_BREATH_MODE            (4)                                                     // 单色呼吸
#define SIDE_LIGHT_MODE             (5)                                                     // 单色常量
#define SIDE_OFF_MODE               (6)                                                     // 关闭

#define SIDE_MAX_COLOUR             (160)                                                   // 颜色最大
#define SIDE_MIN_COLOUR             (0)                                                     // 颜色最小
#define SIDE_COLOUR_LEVEL           (15)                                                    // 颜色等级

#define SIDE_MAX_SATURATION         (0)                                                     // 饱和度最大
#define SIDE_MIN_SATURATION         (255)                                                   // 饱和度最小
#define SIDE_SATURATION_LEVEL       (15)                                                    // 饱和度等级

#define SIDE_MAX_BRIGHTNESS         (RGB_MATRIX_MAXIMUM_BRIGHTNESS)                         // 亮度最大
#define SIDE_MIN_BRIGHTNESS         (0)                                                     // 亮度最小
#define SIDE_BRIGHTNESS_LEVEL       (15)                                                    // 亮度等级

#define SIDE_MAX_SPEED              (4)                                                     // 速度最大
#define SIDE_MIN_SPEED              (0)                                                     // 速度最小
#define SIDE_SPEED_LEVEL            (1)                                                     // 速度等级

#define INIT_SIDE_ON_OFF            (SIDE_LED_ON)                                           // 灯光打开
#define INIT_SIDE_MODE              (SIDE_WAVE_RGB_MODE)                                    // 彩色波浪
#define INIT_SIDE_COLOUR            (SIDE_MIN_COLOUR)                                       // 颜色最小
#define INIT_SIDE_SATURATION        (SIDE_MAX_SATURATION)                                   // 饱和度最大
#define INIT_SIDE_BRIGHTNESS        (SIDE_MAX_BRIGHTNESS)                                   // 亮度最大
#define INIT_SIDE_SPEED             (2)                                                     // 速度居中

void User_Via_Qmk_Side_Get_Value(uint8_t *data);
void User_Via_Qmk_Side_Set_Value(uint8_t *data);
void User_Via_Qmk_Side_Command(uint8_t *data, uint8_t length);

#endif

#define APP_2G4_BUF_SIZE            (USER_KEYBOARD_LENGTH)
#define APP_2G4_BUF_CNT             (20)

#define USER_BATT_POWER_SCAN_COUNT  (10)
#define USER_BATT_SCAN_COUNT        (10)

#define USER_BATT_HIGH_POWER        (2555)      //满电 2565 * 3.3 /4096 = 2.066 4.13V     实际电路存在压降。
#define USER_BATT_LOW_POWER         (2065)      //低电 2065 * 3.3 /4096 = 1.663 3.32V     即使键盘不开灯，电池满电4.2V
#define USER_BATT_STDOWN_POWER      (1865)      //关机 1865 * 3.3 /4096 = 1.502 3.04V     输入到板子也就只有4.1V左右

#define USER_BATT_DELAY_TIME        (100 * 25)  //25S
#define USER_TIME_3S_TIME           (300)       //3S
#define USER_TIME_2S_TIME           (200)       //2S

#define SPI_DELAY_RF_TIME           (60)
#define SPI_DELAY_USB_TIME          (500 * 3)

void User_Sleep(void);
void Emi_Read_Data(uint8_t *User_Data, uint8_t User_Length);
void Emi_Write_Data(uint8_t *User_Data, uint8_t User_Length);

#define MAX_NAME_LEN                (18)
#define USER_BlE_ID                 (0X1115)
#define USER_BlE1_NAME              "GEONIX REV.2.5"
#define USER_BlE2_NAME              "GEONIX REV.2.5"
#define USER_BlE3_NAME              "GEONIX REV.2.5"

#define USER_DSLEEP_TIME            0X147AE0 //二级休眠时间 单位 S

#define KEYBAORD_COL                (12)
#define KEYBAORD_ROL                (4)
#define MATRIX_USER_COL_PINS        { D15, D14, C15, C14, C13, D3, D2, C12, C11, C10, A14, C9 }
#define MATRIX_USER_ROW_PINS        { B0, B4, B5, B6}

#define WIN_COL                     (7)
#define WIN_ROL                     (0)

#define MAC_COL                     (6)
#define MAC_ROL                     (0)

#define KC_K29 	 KC_BACKSLASH
#define KC_K42 	 KC_NONUS_HASH
#define KC_K45 	 KC_NONUS_BACKSLASH
#define KC_K56 	 KC_INTERNATIONAL_1
#define KC_K14   KC_INTERNATIONAL_3
#define KC_K132	 KC_INTERNATIONAL_4
#define KC_K131	 KC_INTERNATIONAL_5
#define KC_K133	 KC_INTERNATIONAL_2
#define KC_K151	 KC_LANGUAGE_1
#define KC_K150	 KC_LANGUAGE_2

#define MD_24G	 QMK_KB_MODE_2P4G
#define MD_BLE1	 QMK_KB_MODE_BLE1
#define MD_BLE2	 QMK_KB_MODE_BLE2
#define MD_BLE3	 QMK_KB_MODE_BLE3
#define MD_USB	 QMK_KB_MODE_USB
#define QK_BAT   QMK_BATT_NUM
#define QK_WLO	 QMK_WIN_LOCK
#define SIX_N	 QMK_KB_SIX_N_CH
#define KC_UC    USER_CHANGE
#define QK_DEB	 QMK_DEBOUNCE
#define TIME_ST	 QMK_TIME_SET
#define TIME_DT	 QMK_DTIME_SET
#define TEST_CL  QMK_TEST_COLOUR
#define LED_RST  QMK_LED_RESET
#define KbPrSlp  TIME_ST
#define KbdSecS  TIME_DT

/************************基本变量**************************/
/************************基本变量**************************/
/************************基本变量**************************/

extern Keyboard_Info_t Keyboard_Info;
extern Keyboard_Status_t Keyboard_Status;

void U16_Buff_Clear(uint16_t *Buff, uint8_t Len);
extern int usbd_ep_start_write(const uint8_t ep, const uint8_t *data, uint32_t data_len);

void es_spi_send_recv_by_dma(uint32_t num, uint8_t *rx_buf, uint8_t *tx_buf);
void User_bluetooth_send_keyboard(uint8_t *report, uint32_t len);

uint8_t es_keyboard_leds(void);
void    es_send_keyboard(report_keyboard_t *report);
void    es_send_nkro(report_nkro_t *report);
void    es_send_mouse(report_mouse_t *report);
void    es_send_extra(report_extra_t *report);

volatile host_driver_t * es_qmk_driver;
const host_driver_t es_user_driver;

/************************按键消抖**************************/
unsigned int Debounce_Delay;        //键盘消抖次数，最大为127
uint8_t Debounce_Point_Count;
uint16_t User_Key_3s_Count;
bool Debounce_Function_Count;
bool Debounce_Function_Status;

/******************自定义休眠相关变量********************/
uint8_t User_Sleep_Timer_Count;

/************************电池**************************/
uint16_t User_Adc_Batt[USER_BATT_SCAN_COUNT];
uint16_t User_Scan_Batt[USER_BATT_SCAN_COUNT];
uint8_t User_Adc_Batt_Count;
uint8_t User_Batt_BaiFen;
uint8_t User_Batt_Old_BaiFen;
uint8_t User_Batt_10ms_Count;
uint16_t User_Batt_Time_15S_Count;
bool User_Batt_Power_Up;
bool User_Batt_Send_Spi;
uint16_t User_Batt_Power_Up_Delay_100ms_Count;
bool User_Batt_Power_Up_Delay;

bool User_Power_Low;
uint8_t User_Power_Low_Count;
uint8_t es_stdby_pin_state;

bool User_Key_Batt_Num_Show;
uint8_t User_Key_Batt_Count;
/*********************************************************/
/************************电池充电******************************/
bool User_Batt_Power_Up_LED_Flag;
uint16_t User_Batt_Power_Up_LED_Count;
/*********************************************************/
/************************SPI******************************/
volatile uint8_t Spi_Send_Recv_Flg;
uint8_t g_es_spi_rx_buf[64], g_es_spi_tx_buf[64];
uint8_t Repet_Send_Coun;
uint8_t Send_Key_Type;
/*********************************************************/

/************************SPI******************************/
volatile uint8_t Spi_Send_Recv_Flg;
uint8_t g_es_spi_rx_buf[64], g_es_spi_tx_buf[64];
uint8_t Repet_Send_Count;
uint8_t Send_Key_Type;

bool Key_2p4g_Status;
bool Key_Ble_1_Status;
bool Key_Ble_2_Status;
bool Key_Ble_3_Status;
bool Key_Fn_Status;

bool Init_Spi_Power_Up;
uint8_t Init_Spi_100ms_Delay;

bool Led_Rf_Pair_Flg;
uint8_t Temp_System_Led_Status;
uint8_t Led_Point_Count;
uint8_t EE_CLR_Point_Count;
uint8_t Mac_Win_Point_Count;

uint16_t Usb_Suspend_Delay;
uint8_t Key_Switch_Scan;
uint8_t Key_Switch_Check;
uint8_t Key_Switch_Old;
uint8_t Key_Switch_delay;

uint8_t Key_Mac_Win_Scan;
uint8_t Key_Mac_Win_Check;
uint8_t Key_Mac_Win_Old;
uint8_t Key_Mac_Win_delay;


uint16_t Usb_Change_Mode_Delay;
bool Usb_Change_Mode_Wakeup;
bool Mode_Synchronization_Signal;

bool Save_Flash;
bool Reset_Save_Flash;
uint16_t Save_Flash_3S_Count;
bool Led_Flash_Busy;

bool Led_Off_Start;
bool Led_Power_Up;
uint16_t Led_Power_Up_Delay;

bool Led_Point_Sleep;
bool Usb_If_Ok_Led;
bool Usb_If_Ok;
uint16_t Usb_If_Ok_Delay;
uint16_t g_usb_sof_frame_id;
uint16_t g_usb_sof_frame_id_last;
bool Usb_Dis_Connect;

bool Ble_Name_Spi_Send ;
uint8_t Ble_Name_Spi_Count;

bool User_Sleep_Time_Send;
bool User_DSleep_Time_Send;

// 键盘灯光测试变量
bool Test_Led;
uint8_t Test_Colour;
/************************键盘恢复初始化变量*******************/
uint16_t Time_3s_EE_CLR_Count;
bool User_QMK_EE_CLR_Flag;
bool User_EE_CLR_Start_Flag;
/*********************************************************/

/************************Systick**************************/
uint8_t Systick_6ms_Count;
uint8_t Systick_10ms_Count;
uint16_t Systick_Interval_Count;
uint8_t Systick_Led_Count;
uint8_t Batt_Led_Count;
uint16_t Time_3s_Count;
uint16_t Spi_Interval;
/*********************************************************/

/************************数据队列**************************/
uint8_t app_2g4_data[APP_2G4_BUF_CNT][APP_2G4_BUF_SIZE];
volatile uint8_t app_2g4_data_send;
volatile uint8_t app_2g4_data_rev;
uint8_t Spi_Main_Loop_Count;

uint8_t app_2g4_buffer_full(void);
uint8_t app_2g4_buffer_empty(void);
void app_2g4_buffer_rev_add(void);
void app_2g4_buffer_send_add(void);
void Spi_Main_Loop(void);

/*********************************************************/

/**************************EMI****************************/
bool Emi_Test_Start;

void Emi_Init(void);
void Emi_Read_Data(uint8_t *User_Data, uint8_t User_Length);
void Emi_Write_Data(uint8_t *User_Data, uint8_t User_Length);

/*********************************************************/

/************************eeprom**************************/
/* Exported Constants --------------------------------------------------------*/
/* Define the size of the sectors to be used */
#define MCU_PAGE_SIZE           (uint32_t)0x200   /* MCU page size = 0.5kB */
#define PAGE_SIZE               (uint32_t)0x2000  /* Page size = 8kB */
#define MCU_PAGE_NUM            PAGE_SIZE / MCU_PAGE_SIZE

/* EEPROM start address in Flash */
#define EEPROM_START_ADDRESS  ((uint32_t)0x1C000)

/* Pages 0 and 1 base and end addresses */
#define PAGE0_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS))
#define PAGE0_END_ADDRESS     ((uint32_t)(PAGE0_BASE_ADDRESS + (PAGE_SIZE - 1)))

#define PAGE1_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + PAGE_SIZE))
#define PAGE1_END_ADDRESS     ((uint32_t)(PAGE1_BASE_ADDRESS + (PAGE_SIZE - 1)))

/* Used Flash pages for EEPROM emulation */
#define PAGE0                 ((uint32_t)0x00000000)
#define PAGE1                 ((uint32_t)0x00000001)

/* No valid page define */
#define NO_VALID_PAGE         ((uint32_t)0x000000AB)

/* Page status definitions */
#define ERASED                ((uint32_t)0xFFFFFFFF)     /* Page is empty */
#define RECEIVE_DATA          ((uint32_t)0xEEEEEEEE)     /* Page is marked to receive data */
#define VALID_PAGE            ((uint32_t)0x00000000)     /* Page containing valid data */

/* Valid pages in read and write defines */
#define READ_FROM_VALID_PAGE  ((uint8_t)0x00)
#define WRITE_IN_VALID_PAGE   ((uint8_t)0x01)

/* Page full define */
#define PAGE_FULL             ((uint8_t)0x80)

/* Variables' number */
#define NB_OF_VAR             (EEPROM_SIZE)
#define NB_OF_PRIVATE_VAR     (64)

#define ES_MCU_MEM_REMAP_OFFSET  ((((SYSCFG->REMAP)&SYSCFG_REMAP_REALBASE_MSK) >> SYSCFG_REMAP_REALBASE_POSS) << 12)

//__attribute__((aligned(4))) static uint8_t g_es_flash_eeprom_table[EEPROM_SIZE + 2];
__attribute__((aligned(4)))  uint8_t g_es_flash_eeprom_table[EEPROM_SIZE + NB_OF_PRIVATE_VAR + 2];

volatile uint32_t g_tst_remap_offset;

uint32_t ee_format(void);
uint32_t ee_find_valid_page(uint8_t operation);
uint32_t ee_verify_pagefull_write_variable(uint32_t virt_address, uint32_t data);
uint32_t ee_page_transfer(uint32_t virt_address, uint32_t data);
uint32_t IAPROM_PAGE_ERASE(uint32_t addr);
uint32_t IAPROM_WORD_PROGRAM(uint32_t addr,uint32_t data);
uint32_t ee_init(void);
uint32_t ee_write_variable(uint32_t virt_address);
uint32_t ee_format(void);
uint32_t ee_find_valid_page(uint8_t operation);
uint32_t ee_verify_pagefull_write_variable(uint32_t virt_address, uint32_t data);
uint32_t ee_page_transfer(uint32_t virt_address, uint32_t data);
size_t clamp_length(intptr_t offset, size_t len);

size_t clamp_length_user(intptr_t offset, size_t len);

void eeprom_driver_erase(void);

#define USER_EEPROM_START_ADDRESS1  (EEPROM_START_ADDRESS - (MCU_PAGE_SIZE))
volatile uint8_t es_eeprom_init_flag;

void eeprom_driver_init(void);
/*****************eeprom块读取********************/
void eeprom_read_block(void *buf, const void *addr, size_t len);
/*****************eeprom块写入********************/
void eeprom_write_block(const void *buf, void *addr, size_t len);
void eeprom_read_block_user(void *buf, const void *addr, size_t len);
void eeprom_write_block_user(const void *buf, void *addr, size_t len);
/*********************************************************/
uint8_t es_keyboard_leds(void);

/*发送6键类型数据*/
void    es_send_keyboard(report_keyboard_t *report);

/*发送全键类型数据*/
void    es_send_nkro(report_nkro_t *report);

/*发送鼠标类型数据*/
void    es_send_mouse(report_mouse_t *report);

/*发送多媒体类型数据*/
void    es_send_extra(report_extra_t *report);

void    es_send_raw_hid(uint8_t *data, uint8_t length);

/*系统复位*/
void es_mcu_reset(void);

/*跳转boot*/
void bootloader_jump(void);

/*MCU复位*/
void mcu_reset(void);

/*写入flash*/
void Save_Flash_Set(void);
/************************SPI*****************************/
const uint32_t g_es_dma_ch2pri_cfg;

const uint32_t g_es_dma_ch2alt_cfg;

const md_spi_inittypedef SPI2_InitStruct;

void es_ble_spi_init(void);

void es_ble_spi_deinit(void);

void es_spi_send_recv_by_dma(uint32_t num, uint8_t *rx_buf, uint8_t *tx_buf);

/*SPI发送命令函数*/
void Spi_Send_Commad(uint8_t Commad);

/*SPI发送命令函数*/
uint8_t Spi_Ack_Send_Commad(uint8_t Commad);

/*获取SPI数据函数*/
void Get_Spi_Return_Data(uint8_t *Data);

/*********************************************************/
/************************灯光*****************************/
#define ES_PWM_LED_SIZE         (42)
#define ES_PWM_LED_BYTE         (24)
#define ES_PWM_DMA_SIZE         (ES_PWM_LED_SIZE * ES_PWM_LED_BYTE)

#define ES_PWM_WS2812_H_VALUE   (43)
#define ES_PWM_WS2812_L_VALUE   (17)

rgb_led_t rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];
uint8_t g_es_pwm_rgb_matrix_array_dma_buf[(RGB_MATRIX_LED_COUNT * ES_PWM_LED_BYTE) + 2];
md_dma_channel_config_typedef DMA_list[5];

void rgb_matrix_driver_init(void);
void User_Pwm_Deinit(void);
void rgb_matrix_driver_flush_pwm_dma_start(void);
void rgb_matrix_driver_flush(void);
void rgb_matrix_driver_set_color(int index, uint8_t r, uint8_t g, uint8_t b);
void rgb_matrix_driver_set_color_all(uint8_t r, uint8_t g, uint8_t b);
// clang-format off
const rgb_matrix_driver_t rgb_matrix_driver;
uint8_t Led_Colour_Tab[9][3];
uint8_t Led_Batt_Index_Tab[10];
uint8_t Led_Point_buf[10];
uint8_t Led_Wave_Pwm_Tab[128];

#if LOGO_LED_ENABLE
uint8_t Logo_Index_Tab[LOGO_LED_SIZE];

uint8_t Logo_Flash_Count;
uint8_t Logo_Led_Coun;
uint8_t Logo_Play_Point;
uint8_t Logo_Pwm_R;
uint8_t Logo_Pwm_G;
uint8_t Logo_Pwm_B;
uint8_t Logo_Pwm_Colour;
/*********************************
            初始化函数
*********************************/
void Logo_Init(void);
void Logo_Pwm_Rgb_Updata(uint8_t Pwm);
void Logo_Pwm_Ds_Updata(uint8_t Pwm);
void Logo_Wave_Rgb_mode_Show(void);
void Logo_Wave_Ds_mode_Show(void);
void Logo_Spectrum_mode_Show(void);
void Logo_Breath_mode_Show(void);
void Logo_Light_mode_Show(void);
void Logo_Off_mode_Show(void);
void Logo_Mode_Show(void);
void User_Via_Qmk_Logo_Get_Value(uint8_t *data);
void User_Via_Qmk_Logo_Set_Value(uint8_t *data);
void User_Via_Qmk_Logo_Command(uint8_t *data, uint8_t length);

#endif

#define LED_ESC_INDEX       (81)
#define LED_BAT_INDEX       (36)
#define LED_SLEEP_ST_INDEX  (39)
#define LED_H_INDEX         (37)

#define LED_A_INDEX        (7)
#define LED_S_INDEX        (6)

#define LED_BLE_1_INDEX     (1) 
#define LED_BLE_2_INDEX     (2)
#define LED_BLE_3_INDEX     (3)
#define LED_2P4G_INDEX      (4)
#define LED_USB_INDEX       (0)

led_config_t g_led_config;

void Led_Rf_Mode_Show(void);

void Led_Point_Flash_Show(void);

void Led_Power_Low_Show(void);

void Led_Batt_Number_Show(void);

void User_Get_Led_Power_Status(void);

// 灯光测试模式
void User_Test_Colour_Show(void);

void User_Led_Show(void);
/*********************************************************/

/************************ADC******************************/
const md_adc_initial adc_initStruct ;

void User_Adc_Init(void);

void User_Adc_Deinit(void);
/*********************************************************/

/************************SYSTIME**************************/
void User_Systime_Init(void);
/*********************************************************/

/************************USB 插件**************************/
void User_Usb_Init(void);

void es_restart_usb_driver(void);

void Usb_Disconnect(void);

void User_Usb_Deinit(void);
/*********************************************************/

/************************休眠*****************************/
void Init_Gpio_Infomation(void);

void Init_Batt_Infomation(void);

/*先将IO配置成需要休眠的状态*/
void User_Sleep(void);

void User_Wakeup(void);

//WAKEUP_IRQHandler
OSAL_IRQ_HANDLER(Vector4C);

//EXTI_0to1_IRQHandler
OSAL_IRQ_HANDLER(Vector54);

//EXTI_2to3_IRQHandler
OSAL_IRQ_HANDLER(Vector58);

//GP32C4T1_IRQHandler
OSAL_IRQ_HANDLER(Vector7C);

//GP16C4T1_IRQHandler
OSAL_IRQ_HANDLER(Vector80);

//GP16C4T2_IRQHandler
OSAL_IRQ_HANDLER(Vector84);

void Board_Wakeup_Init(void);

void es_chibios_user_idle_loop_hook(void);
/*********************************************************/

/**********************系统函数***************************/


void User_Keyboard_Reset(void);
/*********************************************************/

//DMA1_CH12_IRQHandler  DMA中断
OSAL_IRQ_HANDLER(Vector68);

//EXTI_4to15_IRQHandler IO中断
OSAL_IRQ_HANDLER(Vector5C);

void User_Adc_Batt_Power_Up_Init(void);

void User_Adc_Batt_Number(void);

void Init_Keyboard_Infomation(void);

void es_change_qmk_nkro_mode_enable(void);

void es_change_qmk_nkro_mode_disable(void);

void Mode_Synchronization(void);
//蓝牙回连用户名同步
void Ble_Name_Synchronization(void);

void Sleep_Time_Synchronization(void);

void DSleep_Time_Synchronization(void);

//BS16T1_IRQHandler 2ms定时器
OSAL_IRQ_HANDLER(Vector78);

void User_Keyboard_Init(void);

void User_Keyboard_Post_Init(void);

void User_bluetooth_send_keyboard(uint8_t *report, uint32_t len);

bool Key_Value_Dispose(uint16_t keycode, keyrecord_t *record);