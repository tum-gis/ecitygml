using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingUnit
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionClassValue* Class(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionFunctionValueIterator* Functions(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingSubdivisionUsageValueIterator* Usages(BuildingUnit* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingUnit* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingUnit_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingUnit* handle);
}