using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingSubdivisionUsageValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionUsageValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionUsageValue* Next(BuildingSubdivisionUsageValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionUsageValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingSubdivisionUsageValueIterator* handle);
}