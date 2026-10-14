package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RoadLib: Library {
    fun ecitygml_Road_destroy(handle: Pointer)
    fun ecitygml_Road_id(handle: Pointer): Pointer?
    fun ecitygml_Road_names(handle: Pointer): Pointer
    fun ecitygml_Road_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_Road_feature_id(handle: Pointer): Pointer
    fun ecitygml_Road_creation_date(handle: Pointer): Pointer?
    fun ecitygml_Road_termination_date(handle: Pointer): Pointer?
    fun ecitygml_Road_valid_from(handle: Pointer): Pointer?
    fun ecitygml_Road_valid_to(handle: Pointer): Pointer?
    fun ecitygml_Road_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_Road_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_Road_external_references(handle: Pointer): Pointer
    fun ecitygml_Road_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_Road_related_to(handle: Pointer): Pointer
    fun ecitygml_Road_space_type(handle: Pointer): OptionInt
    fun ecitygml_Road_lod1_solid(handle: Pointer): Pointer?
    fun ecitygml_Road_lod2_solid(handle: Pointer): Pointer?
    fun ecitygml_Road_lod3_solid(handle: Pointer): Pointer?
    fun ecitygml_Road_lod0_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Road_lod2_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Road_lod3_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Road_lod0_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Road_lod2_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Road_lod3_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Road_lod0_point(handle: Pointer): Pointer?
    fun ecitygml_Road_boundaries(handle: Pointer): Pointer
    fun ecitygml_Road_lod1_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Road_lod2_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Road_lod3_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_Road_traffic_direction(handle: Pointer): OptionInt
    fun ecitygml_Road_occupancies(handle: Pointer): Pointer
    fun ecitygml_Road_traffic_spaces(handle: Pointer): Pointer
    fun ecitygml_Road_auxiliary_traffic_spaces(handle: Pointer): Pointer
    fun ecitygml_Road_markings(handle: Pointer): Pointer
    fun ecitygml_Road_holes(handle: Pointer): Pointer
    fun ecitygml_Road_try_from(feature: Pointer): Pointer?
    fun ecitygml_Road_class(handle: Pointer): Pointer?
    fun ecitygml_Road_functions(handle: Pointer): Pointer
    fun ecitygml_Road_usages(handle: Pointer): Pointer
    fun ecitygml_Road_sections(handle: Pointer): Pointer
    fun ecitygml_Road_intersections(handle: Pointer): Pointer
}
/** A road, borrowed from a city model.
*/
class Road internal constructor (
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

    private class RoadCleaner(val handle: Pointer, val lib: RoadLib) : Runnable {
        override fun run() {
            lib.ecitygml_Road_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Road.RoadCleaner(handle, Road.lib));
    }

    companion object {
        internal val libClass: Class<RoadLib> = RoadLib::class.java
        internal val lib: RoadLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature as a road, or none if it is another type (Rust: `<&Road>::try_from`).
        */
        fun tryFrom(feature: AbstractFeatureKindRef): Road? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(feature);
            
            val returnVal = lib.ecitygml_Road_try_from(feature.handle);
            val selfEdges: List<Any> = listOf(feature)
            val handle = returnVal ?: return null
            val returnOpaque = Road(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_id(handle);
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
        
        val returnVal = lib.ecitygml_Road_names(handle);
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
        
        val returnVal = lib.ecitygml_Road_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_Road_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_Road_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_Road_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_generic_attributes(handle);
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
        
        val returnVal = lib.ecitygml_Road_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun spaceType(): SpaceType? {
        
        val returnVal = lib.ecitygml_Road_space_type(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return SpaceType.fromNative(intermediateOption)
    }
    
    fun lod1Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod1_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod2_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod3_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod0_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod2_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod3_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod0_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod2_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod3_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0Point(): PointProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod0_point(handle);
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
        
        val returnVal = lib.ecitygml_Road_boundaries(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractSpaceBoundaryPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun lod1TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod1_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod2_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_lod3_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun trafficDirection(): TrafficDirectionValue? {
        
        val returnVal = lib.ecitygml_Road_traffic_direction(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return TrafficDirectionValue.fromNative(intermediateOption)
    }
    
    fun occupancies(): OccupancyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_occupancies(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = OccupancyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun trafficSpaces(): TrafficSpacePropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_traffic_spaces(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = TrafficSpacePropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun auxiliaryTrafficSpaces(): AuxiliaryTrafficSpacePropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_auxiliary_traffic_spaces(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AuxiliaryTrafficSpacePropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun markings(): MarkingPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_markings(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = MarkingPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun holes(): HolePropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_holes(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = HolePropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun class_(): RoadClassValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_class(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = RoadClassValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun functions(): RoadFunctionValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_functions(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = RoadFunctionValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun usages(): RoadUsageValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_usages(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = RoadUsageValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun sections(): SectionPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_sections(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = SectionPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun intersections(): IntersectionPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Road_intersections(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = IntersectionPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}