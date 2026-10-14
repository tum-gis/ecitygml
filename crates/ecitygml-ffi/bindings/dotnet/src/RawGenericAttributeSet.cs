using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct GenericAttributeSet
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeSet_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeSet* TryFrom(GenericAttributeKind* attribute);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeSet_name", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Name(GenericAttributeSet* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeSet_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(GenericAttributeSet* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeSet_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(GenericAttributeSet* handle);
}