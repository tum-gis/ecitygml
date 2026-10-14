using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Envelope
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_lower_corner", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPosition* LowerCorner(Envelope* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_upper_corner", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPosition* UpperCorner(Envelope* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_center", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPosition* Center(Envelope* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_size_x", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double SizeX(Envelope* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_size_y", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double SizeY(Envelope* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_size_z", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double SizeZ(Envelope* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_volume", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Volume(Envelope* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_contains", CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.U1)]
    internal static unsafe extern bool Contains(Envelope* handle, DirectPosition* point);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Envelope_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Envelope* handle);
}