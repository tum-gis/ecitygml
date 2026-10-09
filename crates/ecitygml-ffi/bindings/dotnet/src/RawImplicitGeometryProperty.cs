using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct ImplicitGeometryProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometryProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometry* Object(ImplicitGeometryProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometryProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(ImplicitGeometryProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometryProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(ImplicitGeometryProperty* handle);
}