using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Date
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Date_from_parts", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDateError FromParts(int year, uint month, uint day, int offsetSeconds);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Date_year", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern int Year(Date* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Date_month", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint Month(Date* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Date_day", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern uint Day(Date* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Date_offset_seconds", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern int OffsetSeconds(Date* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Date_start_of_day", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* StartOfDay(Date* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Date_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Date* handle);
}