using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Triangle
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(Triangle* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Triangle* TryFrom(AbstractSurfacePatchKind* patch);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_exterior", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractRingKind* Exterior(Triangle* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_a", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPosition* A(Triangle* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_b", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPosition* B(Triangle* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_c", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPosition* C(Triangle* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_area", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Area(Triangle* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(Triangle* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(Triangle* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangle_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Triangle* handle);
}