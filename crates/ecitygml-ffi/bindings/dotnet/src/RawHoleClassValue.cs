using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct HoleClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HoleClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(HoleClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HoleClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(HoleClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HoleClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(HoleClassValue* handle);
}