using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MarkingClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MarkingClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(MarkingClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MarkingClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(MarkingClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MarkingClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MarkingClassValue* handle);
}