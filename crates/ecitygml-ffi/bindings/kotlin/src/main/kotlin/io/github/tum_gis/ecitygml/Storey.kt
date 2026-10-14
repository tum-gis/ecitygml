package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface StoreyLib: Library {
    fun ecitygml_Storey_destroy(handle: Pointer)
    fun ecitygml_Storey_id(handle: Pointer): Pointer?
    fun ecitygml_Storey_names(handle: Pointer): Pointer
    fun ecitygml_Storey_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_Storey_feature_id(handle: Pointer): Pointer
    fun ecitygml_Storey_creation_date(handle: Pointer): Pointer?
    fun ecitygml_Storey_termination_date(handle: Pointer): Pointer?
    fun ecitygml_Storey_valid_from(handle: Pointer): Pointer?
    fun ecitygml_Storey_valid_to(handle: Pointer): Pointer?
    fun ecitygml_Storey_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_Storey_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_Storey_external_references(handle: Pointer): Pointer
    fun ecitygml_Storey_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_Storey_related_to(handle: Pointer): Pointer
    fun ecitygml_Storey_space_type(handle: Pointer): OptionInt
    fun ecitygml_Storey_lod1_solid(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod2_solid(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod3_solid(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod0_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod2_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod3_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod0_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod2_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod3_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_Storey_lod0_point(handle: Pointer): Pointer?
    fun ecitygml_Storey_boundaries(handle: Pointer): Pointer
    fun ecitygml_Storey_class(handle: Pointer): Pointer?
    fun ecitygml_Storey_functions(handle: Pointer): Pointer
    fun ecitygml_Storey_usages(handle: Pointer): Pointer
    fun ecitygml_Storey_try_from(feature: Pointer): Pointer?
}
/** A storey, borrowed from a city model. It has no properties of its own in CityGML 3.0.
*/
class Storey internal constructor (
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

    private class StoreyCleaner(val handle: Pointer, val lib: StoreyLib) : Runnable {
        override fun run() {
            lib.ecitygml_Storey_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Storey.StoreyCleaner(handle, Storey.lib));
    }

    companion object {
        internal val libClass: Class<StoreyLib> = StoreyLib::class.java
        internal val lib: StoreyLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature as a storey, or none if it is another type (Rust: `<&Storey>::try_from`).
        */
        fun tryFrom(feature: AbstractFeatureKindRef): Storey? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(feature);
            
            val returnVal = lib.ecitygml_Storey_try_from(feature.handle);
            val selfEdges: List<Any> = listOf(feature)
            val handle = returnVal ?: return null
            val returnOpaque = Storey(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_id(handle);
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
        
        val returnVal = lib.ecitygml_Storey_names(handle);
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
        
        val returnVal = lib.ecitygml_Storey_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_Storey_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_Storey_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_Storey_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_generic_attributes(handle);
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
        
        val returnVal = lib.ecitygml_Storey_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun spaceType(): SpaceType? {
        
        val returnVal = lib.ecitygml_Storey_space_type(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return SpaceType.fromNative(intermediateOption)
    }
    
    fun lod1Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod1_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod2_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3Solid(): SolidProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod3_solid(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolidProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod0_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod2_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod3_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod0_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod2_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod3_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0Point(): PointProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_lod0_point(handle);
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
        
        val returnVal = lib.ecitygml_Storey_boundaries(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractSpaceBoundaryPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun class_(): BuildingSubdivisionClassValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_class(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BuildingSubdivisionClassValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun functions(): BuildingSubdivisionFunctionValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_functions(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = BuildingSubdivisionFunctionValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun usages(): BuildingSubdivisionUsageValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Storey_usages(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = BuildingSubdivisionUsageValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}