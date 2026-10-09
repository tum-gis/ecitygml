using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Point
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Point_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Point* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Point_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Point* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Point_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Point* TryFrom(AbstractGeometryKind* geometry);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Point_pos", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPosition* Pos(Point* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Point_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(Point* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Point_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Point* handle);
}