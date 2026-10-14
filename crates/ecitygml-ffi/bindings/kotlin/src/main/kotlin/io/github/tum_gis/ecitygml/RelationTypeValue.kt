package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RelationTypeValueLib: Library {
    fun ecitygml_RelationTypeValue_destroy(handle: Pointer)
    fun ecitygml_RelationTypeValue_code(handle: Pointer): Pointer
    fun ecitygml_RelationTypeValue_value(handle: Pointer): Slice
}
/** The `relationType` property of a CityObjectRelation.
*/
class RelationTypeValue internal constructor (
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

    private class RelationTypeValueCleaner(val handle: Pointer, val lib: RelationTypeValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_RelationTypeValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, RelationTypeValue.RelationTypeValueCleaner(handle, RelationTypeValue.lib));
    }

    companion object {
        internal val libClass: Class<RelationTypeValueLib> = RelationTypeValueLib::class.java
        internal val lib: RelationTypeValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RelationTypeValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RelationTypeValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}