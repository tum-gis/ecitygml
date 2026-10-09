using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TinProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TriangulatedSurface* Object(TinProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(TinProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TinProperty* handle);
}