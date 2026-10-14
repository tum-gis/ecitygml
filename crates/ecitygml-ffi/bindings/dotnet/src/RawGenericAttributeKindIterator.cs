using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct GenericAttributeKindIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeKindIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKind* Next(GenericAttributeKindIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GenericAttributeKindIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(GenericAttributeKindIterator* handle);
}