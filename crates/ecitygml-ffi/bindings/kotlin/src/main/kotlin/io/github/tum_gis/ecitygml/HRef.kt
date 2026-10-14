package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface HRefLib: Library {
    fun ecitygml_HRef_destroy(handle: Pointer)
    fun ecitygml_HRef_local_id(handle: Pointer): OptionSlice
    fun ecitygml_HRef_is_local(handle: Pointer): Byte
    fun ecitygml_HRef_to_string(handle: Pointer, write: Pointer): Unit
}
/** An `xlink:href` reference (local `#id` or remote URI), borrowed from a city model.
*/
class HRef internal constructor (
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

    private class HRefCleaner(val handle: Pointer, val lib: HRefLib) : Runnable {
        override fun run() {
            lib.ecitygml_HRef_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, HRef.HRefCleaner(handle, HRef.lib));
    }

    companion object {
        internal val libClass: Class<HRefLib> = HRefLib::class.java
        internal val lib: HRefLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The referenced `gml:id` of a local reference (`#id`), or none for a remote one.
    */
    fun localId(): String? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_HRef_local_id(handle);
        
        val intermediateOption = returnVal.option() ?: return null
            return PrimitiveArrayTools.getUtf8(intermediateOption)
                                
    }
    
    fun isLocal(): Boolean {
        
        val returnVal = lib.ecitygml_HRef_is_local(handle);
        return (returnVal > 0)
    }
    
    /** The reference as written in GML (Rust: `Display`).
    */
    fun toString_(): String {
        val write = DW.lib.diplomat_buffer_write_create(0)
        val returnVal = lib.ecitygml_HRef_to_string(handle, write);
        
        val returnString = DW.writeToString(write)
        return returnString
    }

}