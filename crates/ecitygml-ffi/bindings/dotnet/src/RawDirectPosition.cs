using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DirectPosition
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DirectPosition_new", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDirectPositionError create(double x, double y, double z);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DirectPosition_x", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double X(DirectPosition* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DirectPosition_y", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Y(DirectPosition* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DirectPosition_z", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Z(DirectPosition* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DirectPosition_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(DirectPosition* handle);
}