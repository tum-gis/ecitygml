using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractBuildingSubdivisionProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractBuildingSubdivisionProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractBuildingSubdivisionKind* Object(AbstractBuildingSubdivisionProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractBuildingSubdivisionProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(AbstractBuildingSubdivisionProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractBuildingSubdivisionProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractBuildingSubdivisionProperty* handle);
}