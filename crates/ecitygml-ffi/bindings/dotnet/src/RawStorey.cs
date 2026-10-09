using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Storey
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionClassValue* Class(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionFunctionValueIterator* Functions(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionUsageValueIterator* Usages(Storey* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Storey* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Storey_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Storey* handle);
}