using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractSurfacePatchKindIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfacePatchKindIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSurfacePatchKind* Next(AbstractSurfacePatchKindIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfacePatchKindIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractSurfacePatchKindIterator* handle);
}