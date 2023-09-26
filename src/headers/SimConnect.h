enum SIMCONNECT_DATATYPE
{
    SIMCONNECT_DATATYPE_INVALID,        // invalid data type
    SIMCONNECT_DATATYPE_INT32,          // 32-bit integer number
    SIMCONNECT_DATATYPE_INT64,          // 64-bit integer number
    SIMCONNECT_DATATYPE_FLOAT32,        // 32-bit floating-point number (float)
    SIMCONNECT_DATATYPE_FLOAT64,        // 64-bit floating-point number (double)
    SIMCONNECT_DATATYPE_STRING8,        // 8-byte string
    SIMCONNECT_DATATYPE_STRING32,       // 32-byte string
    SIMCONNECT_DATATYPE_STRING64,       // 64-byte string
    SIMCONNECT_DATATYPE_STRING128,      // 128-byte string
    SIMCONNECT_DATATYPE_STRING256,      // 256-byte string
    SIMCONNECT_DATATYPE_STRING260,      // 260-byte string
    SIMCONNECT_DATATYPE_STRINGV,        // variable-length string

    SIMCONNECT_DATATYPE_INITPOSITION,   // see SIMCONNECT_DATA_INITPOSITION
    SIMCONNECT_DATATYPE_MARKERSTATE,    // see SIMCONNECT_DATA_MARKERSTATE
    SIMCONNECT_DATATYPE_WAYPOINT,       // see SIMCONNECT_DATA_WAYPOINT
    SIMCONNECT_DATATYPE_LATLONALT,      // see SIMCONNECT_DATA_LATLONALT
    SIMCONNECT_DATATYPE_XYZ,            // see SIMCONNECT_DATA_XYZ

    SIMCONNECT_DATATYPE_MAX             // enum limit
};

#define SIMCONNECT_REFSTRUCT struct
#define SIMCONNECT_STRUCT struct
#define SIMCONNECT_STRING(name, size) char name[size]
#define SIMCONNECT_GUID GUID
#define SIMCONNECT_STRINGV(name) char name[1]
#define SIMCONNECT_DATAV(name, id, count) DWORD name
#define SIMCONNECT_FIXEDTYPE_DATAV(type, name, count, cliMarshalAs, cliType) type name[1]
#define SIMCONNECT_GUID GUID
#define SIMCONNECT_ENUM enum
#define SIMCONNECT_ENUM_FLAGS typedef DWORD
#define SIMCONNECT_USER_ENUM typedef DWORD


SIMCONNECT_ENUM SIMCONNECT_PERIOD
{
    SIMCONNECT_PERIOD_NEVER,
    SIMCONNECT_PERIOD_ONCE,
    SIMCONNECT_PERIOD_VISUAL_FRAME,
    SIMCONNECT_PERIOD_SIM_FRAME,
    SIMCONNECT_PERIOD_SECOND,
};

SIMCONNECT_USER_ENUM SIMCONNECT_NOTIFICATION_GROUP_ID;     //client-defined notification group ID
SIMCONNECT_USER_ENUM SIMCONNECT_INPUT_GROUP_ID;            //client-defined input group ID
SIMCONNECT_USER_ENUM SIMCONNECT_DATA_DEFINITION_ID;        //client-defined data definition ID
SIMCONNECT_USER_ENUM SIMCONNECT_DATA_REQUEST_ID;           //client-defined request data ID

SIMCONNECT_USER_ENUM SIMCONNECT_CLIENT_EVENT_ID;           //client-defined client event ID
SIMCONNECT_USER_ENUM SIMCONNECT_CLIENT_DATA_ID;            //client-defined client data ID
SIMCONNECT_USER_ENUM SIMCONNECT_CLIENT_DATA_DEFINITION_ID; //client-defined client data definition ID

typedef DWORD SIMCONNECT_OBJECT_ID;

static const DWORD SIMCONNECT_OBJECT_ID_USER   = 0;           // proxy value for User vehicle ObjectID

#pragma pack(push, 1)

SIMCONNECT_REFSTRUCT SIMCONNECT_RECV
{
    DWORD   dwSize;         // record size
    DWORD   dwVersion;      // interface version
    DWORD   dwID;           // see SIMCONNECT_RECV_ID
};

SIMCONNECT_ENUM_FLAGS SIMCONNECT_DATA_REQUEST_FLAG;
    static const DWORD SIMCONNECT_DATA_REQUEST_FLAG_DEFAULT           = 0x00000000;
    static const DWORD SIMCONNECT_DATA_REQUEST_FLAG_CHANGED           = 0x00000001;      // send requested data when value(s) change
    static const DWORD SIMCONNECT_DATA_REQUEST_FLAG_TAGGED            = 0x00000002;      // send requested data in tagged format

typedef void (CALLBACK *DispatchProc)(struct SIMCONNECT_RECV* pData, DWORD cbData, void* pContext);

SIMCONNECT_ENUM SIMCONNECT_RECV_ID
{
    SIMCONNECT_RECV_ID_NULL,
    SIMCONNECT_RECV_ID_EXCEPTION,
    SIMCONNECT_RECV_ID_OPEN,
    SIMCONNECT_RECV_ID_QUIT,
    SIMCONNECT_RECV_ID_EVENT,
    SIMCONNECT_RECV_ID_EVENT_OBJECT_ADDREMOVE,
    SIMCONNECT_RECV_ID_EVENT_FILENAME,
    SIMCONNECT_RECV_ID_EVENT_FRAME,
    SIMCONNECT_RECV_ID_SIMOBJECT_DATA,
    SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE,
    SIMCONNECT_RECV_ID_WEATHER_OBSERVATION,
    SIMCONNECT_RECV_ID_CLOUD_STATE,
    SIMCONNECT_RECV_ID_ASSIGNED_OBJECT_ID,
    SIMCONNECT_RECV_ID_RESERVED_KEY,
    SIMCONNECT_RECV_ID_CUSTOM_ACTION,
    SIMCONNECT_RECV_ID_SYSTEM_STATE,
    SIMCONNECT_RECV_ID_CLIENT_DATA,
    SIMCONNECT_RECV_ID_EVENT_WEATHER_MODE,
    SIMCONNECT_RECV_ID_AIRPORT_LIST,
    SIMCONNECT_RECV_ID_VOR_LIST,
    SIMCONNECT_RECV_ID_NDB_LIST,
    SIMCONNECT_RECV_ID_WAYPOINT_LIST,
    SIMCONNECT_RECV_ID_EVENT_MULTIPLAYER_SERVER_STARTED,
    SIMCONNECT_RECV_ID_EVENT_MULTIPLAYER_CLIENT_STARTED,
    SIMCONNECT_RECV_ID_EVENT_MULTIPLAYER_SESSION_ENDED,
    SIMCONNECT_RECV_ID_EVENT_RACE_END,
    SIMCONNECT_RECV_ID_EVENT_RACE_LAP,
#ifdef ENABLE_SIMCONNECT_EXPERIMENTAL
    SIMCONNECT_RECV_ID_PICK,
#endif //ENABLE_SIMCONNECT_EXPERIMENTAL
    SIMCONNECT_RECV_ID_EVENT_EX1,
    SIMCONNECT_RECV_ID_FACILITY_DATA,
    SIMCONNECT_RECV_ID_FACILITY_DATA_END,
    SIMCONNECT_RECV_ID_FACILITY_MINIMAL_LIST,
    SIMCONNECT_RECV_ID_JETWAY_DATA,
    SIMCONNECT_RECV_ID_CONTROLLERS_LIST,
    SIMCONNECT_RECV_ID_ACTION_CALLBACK,
    SIMCONNECT_RECV_ID_ENUMERATE_INPUT_EVENTS,
    SIMCONNECT_RECV_ID_GET_INPUT_EVENT,
    SIMCONNECT_RECV_ID_SUBSCRIBE_INPUT_EVENT,
    SIMCONNECT_RECV_ID_ENUMERATE_INPUT_EVENT_PARAMS,
};

SIMCONNECT_REFSTRUCT SIMCONNECT_RECV_SIMOBJECT_DATA           // when dwID == SIMCONNECT_RECV_ID_SIMOBJECT_DATA
{
    DWORD   dwSize;         // record size
    DWORD   dwVersion;      // interface version
    DWORD   dwID;           // see SIMCONNECT_RECV_ID
    DWORD   dwRequestID;
    DWORD   dwObjectID;
    DWORD   dwDefineID;
    DWORD   dwFlags;            // SIMCONNECT_DATA_REQUEST_FLAG
    DWORD   dwentrynumber;      // if multiple objects returned, this is number <entrynumber> out of <outof>.
    DWORD   dwoutof;            // note: starts with 1, not 0.
    DWORD   dwDefineCount;      // data count (number of datums, *not* byte count)
    SIMCONNECT_DATAV(   dwData, dwDefineID, );             // data begins here, dwDefineCount data items
};

HRESULT __stdcall SimConnect_Open(HANDLE * phSimConnect, LPCSTR szName, HWND hWnd, DWORD UserEventWin32, HANDLE hEventHandle, DWORD ConfigIndex);
HRESULT __stdcall SimConnect_AddToDataDefinition(HANDLE hSimConnect, SIMCONNECT_DATA_DEFINITION_ID DefineID, const char * DatumName, const char * UnitsName, enum SIMCONNECT_DATATYPE DatumType, float fEpsilon, DWORD DatumID);
HRESULT __stdcall SimConnect_RequestDataOnSimObject(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_DATA_DEFINITION_ID DefineID, SIMCONNECT_OBJECT_ID ObjectID, enum SIMCONNECT_PERIOD Period, SIMCONNECT_DATA_REQUEST_FLAG Flags, DWORD origin, DWORD interval, DWORD limit);
HRESULT __stdcall SimConnect_GetNextDispatch(HANDLE hSimConnect, struct SIMCONNECT_RECV ** ppData, DWORD * pcbData);
HRESULT __stdcall SimConnect_CallDispatch(HANDLE hSimConnect, DispatchProc pfcnDispatch, void * pContext);