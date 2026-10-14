using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingPartProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPartProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingPart* Object(BuildingPartProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPartProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(BuildingPartProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPartProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingPartProperty* handle);
}