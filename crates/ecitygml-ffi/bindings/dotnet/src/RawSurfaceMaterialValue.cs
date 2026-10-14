using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SurfaceMaterialValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SurfaceMaterialValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(SurfaceMaterialValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SurfaceMaterialValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(SurfaceMaterialValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SurfaceMaterialValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SurfaceMaterialValue* handle);
}