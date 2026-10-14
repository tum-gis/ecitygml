using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficSpaceClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(TrafficSpaceClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(TrafficSpaceClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficSpaceClassValue* handle);
}