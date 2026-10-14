package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficAreaLib: Library {
    fun ecitygml_TrafficArea_destroy(handle: Pointer)
    fun ecitygml_TrafficArea_id(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_names(handle: Pointer): Pointer
    fun ecitygml_TrafficArea_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_feature_id(handle: Pointer): Pointer
    fun ecitygml_TrafficArea_creation_date(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_termination_date(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_valid_from(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_valid_to(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_TrafficArea_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_TrafficArea_external_references(handle: Pointer): Pointer
    fun ecitygml_TrafficArea_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_TrafficArea_related_to(handle: Pointer): Pointer
    fun ecitygml_TrafficArea_lod0_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_lod0_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_lod1_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_lod2_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_lod3_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_try_from(feature: Pointer): Pointer?
    fun ecitygml_TrafficArea_class(handle: Pointer): Pointer?
    fun ecitygml_TrafficArea_functions(handle: Pointer): Pointer
    fun ecitygml_TrafficArea_usages(handle: Pointer): Pointer
    fun ecitygml_TrafficArea_surface_material(handle: Pointer): Pointer?
}
/** A traffic area, borrowed from a city model.
*/
class TrafficArea internal constructor (
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

    private class TrafficAreaCleaner(val handle: Pointer, val lib: TrafficAreaLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficArea_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficArea.TrafficAreaCleaner(handle, TrafficArea.lib));
    }

    companion object {
        internal val libClass: Class<TrafficAreaLib> = TrafficAreaLib::class.java
        internal val lib: TrafficAreaLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature as a traffic area, or none if it is another type (Rust: `<&TrafficArea>::try_from`).
        */
        fun tryFrom(feature: AbstractFeatureKindRef): TrafficArea? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(feature);
            
            val returnVal = lib.ecitygml_TrafficArea_try_from(feature.handle);
            val selfEdges: List<Any> = listOf(feature)
            val handle = returnVal ?: return null
            val returnOpaque = TrafficArea(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_id(handle);
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
        
        val returnVal = lib.ecitygml_TrafficArea_names(handle);
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
        
        val returnVal = lib.ecitygml_TrafficArea_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_TrafficArea_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_TrafficArea_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_TrafficArea_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_generic_attributes(handle);
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
        
        val returnVal = lib.ecitygml_TrafficArea_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun lod0MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_lod0_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_lod0_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod1MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_lod1_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_lod2_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_lod3_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun class_(): TrafficAreaClassValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_class(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TrafficAreaClassValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun functions(): TrafficAreaFunctionValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_functions(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = TrafficAreaFunctionValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun usages(): TrafficAreaUsageValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_usages(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = TrafficAreaUsageValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun surfaceMaterial(): SurfaceMaterialValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficArea_surface_material(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SurfaceMaterialValue(handle, selfEdges, false)
        return returnOpaque
    }

}