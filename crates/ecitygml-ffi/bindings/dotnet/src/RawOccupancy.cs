using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Occupancy
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Occupancy_number_of_occupants", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern long NumberOfOccupants(Occupancy* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Occupancy_interval", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern IntervalValue* Interval(Occupancy* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Occupancy_occupant_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupantTypeValue* OccupantType(Occupancy* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Occupancy_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Occupancy* handle);
}