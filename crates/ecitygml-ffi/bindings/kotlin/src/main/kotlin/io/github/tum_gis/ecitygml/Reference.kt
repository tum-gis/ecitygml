package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ReferenceLib: Library {
    fun ecitygml_Reference_destroy(handle: Pointer)
    fun ecitygml_Reference_from_traffic_space_reference(reference: Pointer): Pointer
    fun ecitygml_Reference_href(handle: Pointer): Pointer?
}
/** A reference to an object by `xlink:href`, borrowed from a city model.
*/
class Reference internal constructor (
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

    private class ReferenceCleaner(val handle: Pointer, val lib: ReferenceLib) : Runnable {
        override fun run() {
            lib.ecitygml_Reference_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Reference.ReferenceCleaner(handle, Reference.lib));
    }

    companion object {
        internal val libClass: Class<ReferenceLib> = ReferenceLib::class.java
        internal val lib: ReferenceLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** An owned copy of a traffic space reference (Rust: `From<&TrafficSpaceReference>`).
        */
        fun fromTrafficSpaceReference(reference: TrafficSpaceReference): Reference {
            
            val returnVal = lib.ecitygml_Reference_from_traffic_space_reference(reference.handle);
            val selfEdges: List<Any> = listOf()
            val handle = returnVal 
            val returnOpaque = Reference(handle, selfEdges, true)
            return returnOpaque
        }
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Reference_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}