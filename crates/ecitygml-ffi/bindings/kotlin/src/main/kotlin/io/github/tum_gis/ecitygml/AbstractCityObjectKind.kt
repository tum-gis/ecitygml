package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCityObjectKindLib: Library {
    fun ecitygml_AbstractCityObjectKind_destroy(handle: Pointer)
    fun ecitygml_AbstractCityObjectKind_id(handle: Pointer): Pointer?
    fun ecitygml_AbstractCityObjectKind_names(handle: Pointer): Pointer
    fun ecitygml_AbstractCityObjectKind_bounded_by(handle: Pointer): Pointer?
    fun ecitygml_AbstractCityObjectKind_feature_id(handle: Pointer): Pointer
    fun ecitygml_AbstractCityObjectKind_creation_date(handle: Pointer): Pointer?
    fun ecitygml_AbstractCityObjectKind_termination_date(handle: Pointer): Pointer?
    fun ecitygml_AbstractCityObjectKind_valid_from(handle: Pointer): Pointer?
    fun ecitygml_AbstractCityObjectKind_valid_to(handle: Pointer): Pointer?
    fun ecitygml_AbstractCityObjectKind_relative_to_terrain(handle: Pointer): OptionInt
    fun ecitygml_AbstractCityObjectKind_relative_to_water(handle: Pointer): OptionInt
    fun ecitygml_AbstractCityObjectKind_external_references(handle: Pointer): Pointer
    fun ecitygml_AbstractCityObjectKind_generic_attributes(handle: Pointer): Pointer
    fun ecitygml_AbstractCityObjectKind_related_to(handle: Pointer): Pointer
    fun ecitygml_AbstractCityObjectKind_feature_type(handle: Pointer): Int
}
/** A city object of any type (e.g. a building or road), borrowed from a city model. It has the
*getters of every ancestor; for the concrete type, convert it with
*`AbstractCityObjectKindRef::from_city_object`, `AbstractFeatureKindRef::from_city_object` and
*e.g. `Building::try_from`.
*/
class AbstractCityObjectKind internal constructor (
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

    private class AbstractCityObjectKindCleaner(val handle: Pointer, val lib: AbstractCityObjectKindLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractCityObjectKind_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractCityObjectKind.AbstractCityObjectKindCleaner(handle, AbstractCityObjectKind.lib));
    }

    companion object {
        internal val libClass: Class<AbstractCityObjectKindLib> = AbstractCityObjectKindLib::class.java
        internal val lib: AbstractCityObjectKindLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_id(handle);
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
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_names(handle);
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
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_bounded_by(handle);
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
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_feature_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun creationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_creation_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun terminationDate(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_termination_date(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validFrom(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_valid_from(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun validTo(): DateTime? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_valid_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DateTime(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun relativeToTerrain(): RelativeToTerrain? {
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_relative_to_terrain(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToTerrain.fromNative(intermediateOption)
    }
    
    fun relativeToWater(): RelativeToWater? {
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_relative_to_water(handle);
        
        val intermediateOption = returnVal.option() ?: return null
        return RelativeToWater.fromNative(intermediateOption)
    }
    
    fun externalReferences(): ExternalReferenceIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_external_references(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ExternalReferenceIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_generic_attributes(handle);
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
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_related_to(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CityObjectRelationPropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun featureType(): FeatureType {
        
        val returnVal = lib.ecitygml_AbstractCityObjectKind_feature_type(handle);
        return (FeatureType.fromNative(returnVal))
    }

}