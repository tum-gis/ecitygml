using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct IntersectionClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntersectionClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(IntersectionClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntersectionClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(IntersectionClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntersectionClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(IntersectionClassValue* handle);
}