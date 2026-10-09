using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct OccupancyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_OccupancyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Occupancy* Next(OccupancyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_OccupancyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(OccupancyIterator* handle);
}