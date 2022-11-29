void i18n_display_lang()
{
    Serial.println("Set to language: English");
}

// Global

const String I18N_ERROR_TITLE = "Error";
const String I18N_HINT_TITLE = "Notice";
const String I18N_INFO_TITLE = "Info";
const String I18N_WARNING_TITLE = "Warning";
const String I18N_ANS_TITLE = "Response";
const String I18N_MENU_GO_BACK = "[back]";
const String I18N_MENU_ABORT = "[abort]";

const String I18N_REWRITE_BOOL_ACTIV = "Activ";
const String I18N_REWRITE_BOOL_INACTIV = "Inactive";

const String I18N_APPLICATION_FROM = "'\nfrom '";
const String I18N_APPLICATION_RS = "'\nRS=";
const String I18N_APPLICATION_PK = " PK=";

const String I18N_BOOT_DEV_ACTIVE = "Dev Mode\nactive";

const String I18N_DIALOG_YES = "Yes";
const String I18N_DIALOG_NO = "No";
const String I18N_DIALOG_AGAIN = "[read again]";

const String I18N_NOT_RG_ALERT = "For this function your Independer must be registered. Visit for more info " + TEMPLATE_WEBSITE_URL;

// Actor

const String I18N_ACTOR_MAIN_MENU_TITLE = "Independer";
const String I18N_ACTOR_MAIN_MENU_COMMUNICATIONS = "Communication";
const String I18N_ACTOR_MAIN_MENU_ACTOR_FUNCTIONS = "Actor Functions";
const String I18N_ACTOR_MAIN_MENU_GATEWAY_FUNCTIONS = "Gateway Functions";
const String I18N_ACTOR_MAIN_MENU_SETTINGS = "Settings";
const String I18N_ACTOR_MAIN_MENU_INFO = "Info";
const String I18N_ACTOR_MAIN_MENU_ERR = "Selection not available.";

const String I18N_ACTOR_MAIN_MENU_INFO_PREFIX = "Info";
const String I18N_ACTOR_MAIN_MENU_INFO_VERSION = "Version: ";
const String I18N_ACTOR_MAIN_MENU_INFO_ACTOR_MODE = "Actor Mode: ";
const String I18N_ACTOR_MAIN_MENU_INFO_BRIGHTNESS = "Brightness: ";
const String I18N_ACTOR_MAIN_MENU_INFO_BACKGROUND_SYNC = "Background-Receive: ";
const String I18N_ACTOR_MAIN_MENU_INFO_TIME = "Time:\n";
const String I18N_ACTOR_MAIN_MENU_INFO_REG = "Registered:\n";
const String I18N_ACTOR_MAIN_MENU_INFO_ID = "\nID: ";
const String I18N_ACTOR_MAIN_MENU_INFO_GID = "\nGateway ID: ";
const String I18N_ACTOR_MAIN_MENU_INFO_DEVELOPER = "\nDeveloper: ";
const String I18N_ACTOR_MAIN_MENU_INFO_LORA_GAIN = "\nLoRa Gain: ";
const String I18N_ACTOR_MAIN_MENU_INFO_WIFI = "\nWIFI: ";
const String I18N_ACTOR_MAIN_MENU_INFO_WIFI_T = "\nWIFI Timeout: ";
const String I18N_ACTOR_MAIN_MENU_INFO_AUTO_SLP = "\nAuto Sleep: ";
const String I18N_ACTOR_MAIN_MENU_INFO_BATTERY = "\nBattery: ";
const String I18N_ACTOR_MAIN_MENU_INFO_BATTERY_U = "mV";

const String I18N_ACTOR_SETTINGS_MENU_TITLE = "Settings";
const String I18N_ACTOR_SETTINGS_MENU_GID = "Gateway ID";
const String I18N_ACTOR_SETTINGS_MENU_LORA_GAIN = "LoRa Gain";
const String I18N_ACTOR_SETTINGS_MENU_BRI = "Brightness";
const String I18N_ACTOR_SETTINGS_MENU_BACKGROUND_SYNC = "Background-Receive";
const String I18N_ACTOR_SETTINGS_MENU_AUTO_SLP = "Auto Sleep";
const String I18N_ACTOR_SETTINGS_MENU_WIFI = "WIFI";
const String I18N_ACTOR_SETTINGS_MENU_SERVER = "Server";
const String I18N_ACTOR_SETTINGS_MENU_RESET = "Factory settings";
const String I18N_ACTOR_SETTINGS_MENU_RESET_Q = "Do you really want to reset everything?";
const String I18N_ACTOR_SETTINGS_MENU_TIME = "Time";
const String I18N_ACTOR_SETTINGS_MENU_ERR_INV_ID = "Invalid ID";

const String I18N_ACTOR_SETTINGS_MENU_TIME_SYNC_SHOW = "Time sync/show";
const String I18N_ACTOR_SETTINGS_MENU_TIME_SHOW = "Time show";
const String I18N_ACTOR_SETTINGS_MENU_TIME_S_NOW = "Get Time\n...";
const String I18N_ACTOR_SETTINGS_MENU_TIME_S_RES = "Received\n'";
const String I18N_ACTOR_SETTINGS_MENU_TIME_S_LOC = "Local\n'";

const String I18N_ACTOR_SETTINGS_MENU_SERVER_TIMEOUT = "Timeout";
const String I18N_ACTOR_SETTINGS_MENU_SERVER_TIMEOUT_EX = "Timeout (e.g. 5000)";

const String I18N_ACTOR_SETTINGS_MENU_WIFI_AUTOMATIC = "Automatic";
const String I18N_ACTOR_SETTINGS_MENU_WIFI_TEST = "Test";
const String I18N_ACTOR_SETTINGS_MENU_WIFI_MAN_SSID = "(Manual) SSID";
const String I18N_ACTOR_SETTINGS_MENU_WIFI_MAN_PW = "(Manual) Password";
const String I18N_ACTOR_SETTINGS_MENU_WIFI_TEST_WIFI = "Test WIFI\n'";
const String I18N_ACTOR_SETTINGS_MENU_WIFI_TEST_WIFI_OK = "WIFI\nOk";
const String I18N_ACTOR_SETTINGS_MENU_WIFI_TEST_WIFI_ERR = "WIFI\nError";
const String I18N_ACTOR_SETTINGS_MENU_WIFI_SSID_TITLE = "SSID";
const String I18N_ACTOR_SETTINGS_MENU_WIFI_PW_TITLE = "Password";

const String I18N_ACTOR_SETTINGS_MENU_AUTO_SLP_ST = "State";
const String I18N_ACTOR_SETTINGS_MENU_AUTO_SLP_ACT = "Activate";
const String I18N_ACTOR_SETTINGS_MENU_AUTO_SLP_DEACT = "Disable";
const String I18N_ACTOR_SETTINGS_MENU_AUTO_SLP_ST_EX = "State Auto Sleep\n";
const String I18N_ACTOR_SETTINGS_MENU_AUTO_SLP_ST_EX_AC = "Activate\nAuto Sleep";
const String I18N_ACTOR_SETTINGS_MENU_AUTO_SLP_ST_EX_DEAC = "Disable\nAuto Sleep";

const String I18N_ACTOR_SETTINGS_MENU_BACKGROUND_SYNC_ST = "State";
const String I18N_ACTOR_SETTINGS_MENU_BACKGROUND_SYNC_ACT = "Activate";
const String I18N_ACTOR_SETTINGS_MENU_BACKGROUND_SYNC_DEACT = "Disable";
const String I18N_ACTOR_SETTINGS_MENU_BACKGROUND_SYNC_ST_EX = "State Background-Receive\n";
const String I18N_ACTOR_SETTINGS_MENU_BACKGROUND_SYNC_ST_EX_AC = "Activate\nBackground-Receive";
const String I18N_ACTOR_SETTINGS_MENU_BACKGROUND_SYNC_ST_EX_DEAC = "Disable\nBackground-Receive";

const String I18N_ACTOR_GATEWAY_FUNCTIONS_SLEEP_MODE = "Sleep Mode";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_UPDATE = "Update";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_INIT = "Initialize";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_RESET = "Factory settings";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_Q = "Do you really want to perform this action? The gateway must be switched on again manually afterwards.";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_IQ = "Do you really want to perform this action? The gateway must be set up again manually afterwards.";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_FUN_SLP = "Activate Sleep Mode\n(Gateway)";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_FUN_UPD = "Activate Update Mode\n(Gateway)";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_FUN_S_SHOWED_ID = "Showed ID (z.B.: 0g01)";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_FUN_S_G_ID = "Gateway ID (z.B.: 0g01)";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_ST_CHECK_ID = "Check ID";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_ST_SEND_CONFIG = "Send config";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_ERR_NOT_OWNED = "Invalid ID\n(not registered)";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_ERR_NO_VALID_ID = "Invalid ID";
const String I18N_ACTOR_GATEWAY_FUNCTIONS_FUN_RESET = "Factory settings\n(Gateway)";

const String I18N_ACTOR_ACTOR_FUNCTIONS_STATE_MENU = "State Menu";
const String I18N_ACTOR_ACTOR_FUNCTIONS_TEST_MENU = "Test Menu";
const String I18N_ACTOR_ACTOR_FUNCTIONS_STANDBY = "Screen off";
const String I18N_ACTOR_ACTOR_FUNCTIONS_SLP_MODE = "Sleep Mode";
const String I18N_ACTOR_ACTOR_FUNCTIONS_ENV_SCAN = "Environment Scan";
const String I18N_ACTOR_ACTOR_FUNCTIONS_SYNC = "Auto Sync (manual)";
const String I18N_ACTOR_ACTOR_FUNCTIONS_UPD = "Update";
const String I18N_ACTOR_ACTOR_FUNCTIONS_FUN_ACT_SLP = "Activate Sleep Mode\n(Actor)";
const String I18N_ACTOR_ACTOR_FUNCTIONS_SYNC_ERR_NO_DATA = "No data";

const String I18N_ACTOR_ACTOR_FUNCTIONS_TEST_MENU_REACH_CH = "Reachable Check";
const String I18N_ACTOR_ACTOR_FUNCTIONS_TEST_MENU_TEST_OUT = "Test Output";
const String I18N_ACTOR_ACTOR_FUNCTIONS_TEST_MENU_TEST_SHARE = "Test Data exchange";
const String I18N_ACTOR_ACTOR_FUNCTIONS_TEST_MENU_RES_ID = "Receiver (e.g.: 0x01)";
const String I18N_ACTOR_ACTOR_FUNCTIONS_TEST_MENU_ERR_INVALID_RES = "Invalid Receiver";

const String I18N_ACTOR_ACTOR_FUNCTIONS_STATE_MENU_BAT_ST = "Batteriy State";
const String I18N_ACTOR_ACTOR_FUNCTIONS_STATE_MENU_SEND_QT = "Send quota";
const String I18N_ACTOR_ACTOR_FUNCTIONS_STATE_MENU_EX_BAT_ST = "Batterie State (mV)";
const String I18N_ACTOR_ACTOR_FUNCTIONS_STATE_MENU_EX_SEND_QT = "Send quota (millis)";

const String I18N_ACTOR_COMMUNICATIONS_LETTER = "Letters (Gateway)";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_SHORT = "Letter";
const String I18N_ACTOR_COMMUNICATIONS_MSGS = "Messages (Actor)";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_SHORT = "Message";
const String I18N_ACTOR_COMMUNICATIONS_CHAT = "Chat (Internet)";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_SHORT = "Chat";
const String I18N_ACTOR_COMMUNICATIONS_CONTACT_BOOK = "Contacts";
const String I18N_ACTOR_COMMUNICATIONS_ERR_NOT_IMPL = "Unfortunately, the function\nis not yet available.";

const String I18N_ACTOR_COMMUNICATIONS_CHAT_WRITE = "Write message";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_GET = "Get chat";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_CLEAN = "Clean chat";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_RES = "Receiver (e.g.: 0x01)";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_CON = "Content";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_ST_SEND_MSG = "Message will\nbe sent";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_ST_SENT_MSG = "Message sent";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_ERR_SEND_MSG = "Message could\nnot be sent";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_ERR_INVAL_RES = "Invalid Receiver";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_CLEAN_FUN_NOW = "Chat will be\ndeleted...";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_CLEAN_FUN_CLEANED = "Chat was deleted.";
const String I18N_ACTOR_COMMUNICATIONS_CHAT_CLEAN_FUN_ERR = "Chat could not\nbe deleted.";

const String I18N_ACTOR_COMMUNICATIONS_MSGS_WRITE = "Write message";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_READ = "Read messages";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_CLEAN = "Clean messages";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_RESCUE_MENU = "Rescue Menu";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_RES = "Receiver (e.g.: 0x01)";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_CON = "Message";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_ERR_INV_RES = "Invalid Receiver";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_RESCUE_MENU_SEND_AGAIN = "Send again";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_RESCUE_MENU_CLEAN_MEM = "Clean memory";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_RESCUE_MENU_ERR_NO_MSG = "No messages\navailable";
const String I18N_ACTOR_COMMUNICATIONS_MSGS_RESCUE_MENU_CLEAN_NOW = "Messages will be\ndeleted";

const String I18N_ACTOR_COMMUNICATIONS_LETTER_WRITE = "Write letter";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_GET = "Get letters";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_CLEAN = "Clean letters";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_RESCUE_MENU = "Rescue Menu";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_RES = "Receiver (e.g.: 0x01)";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_CON = "Letter";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_ERR_INV_RES = "Invalid receiver";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_FUN_CLEAN = "Clean letters\n(Gateway)";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_RESCUE_MENU_SEND_AGAIN = "Send again";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_RESCUE_MENU_CLEAN = "Clean memory";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_ERR_NO_LETTERS = "No letters\navailable";
const String I18N_ACTOR_COMMUNICATIONS_LETTER_FUN_CLEAN_NOW = "Letters will be\ndeleted";

const String I18N_ACTOR_AUTO_SYNC_BOOT_TITLE = "Auto Sync";
const String I18N_ACTOR_MULTI_ACTOR_NO_MSG_AVA = "no messages\navailable";
const String I18N_ACTOR_MULTI_ACTOR_TITLE = "Messages";
const String I18N_ACTOR_MULTI_ACTOR_MSG = "Message";
const String I18N_ACTOR_MULTI_ACTOR_CLEAN_MSG = "Clean messages";

const String I18N_ACTOR_APP_ENV_SCAN = "Environment Scan";
const String I18N_ACTOR_APP_ENV_SCAN_RS = "' RS=";
const String I18N_ACTOR_APP_ENV_SCAN_OUTPUT_T = "Scan Output";
const String I18N_ACTOR_APP_ENV_SCAN_DETAIL_T = "Scan Details";

const String I18N_ACTOR_APP_REACH_CH_ATTEMPT = "Reachable Check Attempt";
const String I18N_ACTOR_APP_REACH_ERR_NO_RES = "no response";

const String I18N_ACTOR_APP_SEND_TO_GATEWAY_ERR_GA_NOT_REACH = "Gateway is\nnot available";
const String I18N_ACTOR_APP_SEND_TO_GATEWAY_SEND_ATT = "Send Attempt";
const String I18N_ACTOR_APP_SEND_TO_GATEWAY_SEND_SUC = "Letter was\nsent";
const String I18N_ACTOR_APP_SEND_TO_GATEWAY_SEND_ERR = "Letter could\nnot be sent";

const String I18N_ACTOR_APP_QUERY_GATEWAY_ATT = "Attempt";
const String I18N_ACTOR_APP_QUERY_GATEWAY_LETTERS = "Letters";
const String I18N_ACTOR_APP_QUERY_GATEWAY_LETTER = "Letter";
const String I18N_ACTOR_APP_QUERY_GATEWAY_ER_NO_LETTER = "no letters\navailable";
const String I18N_ACTOR_APP_QUERY_GATEWAY_ER_NO_RES = "Letters could\nnot be received";

const String I18N_ACTOR_APP_SEND_TO_ACTOR_ATT = "Send Attempt";
const String I18N_ACTOR_APP_SEND_TO_ACTOR_SEND_SUC = "Message sent";
const String I18N_ACTOR_APP_SEND_TO_ACTOR_SEND_ERR = "Message could\nnot be sent";

const String I18N_ACTOR_APP_LARGE_DATA_MSG = "Message";

const String I18N_ACTOR_APP_QUERY_INTERNET_GET_MSG = "Chats will\nbe retrieved";
const String I18N_ACTOR_APP_QUERY_INTERNET_CHATS = "Chats";
const String I18N_ACTOR_APP_QUERY_INTERNET_CHAT = "Chat";
const String I18N_ACTOR_APP_QUERY_INTERNET_GET_NO_MSGS = "No chats\navailable";
const String I18N_ACTOR_APP_QUERY_INTERNET_GET_ERR = "Chats could\nnot be received";

const String I18N_ACTOR_APP_AUTO_WIFI_SCAN_NOW = "Scan...";
const String I18N_ACTOR_APP_AUTO_WIFI_SSIDS = "SSIDs";
const String I18N_ACTOR_APP_AUTO_WIFI_PW = "Password";
const String I18N_ACTOR_APP_AUTO_WIFI_SAVED = "Settings\nstored";
const String I18N_ACTOR_APP_AUTO_WIFI_NO_NETWORKS = "No networks found";

// Gateway

const String I18N_GATEWAY_MENU_TITLE = "Independer Gateway";

const String I18N_GATEWAY_MENU_PACKETS = "Packages: ";
const String I18N_GATEWAY_MENU_MSGS = " Messages: ";
const String I18N_GATEWAY_MENU_DB_ITEMS = "\nDatabase entries: ";

// Device

const String I18N_DEVICE_WIFI_AUTO_SYNC_PROC_NEW_UPDATE = "New update available (";
const String I18N_DEVICE_WIFI_AUTO_SYNC_PROC_NEW_CHAT_MSGS = "New chat messages available (";
const String I18N_DEVICE_WIFI_AUTO_SYNC_PROC_STATUS_MSG = "State Message: [";

const String I18N_DEVICE_WIFI_AUTO_SYNC_TITLE = "Auto Sync";
const String I18N_DEVICE_WIFI_AUTO_SYNC_NOW = "Synchronize data\n...";

const String I18N_DEVICE_UTILS_THX = "Thank you for\nchoosing the\nIndepender!";

const String I18N_DEVICE_OTA_CONN_WITH = "Connect with\n'";
const String I18N_DEVICE_OTA_UPDATE_TITLE = "Update";
const String I18N_DEVICE_OTA_BROWSER_GO = "Open in browser\n'";

const String I18N_DEVICE_LORA_SEND_TITLE = "Send";
const String I18N_DEVICE_LORA_RES_TITLE = "Receive";

const String I18N_DEVICE_GUI_ACTOR = " Actor\n";
const String I18N_DEVICE_GUI_GATEWAY = " Gateway\n";
const String I18N_DEVICE_GUI_BY = " from ";
const String I18N_DEVICE_GUI_ENTER_OK = "[Enter] Ok";

const String I18N_DEVICE_DB_INIT_TITLE = "Independer";
const String I18N_DEVICE_DB_INIT_SUB_TITLE = "Setup mode";
const String I18N_DEVICE_DB_INIT_DESC = "After an update or at the first start the Independer has to be configured. The configuration wizard will help you with this.";

const String I18N_DEVICE_DB_INIT_REG_TITLE = "Registered?";
const String I18N_DEVICE_DB_INIT_REG_DESC = "Are you already registered? For some functions like online chat, update check, WIFI, NTP time sync and for using gateways the Independer has to be registered. If you are not registered, it is only possible to communicate with other unregistered Independers. Visit for more info " + TEMPLATE_WEBSITE_URL;

const String I18N_DEVICE_DB_INIT_WIFI_TITLE = "WIFI";
const String I18N_DEVICE_DB_INIT_WIFI_AUTO = "Automatic";
const String I18N_DEVICE_DB_INIT_WIFI_MAN_SSID = "(Manual) SSID";
const String I18N_DEVICE_DB_INIT_WIFI_MAN_PW = "(Manual) Password";
const String I18N_DEVICE_DB_INIT_WIFI_OK = "[Confirm]";
const String I18N_DEVICE_DB_INIT_WIFI_OFF = "[Turn off]";
const String I18N_DEVICE_DB_INIT_WIFI_FUN_TEST = "Test WIFI\n'";
const String I18N_DEVICE_DB_INIT_WIFI_ERR = "WIFI\nError";
const String I18N_DEVICE_DB_INIT_WIFI_SSID = "SSID";
const String I18N_DEVICE_DB_INIT_WIFI_PW = "Password";

const String I18N_DEVICE_DB_INIT_IACTOR_MY_ID = "My ID (e.g.: 0x01)";
const String I18N_DEVICE_DB_INIT_IACTOR_MY_PW = "Independer Password";
const String I18N_DEVICE_DB_INIT_IACTOR_FUN_CHECK_LOGIN = "Check login\nID\n'";
const String I18N_DEVICE_DB_INIT_IACTOR_FUN_GID = "Gateway ID (e.g.: 0g01)";
const String I18N_DEVICE_DB_INIT_IACTOR_ERR_INV_ID = "Invalid ID";
const String I18N_DEVICE_DB_INIT_IACTOR_ERR_NO_L = "ID could not\nbe registered.";
const String I18N_DEVICE_DB_INIT_IACTOR_SUC = "Setup\ncomplet!";

const String I18N_DEVICE_DB_INIT_IGAT_TITLE = "Setup mode";
const String I18N_DEVICE_DB_INIT_IGAT_DESC = "On Actor:\nG. Functions->Initialize\nID: '";
const String I18N_DEVICE_DB_INIT_IGAT_SUC = "Setup\ncomplet!";