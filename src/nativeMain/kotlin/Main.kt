@file:OptIn(ExperimentalForeignApi::class)

import kotlinx.cinterop.*
import kotlinx.io.Buffer
import kotlinx.io.readFloatLe
import platform.windows.DWORD
import platform.windows.HANDLEVar
import simconnect.*


@OptIn(ExperimentalForeignApi::class)
fun main() {
    memScoped {
        val handleVar = alloc<HANDLEVar>()
        println("SimConnect_Open")
        SimConnect_Open(
            phSimConnect = handleVar.ptr,
            szName = "Twitch flies MSFS",
            hWnd = null,
            UserEventWin32 = 0.toUInt(),
            hEventHandle = null,
            ConfigIndex = 0.toUInt()
        )
        SimConnect_AddToDataDefinition(
            hSimConnect = handleVar.value,
            DefineID = 1.toUInt(),
            DatumName = "PLANE LATITUDE",
            UnitsName = "degree latitude",
            DatumType = SIMCONNECT_DATATYPE.SIMCONNECT_DATATYPE_FLOAT32,
            fEpsilon = 0f,
            DatumID = 0.toUInt()
        )
        SimConnect_AddToDataDefinition(
            hSimConnect = handleVar.value,
            DefineID = 1.toUInt(),
            DatumName = "PLANE LONGITUDE",
            UnitsName = "degree longitude",
            DatumType = SIMCONNECT_DATATYPE.SIMCONNECT_DATATYPE_FLOAT32,
            fEpsilon = 0f,
            DatumID = 1.toUInt()
        )
        SimConnect_RequestDataOnSimObject(
            hSimConnect = handleVar.value,
            RequestID = 0.toUInt(),
            DefineID = 1.toUInt(),
            ObjectID = SIMCONNECT_OBJECT_ID_USER,
            Period = SIMCONNECT_PERIOD.SIMCONNECT_PERIOD_SECOND,
            Flags = SIMCONNECT_DATA_REQUEST_FLAG_DEFAULT,
            origin = 0.toUInt(),
            interval = 1.toUInt(),
            limit = 0.toUInt()
        )
        while (true) {
            SimConnect_CallDispatch(
                hSimConnect = handleVar.value,
                pfcnDispatch = staticCFunction { a, b, c -> dispatchProc(a, b, c) },
                pContext = null
            )
        }
    }
}

@Suppress("CAST_NEVER_SUCCEEDS")
@OptIn(ExperimentalForeignApi::class)
fun dispatchProc(recvcPointer: CPointer<SIMCONNECT_RECV>?, b: DWORD, c: COpaquePointer?) {
    recvcPointer?.pointed?.also {
        when (it.dwID) {
            SIMCONNECT_RECV_ID.SIMCONNECT_RECV_ID_SIMOBJECT_DATA.value -> {
//                println(recvcPointer.pointed.memberAt<FLOATVar>(40).value)
//                println(recvcPointer.pointed.memberAt<FLOATVar>(44).value)
                val bytes = interpretCPointer<COpaquePointerVar>(recvcPointer.rawValue.plus(40))?.readBytes(8)!!
                with(Buffer()) {
                    write(bytes)
                    println(readFloatLe())
                    println(readFloatLe())
                }
            }
        }
    }
}