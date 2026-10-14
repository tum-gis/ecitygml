using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractGeometryKind
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryKind_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(AbstractGeometryKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryKind_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(AbstractGeometryKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryKind_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(AbstractGeometryKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryKind_geometry_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GeometryType GeometryType(AbstractGeometryKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryKind_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(AbstractGeometryKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractGeometryKind_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractGeometryKind* handle);
}