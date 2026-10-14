using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingSubdivisionUsageValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionUsageValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionUsageValue* Next(BuildingSubdivisionUsageValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionUsageValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingSubdivisionUsageValueIterator* handle);
}