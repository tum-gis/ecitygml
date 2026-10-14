using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityObjectRelation
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelation_relation_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern RelationTypeValue* RelationType(CityObjectRelation* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelation_relation_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Reference* RelationTo(CityObjectRelation* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelation_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(CityObjectRelation* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelation_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityObjectRelation* handle);
}