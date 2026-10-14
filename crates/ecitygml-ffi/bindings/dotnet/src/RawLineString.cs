using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct LineString
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LineString_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(LineString* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LineString_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(LineString* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LineString_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern LineString* TryFrom(AbstractCurveKind* curve);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LineString_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(LineString* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LineString_length_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Length3d(LineString* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LineString_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(LineString* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LineString_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(LineString* handle);
}