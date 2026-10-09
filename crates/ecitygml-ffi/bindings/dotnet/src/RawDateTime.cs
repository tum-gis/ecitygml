using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DateTime
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_from_parts", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDateTimeError FromParts(int year, uint month, uint day, uint hour, uint minute, uint second, uint nanosecond, int offsetSeconds);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_year", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern int Year(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_month", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint Month(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_day", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint Day(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_hour", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint Hour(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_minute", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint Minute(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_second", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint Second(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_nanosecond", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint Nanosecond(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_offset_seconds", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern int OffsetSeconds(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_to_rfc3339", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void ToRfc3339(DateTime* handle, DiplomatWrite* writeable);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_timestamp", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern long Timestamp(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_timestamp_subsec_nanos", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint TimestampSubsecNanos(DateTime* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DateTime_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(DateTime* handle);
}