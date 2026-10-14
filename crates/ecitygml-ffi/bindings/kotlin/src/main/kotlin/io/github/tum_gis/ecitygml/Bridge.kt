package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BridgeLib: Library {
    fun ecitygml_Bridge_destroy(handle: Pointer)
    fun ecitygml_Bridge_id(handle: Pointer): Pointer?
    fun ecitygml_Bridge_names(handle: Pointer): Pointer
    fun ecitygml_Bridge_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_Bridge_feature_id(handle: Pointer): Pointer
    fun ecitygml_Bridge_creation_date(handle: Pointer): Pointer?
    fun ecitygml_Bridge_termination_date(handle: Pointer): Pointer?
    fun ecitygml_Bridge_valid_from(handle: Pointer): Pointer?
    fun ecitygml_Bridge_valid_to(handle: Pointer): Pointer?
    fun ecitygml_Bridge_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_Bridge_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_Bridge_external_references(handle: Pointer): Pointer
    fun ecitygml_Bridge_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_Bridge_related_to(handle: Pointer): Pointer
    fun ecitygml_Bridge_space_type(handle: Pointer): OptionInt
    fun ecitygml_Bridge_lod1_solid(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod2_solid(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod3_solid(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod0_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod2_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod3_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod0_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod2_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod3_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod0_point(handle: Pointer): Pointer?
    fun ecitygml_Bridge_boundaries(handle: Pointer): Pointer
    fun ecitygml_Bridge_lod1_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod2_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod3_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod1_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod2_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_Bridge_lod3_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_Bridge_date_of_construction(handle: Pointer): Pointer?
    fun ecitygml_Bridge_date_of_demolition(handle: Pointer): Pointer?
    fun ecitygml_Bridge_heights(handle: Pointer): Pointer
    fun ecitygml_Bridge_occupancies(handle: Pointer): Pointer
    fun ecitygml_Bridge_class(handle: Pointer): Pointer?
    fun ecitygml_Bridge_functions(handle: Pointer): Pointer
    fun ecitygml_Bridge_usages(handle: Pointer): Pointer
    fun ecitygml_Bridge_try_from(feature: Pointer): Pointer?
    fun ecitygml_Bridge_bridge_parts(handle: Pointer): Pointer
}
/** A bridge, borrowed from a city model.
*/
class Bridge internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal var owned: Boolean,
)  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BridgeCleaner(val handle: Pointer, val lib: BridgeLib) : Runnable {
        override fun run() {
            lib.ecitygml_Bridge_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Bridge.BridgeCleaner(handle, Bridge.lib));
    }

    companion object {
        internal val libClass: Class<BridgeLib> = BridgeLib::class.java
        internal val lib: BridgeLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature as a bridge, or none if it is another type (Rust: `<&Bridge>::try_from`).
        */
        fun tryFrom(feature: AbstractFeatureKindRef): Bridge? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(feature);
            
            val returnVal = lib.ecitygml_Bridge_try_from(feature.handle);
            val selfEdges: List<Any> = listOf(feature)
            val handle = returnVal ?: return null
            val returnOpaque = Bridge(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The object's `gml:name`s.
    */
    fun names(): CodeIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** The feature's bounding shape (`gml:boundedBy`), if it has one.
    */
    fun boundedBy(): BoundingShape? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_bounded_by(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BoundingShape(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The feature's `gml:id`.
    */
    fun featureId(): Id {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_Bridge_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_Bridge_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_generic_attributes(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = GenericAttributeKindIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Relations to other city objects (`relatedTo`).
    */
    fun relatedTo(): CityObjectRelationPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun spaceType(): SpaceType? {
        
        val returnVal = lib.ecitygml_Bridge_space_type(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return SpaceType.fromNative(intermediateOption)
    }
    
    fun lod1Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod1_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod2_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod3_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod0_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod2_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod3_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod0_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod2_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod3_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0Point(): PointProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod0_point(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = PointProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The space's boundaries (e.g. wall surfaces or traffic areas).
    */
    fun boundaries(): AbstractSpaceBoundaryPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_boundaries(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractSpaceBoundaryPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun lod1TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod1_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod2_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod3_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod1ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod1_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod2_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_lod3_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun dateOfConstruction(): Date? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_date_of_construction(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Date(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun dateOfDemolition(): Date? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_date_of_demolition(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Date(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun heights(): HeightIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_heights(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = HeightIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun occupancies(): OccupancyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_occupancies(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = OccupancyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun class_(): BridgeClassValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_class(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BridgeClassValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun functions(): BridgeFunctionValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_functions(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = BridgeFunctionValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun usages(): BridgeUsageValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_usages(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = BridgeUsageValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun bridgeParts(): BridgePartPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Bridge_bridge_parts(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = BridgePartPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}