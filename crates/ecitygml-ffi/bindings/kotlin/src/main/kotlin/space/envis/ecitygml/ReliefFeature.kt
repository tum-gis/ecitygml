package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ReliefFeatureLib: Library {
    fun ecitygml_ReliefFeature_destroy(handle: Pointer)
    fun ecitygml_ReliefFeature_id(handle: Pointer): Pointer?
    fun ecitygml_ReliefFeature_names(handle: Pointer): Pointer
    fun ecitygml_ReliefFeature_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_ReliefFeature_feature_id(handle: Pointer): Pointer
    fun ecitygml_ReliefFeature_creation_date(handle: Pointer): Pointer?
    fun ecitygml_ReliefFeature_termination_date(handle: Pointer): Pointer?
    fun ecitygml_ReliefFeature_valid_from(handle: Pointer): Pointer?
    fun ecitygml_ReliefFeature_valid_to(handle: Pointer): Pointer?
    fun ecitygml_ReliefFeature_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_ReliefFeature_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_ReliefFeature_external_references(handle: Pointer): Pointer
    fun ecitygml_ReliefFeature_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_ReliefFeature_related_to(handle: Pointer): Pointer
    fun ecitygml_ReliefFeature_try_from(feature: Pointer): Pointer?
    fun ecitygml_ReliefFeature_lod(handle: Pointer): Int
    fun ecitygml_ReliefFeature_relief_components(handle: Pointer): Pointer
}
/** A relief (terrain) feature made of relief components, borrowed from a city model.
*/
class ReliefFeature internal constructor (
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

    private class ReliefFeatureCleaner(val handle: Pointer, val lib: ReliefFeatureLib) : Runnable {
        override fun run() {
            lib.ecitygml_ReliefFeature_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, ReliefFeature.ReliefFeatureCleaner(handle, ReliefFeature.lib));
    }

    companion object {
        internal val libClass: Class<ReliefFeatureLib> = ReliefFeatureLib::class.java
        internal val lib: ReliefFeatureLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The feature as a relief feature, or none if it is another type (Rust: `<&ReliefFeature>::try_from`).
        */
        fun tryFrom(feature: AbstractFeatureKindRef): ReliefFeature? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(feature);
            
            val returnVal = lib.ecitygml_ReliefFeature_try_from(feature.handle);
            val selfEdges: List<Any> = listOf(feature)
            val handle = returnVal ?: return null
            val returnOpaque = ReliefFeature(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ReliefFeature_id(handle);
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
        
        val returnVal = lib.ecitygml_ReliefFeature_names(handle);
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
        
        val returnVal = lib.ecitygml_ReliefFeature_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_ReliefFeature_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ReliefFeature_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ReliefFeature_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ReliefFeature_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ReliefFeature_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_ReliefFeature_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_ReliefFeature_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ReliefFeature_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ReliefFeature_generic_attributes(handle);
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
        
        val returnVal = lib.ecitygml_ReliefFeature_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun lod(): LevelOfDetail {
        
        val returnVal = lib.ecitygml_ReliefFeature_lod(handle);
        return (LevelOfDetail.fromNative(returnVal))
    }
    
    fun reliefComponents(): AbstractReliefComponentPropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ReliefFeature_relief_components(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractReliefComponentPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}