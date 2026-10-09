package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractReliefComponentKindLib: Library {
    fun ecitygml_AbstractReliefComponentKind_destroy(handle: Pointer)
    fun ecitygml_AbstractReliefComponentKind_id(handle: Pointer): Pointer?
    fun ecitygml_AbstractReliefComponentKind_names(handle: Pointer): Pointer
    fun ecitygml_AbstractReliefComponentKind_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_AbstractReliefComponentKind_feature_id(handle: Pointer): Pointer
    fun ecitygml_AbstractReliefComponentKind_creation_date(handle: Pointer): Pointer?
    fun ecitygml_AbstractReliefComponentKind_termination_date(handle: Pointer): Pointer?
    fun ecitygml_AbstractReliefComponentKind_valid_from(handle: Pointer): Pointer?
    fun ecitygml_AbstractReliefComponentKind_valid_to(handle: Pointer): Pointer?
    fun ecitygml_AbstractReliefComponentKind_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_AbstractReliefComponentKind_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_AbstractReliefComponentKind_external_references(handle: Pointer): Pointer
    fun ecitygml_AbstractReliefComponentKind_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_AbstractReliefComponentKind_related_to(handle: Pointer): Pointer
    fun ecitygml_AbstractReliefComponentKind_lod(handle: Pointer): Int
    fun ecitygml_AbstractReliefComponentKind_feature_type(handle: Pointer): Int
}
/** A relief component (a TIN relief), borrowed from a city model. It has the getters of every
*ancestor; `feature_type()` tells which component it is. Not bound yet: the concrete types'
*own getters (e.g. `tin`); get a `TinRelief` from the features with `TinRelief::try_from`.
*/
class AbstractReliefComponentKind internal constructor (
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

    private class AbstractReliefComponentKindCleaner(val handle: Pointer, val lib: AbstractReliefComponentKindLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractReliefComponentKind_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractReliefComponentKind.AbstractReliefComponentKindCleaner(handle, AbstractReliefComponentKind.lib));
    }

    companion object {
        internal val libClass: Class<AbstractReliefComponentKindLib> = AbstractReliefComponentKindLib::class.java
        internal val lib: AbstractReliefComponentKindLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_id(handle);
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
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_names(handle);
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
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_generic_attributes(handle);
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
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun lod(): LevelOfDetail {
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_lod(handle);
        return (LevelOfDetail.fromNative(returnVal))
    }
    
    fun featureType(): FeatureType {
        
        val returnVal = lib.ecitygml_AbstractReliefComponentKind_feature_type(handle);
        return (FeatureType.fromNative(returnVal))
    }

}