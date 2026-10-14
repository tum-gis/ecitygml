package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficAreaLib: Library {
    fun ecitygml_AuxiliaryTrafficArea_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficArea_id(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_names(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficArea_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_feature_id(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficArea_creation_date(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_termination_date(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_valid_from(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_valid_to(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_AuxiliaryTrafficArea_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_AuxiliaryTrafficArea_external_references(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficArea_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficArea_related_to(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficArea_lod0_multi_curve(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_lod0_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_lod1_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_lod2_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_lod3_multi_surface(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_try_from(feature: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_class(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficArea_functions(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficArea_usages(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficArea_surface_material(handle: Pointer): Pointer?
}
/** An auxiliary traffic area, borrowed from a city model.
*/
class AuxiliaryTrafficArea internal constructor (
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

    private class AuxiliaryTrafficAreaCleaner(val handle: Pointer, val lib: AuxiliaryTrafficAreaLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficArea_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficArea.AuxiliaryTrafficAreaCleaner(handle, AuxiliaryTrafficArea.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficAreaLib> = AuxiliaryTrafficAreaLib::class.java
        internal val lib: AuxiliaryTrafficAreaLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature as an auxiliary traffic area, or none if it is another type (Rust: `<&AuxiliaryTrafficArea>::try_from`).
        */
        fun tryFrom(feature: AbstractFeatureKindRef): AuxiliaryTrafficArea? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(feature);
            
            val returnVal = lib.ecitygml_AuxiliaryTrafficArea_try_from(feature.handle);
            val selfEdges: List<Any> = listOf(feature)
            val handle = returnVal ?: return null
            val returnOpaque = AuxiliaryTrafficArea(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_id(handle);
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
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_names(handle);
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
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_generic_attributes(handle);
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
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun lod0MultiCurve(): MultiCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_lod0_multi_curve(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod0MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_lod0_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod1MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_lod1_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod2MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_lod2_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lod3MultiSurface(): MultiSurfaceProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_lod3_multi_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurfaceProperty(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun class_(): AuxiliaryTrafficAreaClassValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_class(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AuxiliaryTrafficAreaClassValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun functions(): AuxiliaryTrafficAreaFunctionValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_functions(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AuxiliaryTrafficAreaFunctionValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun usages(): AuxiliaryTrafficAreaUsageValueIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_usages(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AuxiliaryTrafficAreaUsageValueIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun surfaceMaterial(): SurfaceMaterialValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficArea_surface_material(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SurfaceMaterialValue(handle, selfEdges, false)
        return returnOpaque
    }

}