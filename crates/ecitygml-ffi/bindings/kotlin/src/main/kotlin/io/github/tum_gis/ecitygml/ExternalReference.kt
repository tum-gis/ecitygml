package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ExternalReferenceLib: Library {
    fun ecitygml_ExternalReference_destroy(handle: Pointer)
    fun ecitygml_ExternalReference_target_resource(handle: Pointer): Slice
    fun ecitygml_ExternalReference_information_system(handle: Pointer): OptionSlice
    fun ecitygml_ExternalReference_relation_type(handle: Pointer): OptionSlice
}
/** A reference to an object in another information system, borrowed from a city model.
*/
class ExternalReference internal constructor (
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

    private class ExternalReferenceCleaner(val handle: Pointer, val lib: ExternalReferenceLib) : Runnable {
        override fun run() {
            lib.ecitygml_ExternalReference_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, ExternalReference.ExternalReferenceCleaner(handle, ExternalReference.lib));
    }

    companion object {
        internal val libClass: Class<ExternalReferenceLib> = ExternalReferenceLib::class.java
        internal val lib: ExternalReferenceLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun targetResource(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ExternalReference_target_resource(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }
    
    fun informationSystem(): String? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ExternalReference_information_system(handle);
        
        val intermediateOption = returnVal.option() ?: return null
            return PrimitiveArrayTools.getUtf8(intermediateOption)
                                
    }
    
    fun relationType(): String? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ExternalReference_relation_type(handle);
        
        val intermediateOption = returnVal.option() ?: return null
            return PrimitiveArrayTools.getUtf8(intermediateOption)
                                
    }

}