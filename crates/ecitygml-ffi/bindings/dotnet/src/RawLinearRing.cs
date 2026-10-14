using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct LinearRing
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LinearRing_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(LinearRing* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LinearRing_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(LinearRing* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LinearRing_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern LinearRing* TryFrom(AbstractRingKind* ring);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LinearRing_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(LinearRing* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LinearRing_length_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Length3d(LinearRing* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LinearRing_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Area3d(LinearRing* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LinearRing_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(LinearRing* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_LinearRing_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(LinearRing* handle);
}