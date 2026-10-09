package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SolitaryVegetationObjectLib: Library {
    fun ecitygml_SolitaryVegetationObject_destroy(handle: Pointer)
    fun ecitygml_SolitaryVegetationObject_id(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_names(handle: Pointer): Pointer
    fun ecitygml_SolitaryVegetationObject_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_feature_id(handle: Pointer): Pointer
    fun ecitygml_SolitaryVegetationObject_creation_date(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_termination_date(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_valid_from(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_valid_to(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_SolitaryVegetationObject_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_SolitaryVegetationObject_external_references(handle: Pointer): Pointer
    fun ecitygml_SolitaryVegetationObject_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_SolitaryVegetationObject_related_to(handle: Pointer): Pointer
    fun ecitygml_SolitaryVegetationObject_space_type(handle: Pointer): OptionInt
    fun ecitygml_SolitaryVegetationObject_lod1_solid(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod2_solid(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod3_solid(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod0_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod2_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod3_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod0_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod2_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod3_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod0_point(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_boundaries(handle: Pointer): Pointer
    fun ecitygml_SolitaryVegetationObject_lod1_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod2_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod3_terrain_intersection_curve(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod1_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod2_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_lod3_implicit_representation(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_try_from(feature: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_class(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_functions(handle: Pointer): Pointer
    fun ecitygml_SolitaryVegetationObject_usages(handle: Pointer): Pointer
    fun ecitygml_SolitaryVegetationObject_species(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_height(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_trunk_diameter(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_crown_diameter(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_root_ball_diameter(handle: Pointer): Pointer?
    fun ecitygml_SolitaryVegetationObject_max_root_ball_depth(handle: Pointer): Pointer?
}
/** A solitary vegetation object (e.g. a tree), borrowed from a city model.
*/
class SolitaryVegetationObject internal constructor (
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

    private class SolitaryVegetationObjectCleaner(val handle: Pointer, val lib: SolitaryVegetationObjectLib) : Runnable {
        override fun run() {
            lib.ecitygml_SolitaryVegetationObject_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, SolitaryVegetationObject.SolitaryVegetationObjectCleaner(handle, SolitaryVegetationObject.lib));
    }

    companion object {
        internal val libClass: Class<SolitaryVegetationObjectLib> = SolitaryVegetationObjectLib::class.java
        internal val lib: SolitaryVegetationObjectLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature as a solitary vegetation object, or none if it is another type (Rust: `<&SolitaryVegetationObject>::try_from`).
        */
        fun tryFrom(feature: AbstractFeatureKindRef): SolitaryVegetationObject? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(feature);
            
            val returnVal = lib.ecitygml_SolitaryVegetationObject_try_from(feature.handle);
            val selfEdges: List<Any> = listOf(feature)
            val handle = returnVal ?: return null
            val returnOpaque = SolitaryVegetationObject(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_id(handle);
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
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_names(handle);
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
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_generic_attributes(handle);
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
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun spaceType(): SpaceType? {
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_space_type(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return SpaceType.fromNative(intermediateOption)
    }
    
    fun lod1Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod1_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod2_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod3_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod0_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod2_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod3_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod0_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod2_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod3_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0Point(): PointProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod0_point(handle);
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
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_boundaries(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractSpaceBoundaryPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun lod1TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod1_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod2_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3TerrainIntersectionCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod3_terrain_intersection_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod1ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod1_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod2_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3ImplicitRepresentation(): ImplicitGeometryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_lod3_implicit_representation(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometryProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun class_(): SolitaryVegetationObjectClassValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_class(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolitaryVegetationObjectClassValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun functions(): SolitaryVegetationObjectFunctionValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_functions(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = SolitaryVegetationObjectFunctionValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun usages(): SolitaryVegetationObjectUsageValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_usages(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = SolitaryVegetationObjectUsageValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun species(): SpeciesValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_species(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SpeciesValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun height(): Measure? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_height(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Measure(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun trunkDiameter(): Measure? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_trunk_diameter(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Measure(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun crownDiameter(): Measure? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_crown_diameter(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Measure(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun rootBallDiameter(): Measure? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_root_ball_diameter(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Measure(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun maxRootBallDepth(): Measure? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObject_max_root_ball_depth(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Measure(handle, selfEdges, false)
        return returnOpaque
    }

}