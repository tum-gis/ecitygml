using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct GmlReader
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlReader_new", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GmlReader* create(DiplomatSliceU8 data, CitygmlFormat format);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlReader_from_path", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultGmlReaderError FromPath(DiplomatSliceU8 path);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlReader_with_rebuild_object_bounds", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void WithRebuildObjectBounds(GmlReader* handle, [MarshalAs(UnmanagedType.U1)] bool rebuildObjectBounds);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlReader_finish", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultCityModelError Finish(GmlReader* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlReader_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(GmlReader* handle);
}