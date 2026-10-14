using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingSubdivisionFunctionValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionFunctionValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionFunctionValue* Next(BuildingSubdivisionFunctionValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingSubdivisionFunctionValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingSubdivisionFunctionValueIterator* handle);
}