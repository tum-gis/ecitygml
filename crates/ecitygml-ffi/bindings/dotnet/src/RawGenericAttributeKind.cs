using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct GenericAttributeKind
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeKind_name", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Name(GenericAttributeKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeKind_as_string", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern StringAttribute* AsString(GenericAttributeKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeKind_as_int", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern IntAttribute* AsInt(GenericAttributeKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeKind_as_double", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DoubleAttribute* AsDouble(GenericAttributeKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeKind_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(GenericAttributeKind* handle);
}