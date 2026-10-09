package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface IdLib: Library {
    fun ecitygml_Id_destroy(handle: Pointer)
    fun ecitygml_Id_as_str(handle: Pointer): Slice
}
/** A `gml:id`, borrowed from a city model.
*/
class Id internal constructor (
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

    private class IdCleaner(val handle: Pointer, val lib: IdLib) : Runnable {
        override fun run() {
            lib.ecitygml_Id_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Id.IdCleaner(handle, Id.lib));
    }

    companion object {
        internal val libClass: Class<IdLib> = IdLib::class.java
        internal val lib: IdLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun asStr(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Id_as_str(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}