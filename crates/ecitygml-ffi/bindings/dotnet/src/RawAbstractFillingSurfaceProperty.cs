using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractFillingSurfaceProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFillingSurfaceProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractFillingSurfaceKind* Object(AbstractFillingSurfaceProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFillingSurfaceProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(AbstractFillingSurfaceProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFillingSurfaceProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractFillingSurfaceProperty* handle);
}