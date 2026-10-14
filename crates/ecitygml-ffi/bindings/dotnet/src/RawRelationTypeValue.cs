using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct RelationTypeValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RelationTypeValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(RelationTypeValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RelationTypeValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(RelationTypeValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RelationTypeValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(RelationTypeValue* handle);
}