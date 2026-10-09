using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MultiSurfaceProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurfaceProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurface* Object(MultiSurfaceProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurfaceProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(MultiSurfaceProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurfaceProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MultiSurfaceProperty* handle);
}