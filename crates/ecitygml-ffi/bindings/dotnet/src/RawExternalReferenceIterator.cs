using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct ExternalReferenceIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ExternalReferenceIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReference* Next(ExternalReferenceIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ExternalReferenceIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(ExternalReferenceIterator* handle);
}