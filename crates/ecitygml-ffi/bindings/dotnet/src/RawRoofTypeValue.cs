using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct RoofTypeValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofTypeValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(RoofTypeValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofTypeValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(RoofTypeValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofTypeValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(RoofTypeValue* handle);
}