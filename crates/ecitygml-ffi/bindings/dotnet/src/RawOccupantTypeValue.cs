using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct OccupantTypeValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_OccupantTypeValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(OccupantTypeValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_OccupantTypeValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(OccupantTypeValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_OccupantTypeValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(OccupantTypeValue* handle);
}