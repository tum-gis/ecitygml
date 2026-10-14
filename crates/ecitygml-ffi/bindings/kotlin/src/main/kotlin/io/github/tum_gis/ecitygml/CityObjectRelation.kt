package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CityObjectRelationLib: Library {
    fun ecitygml_CityObjectRelation_destroy(handle: Pointer)
    fun ecitygml_CityObjectRelation_relation_type(handle: Pointer): Pointer
    fun ecitygml_CityObjectRelation_relation_to(handle: Pointer): Pointer
    fun ecitygml_CityObjectRelation_generic_attributes(handle: Pointer): Pointer
}
/** A relation of a city object to another one, borrowed from a city model.
*/
class CityObjectRelation internal constructor (
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

    private class CityObjectRelationCleaner(val handle: Pointer, val lib: CityObjectRelationLib) : Runnable {
        override fun run() {
            lib.ecitygml_CityObjectRelation_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CityObjectRelation.CityObjectRelationCleaner(handle, CityObjectRelation.lib));
    }

    companion object {
        internal val libClass: Class<CityObjectRelationLib> = CityObjectRelationLib::class.java
        internal val lib: CityObjectRelationLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun relationType(): RelationTypeValue {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityObjectRelation_relation_type(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = RelationTypeValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The related city object (`relatedTo`), by reference.
    */
    fun relationTo(): Reference {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityObjectRelation_relation_to(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Reference(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityObjectRelation_generic_attributes(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = GenericAttributeKindIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}