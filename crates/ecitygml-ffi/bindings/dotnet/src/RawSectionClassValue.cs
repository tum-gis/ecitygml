using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SectionClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SectionClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(SectionClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SectionClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(SectionClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SectionClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SectionClassValue* handle);
}